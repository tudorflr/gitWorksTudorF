library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity dataPath is
    Port ( 
        mem_write : in STD_LOGIC;
        mem_enable : in STD_LOGIC;
        alu_res : inout STD_LOGIC_VECTOR(15 downto 0);
        clk : in STD_LOGIC;
        rd2 : in STD_LOGIC_VECTOR(15 downto 0);
        mem_data : out STD_LOGIC_VECTOR(15 downto 0)
    );
end dataPath;

architecture Behavioral of dataPath is
    
    type ram_array is array (0 to 255) of STD_LOGIC_VECTOR(15 downto 0);
    signal ram : ram_array := (others => x"0000");
    signal addr : STD_LOGIC_VECTOR(7 downto 0);

begin

process(clk, mem_enable, alu_res, rd2)
begin
    if rising_edge(clk) then
        if mem_enable = '1' then
            ram(conv_integer(alu_res(7 downto 0))) <= rd2;
        end if;
    end if;
    mem_data <= ram(conv_integer(alu_res(7 downto 0)));
    alu_res <= alu_res;
end process;

end Behavioral;