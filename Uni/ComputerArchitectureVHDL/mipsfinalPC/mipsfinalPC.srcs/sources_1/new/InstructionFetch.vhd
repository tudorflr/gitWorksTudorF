library IEEE;
  use ieee.std_logic_1164.all;
  use ieee.std_logic_arith.all;
  use ieee.std_logic_unsigned.all;


entity InstructionFetch is
  Port ( 
        clk : in STD_LOGIC;
        jump : in STD_LOGIC;
        enablePC : in STD_LOGIC;
        resetPC : in STD_LOGIC;
        jumpAddress : in STD_LOGIC_VECTOR(15 downto 0);
        PCSrc : in STD_LOGIC;
        branchAddress : in STD_LOGIC_VECTOR(15 downto 0);
        PCPlusOne : out STD_LOGIC_VECTOR(15 downto 0);
        instruction : out STD_LOGIC_VECTOR(15 downto 0)
        );
end InstructionFetch;

architecture Behavioral of InstructionFetch is

type mem_type is array (0 to 255) of STD_LOGIC_VECTOR(15 downto 0);
signal mem : mem_type := (

   0  => B"001_000_001_0001000",    -- addi  $1,$0,8     -> 0+8=  8  (x\"0008\")    2088

   1  => B"000_001_010_100_0_000",  -- add   $4,$1,$2                               540
   2  => B"000_001_010_101_0_001",  -- sub   $5,$1,$2                               551
   3  => B"000_000_011_110_1_010",  -- sll   $6,$3,1                                1EA
   4  => B"000_000_011_111_1_011",  -- srl   $7,$3,1                                1Fb
   5  => B"000_010_011_100_0_100",  -- AND   $4,$2,$3                               9C4
   6  => B"000_010_011_101_0_101",  -- OR    $5,$2,$3                               9d5
   7  => B"000_010_011_110_0_110",  -- XOR   $6,$2,$3                               9E6
   8  => B"000_010_011_111_0_111",  -- XNOR  $7,$2,$3                               9F7

   9  => B"001_000_001_0001000",    -- addi  $1,$0,8     -> 0+8=  8  (x\"0008\")    2088
  10  => B"001_001_010_0001010",    -- addi  $2,$1,10    -> 8+10=18  (x\"0012\")    250A
  11  => B"011_010_011_0000100",    -- sw    $3,4($2)                               6984
  12  => B"010_010_011_0000011",    -- lw    $3,3($2)                               4983
  13  => B"100_001_011_0000010",    -- beq   $1,$3,2                                8582

  14  => B"101_000_001_0000111",    -- ori   $1,$0,7     -> 0|7=7   (x\"0007\")     A087
  15  => B"110_001_010_0000011",    -- slti  $2,$1,3     -> 7<3? no=0  (x\"0000\")  C503

  16  => B"111_0000000001111",      -- j                                            E00F

  others => x"0000"
  );
signal pc : STD_LOGIC_VECTOR(15 downto 0);
signal regData : STD_LOGIC_VECTOR(15 downto 0);
signal outMux1 : STD_LOGIC_VECTOR(15 downto 0);
--signal outMux2 : STD_LOGIC_VECTOR(15 downto 0);
signal PCPlusOneSig : STD_LOGIC_VECTOR(15 downto 0);

begin


process(clk)
begin
    if resetPC = '1' then
        regData <= (others => '0');
    else
        if rising_edge(clk) then
            if enablePC = '1' then
                regData <= pc;
            end if;
        end if;
    end if;
end process;

PCPlusOne <= regData + 1;
PCPlusOneSig <= regData + 1;

-- mux 1
process(PCPlusOneSig, PCSrc, branchAddress)
begin
    if PCSrc = '1' then
        outMux1 <= branchAddress;
    else
        outMux1 <= PCPlusOneSig;
    end if;
end process;

-- mux 2
process(outMux1, jump, jumpAddress)
begin
    if jump = '1' then
        pc <= jumpAddress;
    else
        pc <= outMux1;
    end if;
end process;

instruction <= mem(conv_integer(regData(7 downto 0)));
        

end Behavioral;
