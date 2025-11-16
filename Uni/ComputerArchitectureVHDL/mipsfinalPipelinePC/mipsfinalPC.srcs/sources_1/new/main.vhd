library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity main is
  port (
    btn : in  std_logic_vector(4 downto 0);
    sw  : in  std_logic_vector(15 downto 0);
    led : out std_logic_vector(15 downto 0);
    an  : out std_logic_vector(3 downto 0);
    cat : out std_logic_vector(6 downto 0);
    clk : in  std_logic
  );
end entity main;

architecture Behavioral of main is

component mpg is
    port (
      btn    : in  std_logic;
      clk    : in  std_logic;
      enable : out std_logic
    );
  end component;

  component InstructionFetch is
    port (
      clk            : in  std_logic;
      jump           : in  std_logic;
      enablePC       : in  std_logic;
      resetPC        : in  std_logic;
      jumpAddress    : in  std_logic_vector(15 downto 0);
      PCSrc          : in  std_logic;
      branchAddress  : in  std_logic_vector(15 downto 0);
      PCPlusOne      : out std_logic_vector(15 downto 0);
      instruction    : out std_logic_vector(15 downto 0)
    );
  end component;

  component InstructionDecode is
    port (
      clk       : in  std_logic;
      regWrite  : in  std_logic;
      regDst    : in  std_logic;
      mpgBtn    : in  std_logic;
      extOp     : in  std_logic;
      instr     : in  std_logic_vector(15 downto 0);
      rd1       : out std_logic_vector(15 downto 0);
      rd2       : out std_logic_vector(15 downto 0);
      extImm    : out std_logic_vector(15 downto 0);
      func      : out std_logic_vector(2 downto 0);
      sa        : out std_logic;
      wd        : in  std_logic_vector(15 downto 0)
    );
  end component;

  component main_control is
    port (
      instr      : in  std_logic_vector(15 downto 0);
      reg_dst    : out std_logic;
      ext_op     : out std_logic;
      reg_write  : out std_logic;
      alu_src    : out std_logic;
      alu_op     : out std_logic_vector(2 downto 0);
      branch     : out std_logic;
      jump       : out std_logic;
      mem_write  : out std_logic;
      memto_reg  : out std_logic
    );
  end component;

  component dataPath is
    port (
      mem_write   : in  std_logic;
      mem_enable  : in  std_logic;
      alu_res     : inout std_logic_vector(15 downto 0);
      clk         : in  std_logic;
      rd2         : in  std_logic_vector(15 downto 0);
      mem_data    : out std_logic_vector(15 downto 0)
    );
  end component;

  component executionUnit is
    port (
      rd1             : in  std_logic_vector(15 downto 0);
      rd2             : in  std_logic_vector(15 downto 0);
      ext_imm         : in  std_logic_vector(15 downto 0);
      sa              : in  std_logic;
      func            : in  std_logic_vector(2 downto 0);
      alu_op          : in  std_logic_vector(2 downto 0);
      pc_plus_4       : in  std_logic_vector(15 downto 0);
      alu_src         : in  std_logic;
      branch_address  : out std_logic_vector(15 downto 0);
      zero            : out std_logic;
      alu_res         : out std_logic_vector(15 downto 0)
    );
  end component;

  component ssdEn is
    port (
      digit0 : in std_logic_vector(3 downto 0);
      digit1 : in std_logic_vector(3 downto 0);
      digit2 : in std_logic_vector(3 downto 0);
      digit3 : in std_logic_vector(3 downto 0);
      clk    : in std_logic;
      an     : out std_logic_vector(3 downto 0);
      ca     : out std_logic_vector(6 downto 0)
    );
  end component;

  
  component dReg is
    generic ( N : integer );
    port (
      en     : in std_logic;
      input  : in std_logic_vector(N-1 downto 0);
      clk    : in std_logic;
      output : out std_logic_vector(N-1 downto 0)
    );
  end component;

  -- Pipeline register signals
  signal if_id_in : std_logic_vector(31 downto 0);
  signal if_id_out : std_logic_vector(31 downto 0);
  
  signal id_ex_in : std_logic_vector(82 downto 0);
  signal id_ex_out : std_logic_vector(82 downto 0);
  
  signal ex_mem_in : std_logic_vector(55 downto 0);  -- 56 bits (0 to 55)
  signal ex_mem_out : std_logic_vector(55 downto 0);
  
  signal mem_wb_in : std_logic_vector(36 downto 0);
  signal mem_wb_out : std_logic_vector(36 downto 0);
  
  -- Internal signals
  signal enable1, enable2, enable3, enable4 : std_logic;
  signal instructionSig    : std_logic_vector(15 downto 0);
  signal PCPlusOneAux      : std_logic_vector(15 downto 0);
  
  -- Control signals
  signal reg_dst, ext_op, reg_write : std_logic;
  signal alu_src                      : std_logic;
  signal alu_op                       : std_logic_vector(2 downto 0);
  signal branch                       : std_logic;
  signal jump                         : std_logic;
  signal mem_write, memto_reg         : std_logic;
  
  signal rd1, rd2, extImm : std_logic_vector(15 downto 0);
  signal func             : std_logic_vector(2 downto 0);
  signal sa               : std_logic;
  signal write_data       : std_logic_vector(15 downto 0);
  
  signal alu_res_internal : std_logic_vector(15 downto 0);
  signal zero             : std_logic;
  signal mem_data         : std_logic_vector(15 downto 0);
  signal digits           : std_logic_vector(15 downto 0);
  
  signal branchAddressAux : std_logic_vector(15 downto 0);
  signal jumpAddressAux   : std_logic_vector(15 downto 0);
  signal PCSrcAux         : std_logic;
  
  signal write_reg        : std_logic_vector(2 downto 0);

