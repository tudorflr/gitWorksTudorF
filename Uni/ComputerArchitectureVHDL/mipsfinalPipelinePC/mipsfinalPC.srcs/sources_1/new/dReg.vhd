library IEEE;
use IEEE.STD_LOGIC_1164.ALL;



entity dReg is
  generic (
    N : integer);
    Port (
    en: in std_logic;
    input: in std_logic_vector(N-1 downto 0);
    clk : in std_logic;
    output : out std_logic_vector(N-1 downto 0));
end dReg;

architecture Behavioral of dReg is

begin

process(clk)
begin
    if rising_edge(clk) then
        if en = '1' then
            output <= input;
        end if;
    end if;
end process;

end Behavioral;
