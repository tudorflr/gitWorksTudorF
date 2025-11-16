library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity mpg is
  Port ( 
           btn: in std_logic;
           clk: in std_logic;
           enable: out std_logic
       );
end mpg;

architecture Behavioral of mpg is

signal counter: std_logic_vector(15 downto 0);
signal d1: std_logic;
signal d2: std_logic;
signal d3: std_logic;

begin
    process(clk)   --counter
    begin
        if rising_edge(clk) then
            counter <= counter + 1; 
        end if;
    end process;
    
    process(clk, btn, counter) --register 1
    begin
       if rising_edge(clk) then
          if counter = x"1111" then
             d1 <= btn;
          end if;   
       end if;
    end process;
    
    process(clk) --register 2 and 3
    begin
       if rising_edge(clk) then
          d2 <= d1;
          d3 <= d2;
        end if;   
    end process;
    
    enable <= d2 and not(d3);
    
end Behavioral;