begin

  -- Button edge detectors
  mpg1 : mpg port map(btn => btn(0), clk => clk, enable => enable1);
  mpg2 : mpg port map(btn => btn(1), clk => clk, enable => enable2);
  mpg3 : mpg port map(btn => btn(2), clk => clk, enable => enable3);
  mpg4 : mpg port map(btn => btn(3), clk => clk, enable => enable4);

  -- Instruction Fetch
  instructionFetch1 : InstructionFetch port map(
    clk           => clk,
    jump          => jump,
    enablePC      => enable2,
    resetPC       => enable3,
    jumpAddress   => jumpAddressAux,
    PCSrc         => PCSrcAux,
    branchAddress => branchAddressAux,
    PCPlusOne     => PCPlusOneAux,
    instruction   => instructionSig
  );

  -- IF/ID Pipeline Register
  if_id_in <= PCPlusOneAux & instructionSig;
  if_id_reg : dReg generic map(N => 32) 
             port map(en => '1', input => if_id_in, clk => clk, output => if_id_out);

  -- Main Control Unit
  main_comp : main_control port map(
    instr     => if_id_out(15 downto 0),  
    reg_dst   => reg_dst,
    ext_op    => ext_op,
    reg_write => reg_write,
    alu_src   => alu_src,
    alu_op    => alu_op,
    branch    => branch,
    jump      => jump,
    mem_write => mem_write,
    memto_reg => memto_reg
  );

  -- Instruction Decode
  instructionDecode1 : InstructionDecode port map(
    clk      => clk,
    regWrite => mem_wb_out(35),  
    regDst   => reg_dst,
    mpgBtn   => enable2,
    extOp    => ext_op,
    instr    => if_id_out(15 downto 0),  
    rd1      => rd1,
    rd2      => rd2,
    extImm   => extImm,
    func     => func,
    sa       => sa,
    wd       => write_data
  );
  
  -- ID/EX Pipeline Register
  id_ex_in <= memto_reg & reg_write & mem_write & branch & alu_op & alu_src & reg_dst & 
              if_id_out(31 downto 16) &  
              rd1 & rd2 & extImm & func & sa & 
              if_id_out(9 downto 7) &    
              if_id_out(6 downto 4);     
              
  id_ex_reg : dReg generic map(N => 83) 
             port map(en => '1', input => id_ex_in, clk => clk, output => id_ex_out);

  -- Execute Unit
  execution_unit: executionUnit port map(
    rd1            => id_ex_out(57 downto 42),  
    rd2            => id_ex_out(41 downto 26),  
    ext_imm        => id_ex_out(25 downto 10),  
    sa             => id_ex_out(6),             
    func           => id_ex_out(9 downto 7),    
    alu_op         => id_ex_out(78 downto 76),  
    pc_plus_4      => id_ex_out(73 downto 58), 
    alu_src        => id_ex_out(75),            
    branch_address => branchAddressAux,
    zero           => zero,
    alu_res        => alu_res_internal
  );
  
  -- Destination register selection
  write_reg <= id_ex_out(2 downto 0) when id_ex_out(74) = '1' else 
               id_ex_out(5 downto 3); 
  
  -- EX/MEM Pipeline Register (56 bits: 0 to 55)
  ex_mem_in <= id_ex_out(82 downto 79) &  
               branchAddressAux &         
               zero &                     
               alu_res_internal &         
               id_ex_out(41 downto 26) &  
               write_reg;                 
               
  ex_mem_reg : dReg generic map(N => 56) 
             port map(en => '1', input => ex_mem_in, clk => clk, output => ex_mem_out);

  
  PCSrcAux <= ex_mem_out(52) and ex_mem_out(35);  -- branch and zero

