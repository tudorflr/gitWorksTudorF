library ieee;
  use ieee.std_logic_1164.all;
  use ieee.std_logic_arith.all;
  use ieee.std_logic_unsigned.all;

entity reg_file is
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
end reg_file;
architecture Behavioral of reg_file is
    
    type reg_array is array (0 to 15) of std_logic_vector(15 downto 0);
    signal reg_file : reg_array := (x"0000", x"0001", x"0010", x"0011", x"0100", x"0101", others => x"0000");
    
    type ram_array is array (0 to 15) of std_logic_vector(15 downto 0);
    signal ram : ram_array := (x"0000", x"0002", x"0003", x"0004", others => x"0000");
    
begin
    --regFile
    process(clk)
    begin
        if rising_edge(clk) then
            if wen = '1' and mpgBtn = '1' then
                reg_file(conv_integer(wa)) <= wd;
            end if;
        end if;
    end process;

    --ram
--    process(clk)
--    begin
--        if rising_edge(clk) then
--            if wen = '1' then
--                ram(conv_integer(ra1)) <= ram_in;
--            else
--                ram_out <= ram(conv_integer(ra1));
--            end if;          
--        end if;
--    end process;
    
  
    
    rd1 <= reg_file(conv_integer(ra1));
    rd2 <= reg_file(conv_integer(ra2));
end Behavioral;