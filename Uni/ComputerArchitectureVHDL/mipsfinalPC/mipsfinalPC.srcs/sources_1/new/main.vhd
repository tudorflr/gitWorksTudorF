library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

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

  -- Internal signals
  signal enable1, enable2, enable3, enable4 : std_logic;
  signal instructionSig    : std_logic_vector(15 downto 0);
  signal PCPlusOneAux      : std_logic_vector(15 downto 0);
  signal branchAddressAux  : std_logic_vector(15 downto 0);
  signal jumpAddressAux    : std_logic_vector(15 downto 0);
  signal PCSrcAux          : std_logic;

  signal reg_dst, ext_op, reg_write : std_logic;
  signal alu_src                      : std_logic;
  signal alu_op                       : std_logic_vector(2 downto 0);
  signal branch                       : std_logic;
  signal jump                         : std_logic;
  signal mem_write, memto_reg        : std_logic;

  signal rd1, rd2, extImm : std_logic_vector(15 downto 0);
  signal func             : std_logic_vector(2 downto 0);
  signal sa               : std_logic;
  signal write_data : std_logic_vector(15 downto 0);

  signal alu_res_internal : std_logic_vector(15 downto 0);
  signal zero             : std_logic;
  signal mem_data         : std_logic_vector(15 downto 0);
  signal digits           : std_logic_vector(15 downto 0);

begin

  -- Button edge detectors
  mpg1 : mpg port map(btn => btn(0), clk => clk, enable => enable1);
  mpg2 : mpg port map(btn => btn(1), clk => clk, enable => enable2);
  mpg3 : mpg port map(btn => btn(2), clk => clk, enable => enable3);
  mpg4 : mpg port map(btn => btn(3), clk => clk, enable => enable4);

  -- Instruction Fetch
  instructionFetch1 : InstructionFetch port map(
    clk           => clk,
    jump          => enable1,
    enablePC      => enable2,
    resetPC       => enable3,
    jumpAddress   => jumpAddressAux,
    PCSrc         => PCSrcAux,
    branchAddress => branchAddressAux,
    PCPlusOne     => PCPlusOneAux,
    instruction   => instructionSig
  );

  -- Main Control Unit
  main_comp : main_control port map(
    instr     => instructionSig,
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
    regWrite => reg_write,
    regDst   => reg_dst,
    mpgBtn => enable2,
    extOp    => ext_op,
    instr    => instructionSig,
    rd1      => rd1,
    rd2      => rd2,
    extImm   => extImm,
    func     => func,
    sa       => sa,
    --wd       => (others => '0')
    wd       => write_data
  );
  
    process(memto_reg, mem_data, alu_res_internal)
    begin
    if memto_reg = '1' then
        write_data <= mem_data;
    else
        write_data <= alu_res_internal;
    end if;
    end process;

  -- Execute Unit
  execution_unit: executionUnit port map(
    rd1            => rd1,
    rd2            => rd2,
    ext_imm        => extImm,
    sa             => sa,
    func           => func,
    alu_op         => alu_op,
    pc_plus_4      => PCPlusOneAux,
    alu_src        => alu_src,
    branch_address => branchAddressAux,
    zero           => zero,
    alu_res        => alu_res_internal
  );

  -- Data Path
  memory_comp: dataPath port map(
    mem_write  => mem_write,
    mem_enable => enable4,
    alu_res    => alu_res_internal,
    clk        => clk,
    rd2        => rd2,
    mem_data   => mem_data
  );

  PCSrcAux <= branch and zero;

  -- Display and Write-back
  process(sw(7 downto 5), clk)
  begin
    case sw(7 downto 5) is
      when "000" => digits <= instructionSig;
      when "001" => digits <= PCPlusOneAux;
      when "010" => digits <= rd1;
      when "011" => digits <= rd2;
      when "100" => digits <= extImm;
      when "101" => digits <= alu_res_internal;
      when "110" => digits <= mem_data;
      when "111" => digits <= write_data;
      when others => digits <= (others => '0');
    end case;
  end process;

  write_back: process(memto_reg, alu_res_internal, mem_data)
  begin
    if memto_reg = '1' then
      null;
    end if;
  end process;

  -- LEDs
  process(sw(0), clk)
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
