library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity ssdEn is
--  Port ( );
    Port(
        digit0 : in STD_LOGIC_VECTOR(3 downto 0);
        digit1 : in STD_LOGIC_VECTOR(3 downto 0);
        digit2 : in STD_LOGIC_VECTOR(3 downto 0);
        digit3 : in STD_LOGIC_VECTOR(3 downto 0);
        clk : in STD_LOGIC;
        an : out STD_LOGIC_VECTOR(3 downto 0);
        ca : out STD_LOGIC_VECTOR(6 downto 0)
    );
end ssdEn;

architecture Behavioral of ssdEn is

signal caOut : STD_LOGIC_VECTOR(6 downto 0) := (others => '0');
signal cnt : STD_LOGIC_VECTOR(15 downto 0) := (others => '0');
signal selectMux : STD_LOGIC_VECTOR(1 downto 0) := (others => '0');
signal digitBinary : STD_LOGIC_VECTOR(3 downto 0) := (others => '0');
signal anOut : STD_LOGIC_VECTOR(3 downto 0) := (others => '0');

begin

process(clk)
begin
    if rising_edge(clk) then
        cnt <= cnt + 1;
    end if;
end process;

--selectMux(0) <= cnt(15);
--selectMux(1) <= cnt(14);

process(selectMux)
begin
    case cnt(15 downto 14) is
        when "00" => digitBinary <= digit0;
        when "01" => digitBinary <= digit1;
        when "10" => digitBinary <= digit2;
        when others => digitBinary <= digit3;
    end case;
    
    case cnt(15 downto 14) is
        when "00" => an <= "1110";
        when "01" => an <= "1101";
        when "10" => an <= "1011";
        when "11" => an <= "0111";
        when others => an <= "0000";
    end case;
    
end process;

process(digitBinary)
begin
    case digitBinary is
        when "0001"=>ca<="1111001"; -- 1
        when "0010"=>ca<="0100100"; -- 2
        when "0011"=>ca<="0110000"; -- 3
        when "0100"=>ca<="0011001"; -- 4
        when "0101"=>ca<="0010010"; -- 5
        when "0110"=>ca<="0000010"; -- 6
        when "0111"=>ca<="1111000"; -- 7
        when "1000"=>ca<="0000000"; -- 8
        when "1001"=>ca<="0010000"; -- 9
        when "1010"=>ca<="0001000"; -- A
        when "1011"=>ca<="0000011"; -- b
        when "1100"=>ca<="1000110"; -- C
        when "1101"=>ca<="0100001"; -- d
        when "1110"=>ca<="0000110"; -- E
        when "1111"=>ca<="0001110"; -- F
        when others=>ca<="1000000"; -- 0
    end case;
end process;

--an <= anOut;
    
--ca <= caOut;
    
    

end Behavioral;