-- Data Path (Memory) - using proper indices
  memory_comp: dataPath port map(
    mem_write  => ex_mem_out(53),          
    mem_enable => enable4,
    alu_res    => ex_mem_out(34 downto 19),  
    clk        => clk,
    rd2        => ex_mem_out(18 downto 3),   
    mem_data   => mem_data
  );
  
  -- MEM/WB Pipeline Register (37 bits)
  mem_wb_in <= ex_mem_out(55) & ex_mem_out(54) &  
               mem_data &                         
               ex_mem_out(34 downto 19) &         
               ex_mem_out(2 downto 0);            
               
  mem_wb_reg : dReg generic map(N => 37) 
             port map(en => '1', input => mem_wb_in, clk => clk, output => mem_wb_out);

  -- Writeback data selection
  write_data <= mem_wb_out(34 downto 19) when mem_wb_out(36) = '1' else 
                mem_wb_out(18 downto 3); 
  
  -- Jump address calculation
  jumpAddressAux <= if_id_out(31 downto 29) & if_id_out(12 downto 0);  

  -- Display multiplexer
  process(sw(7 downto 5))
  begin
    case sw(7 downto 5) is
      when "000" => digits <= instructionSig;           
      when "001" => digits <= PCPlusOneAux;             
      when "010" => digits <= id_ex_out(57 downto 42);  
      when "011" => digits <= id_ex_out(41 downto 26);  
      when "100" => digits <= id_ex_out(25 downto 10);  
      when "101" => digits <= ex_mem_out(34 downto 19); 
      when "110" => digits <= mem_wb_out(34 downto 19); 
      when "111" => digits <= write_data;               
      when others => digits <= (others => '0');
    end case;
  end process;

  -- LEDs display
  process(sw(0))
  begin
    if sw(0) = '0' then
      led(0) <= reg_dst;
      led(1) <= ext_op;
      led(2) <= reg_write;
      led(3) <= alu_src;
      led(4) <= branch;
      led(5) <= jump;
      led(6) <= mem_write;
      led(7) <= memto_reg;
    else
      led(0) <= alu_op(0);
      led(1) <= alu_op(1);
      led(2) <= alu_op(2);
      led(3) <= '0';
      led(4) <= '0';
      led(5) <= '0';
      led(6) <= '0';
      led(7) <= '0';
    end if;
  end process;

  -- Seven-segment display
  ssd_for_rom : ssdEn port map(
    digit0 => digits(3 downto 0),
    digit1 => digits(7 downto 4),
    digit2 => digits(11 downto 8),
    digit3 => digits(15 downto 12),
    clk    => clk,
    an     => an,
    ca     => cat
  );

end architecture Behavioral;