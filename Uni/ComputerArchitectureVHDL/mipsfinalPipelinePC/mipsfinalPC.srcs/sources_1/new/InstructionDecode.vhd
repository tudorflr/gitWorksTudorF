library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity InstructionDecode is
    Port (
        clk : in STD_LOGIC;
        instr : in STD_LOGIC_VECTOR(15 downto 0);
        regWrite : in STD_LOGIC;
        regDst : in STD_LOGIC;
        mpgBtn : in STD_LOGIC;
        extOp : in STD_LOGIC;
        rd1 : out STD_LOGIC_VECTOR(15 downto 0);
        rd2 : out STD_LOGIC_VECTOR(15 downto 0);
        wd : in STD_LOGIC_VECTOR(15 downto 0);
        extImm : out STD_LOGIC_VECTOR(15 downto 0);
        func : out STD_LOGIC_VECTOR(2 downto 0);
        sa : out STD_LOGIC
     );
end InstructionDecode;

architecture Behavioral of InstructionDecode is

signal mux1 : STD_LOGIC_VECTOR(2 downto 0);

component reg_file is
port (
    clk : in std_logic;
    ra1 : in std_logic_vector (2 downto 0);
    ra2 : in std_logic_vector (2 downto 0);
    mpgBtn : in std_logic;
    wa : in std_logic_vector (2 downto 0);
    wd : in std_logic_vector (15 downto 0);
    wen : in std_logic;
    rd1 : out std_logic_vector (15 downto 0);
    rd2 : out std_logic_vector (15 downto 0)
    --ram_in : in std_logic_vector (3 downto 0);
    --ram_out : out std_logic_vector (15 downto 0)
    );
end component;

begin

process(regDst, instr)
begin
    if regDst = '1' then
        mux1 <= instr(9 downto 7);
    else
        mux1 <= instr(6 downto 4);
    end if;
end process;

reg_file1 : reg_file port map(
    clk => clk,
    ra1 => instr(12 downto 10),
    ra2 => instr(9 downto 7),
    mpgBtn => mpgBtn,
    wa => mux1,
    wd => wd,
    wen => regWrite,
    rd1 => rd1,
    rd2 => rd2
    );

process(extOp, instr)
begin
    if extOp = '0' then
        extImm <= "000000000" & instr(6 downto 0);
    else 
        extImm <= (15 downto 7 => instr(6)) & instr(6 downto 0);
    end if;
end process;

func <= instr(2 downto 0);
sa <= instr(3);

end Behavioral;
