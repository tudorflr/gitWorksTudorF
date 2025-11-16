library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

entity executionUnit is
    Port ( 
    rd1 : in STD_LOGIC_VECTOR(15 downto 0);
    rd2 : in STD_LOGIC_VECTOR(15 downto 0);
    ext_imm : in STD_LOGIC_VECTOR(15 downto 0);
    sa : in STD_LOGIC;
    func : in STD_LOGIC_VECTOR(2 downto 0);
    alu_op : in STD_LOGIC_VECTOR(2 downto 0);
    pc_plus_4 : in STD_LOGIC_VECTOR(15 downto 0);
    alu_src : in STD_LOGIC;
    branch_address : out STD_LOGIC_VECTOR(15 downto 0);
    zero : out STD_LOGIC;
    alu_res : out STD_LOGIC_VECTOR(15 downto 0)
    );
end executionUnit;

architecture Behavioral of executionUnit is

signal mux_out : std_logic_vector(15 downto 0);
signal alu_ctrl : std_logic_vector(2 downto 0);

begin

process(alu_src, rd2, ext_imm)
begin
    if alu_src = '1' then
    mux_out <= ext_imm;
    else
    mux_out <= rd2;
    end if;
end process;

process(alu_op, func)
begin
    case alu_op is
    when "001" => 
        case func is
        when "000" => alu_ctrl <= "000";
        when "001" => alu_ctrl <= "001";
        when "010" => alu_ctrl <= "010";
        when "011" => alu_ctrl <= "011";
        when "100" => alu_ctrl <= "100";
        when "101" => alu_ctrl <= "101";
        when "110" => alu_ctrl <= "110";
        when "111" => alu_ctrl <= "111";
        when others => alu_ctrl <= "000";
        end case;
    when "010" => alu_ctrl <= "000";
    when "011" => alu_ctrl <= "001";
    when "000" => alu_ctrl <= "100";
    when "100" => alu_ctrl <= "101";
    when others => alu_ctrl <= "000";
    end case;
end process;

process(rd1, mux_out, alu_ctrl, sa)
begin
    zero <= '0';
    case alu_ctrl is
        when "000" => alu_res <= rd1 + mux_out;
        when "001" => alu_res <= rd1 - mux_out;
    if (rd1 = mux_out) then
        zero <= '1';
    else
        zero <= '0';
    end if;
    when "010" => if (sa = '1') then
        alu_res <= rd1(14 downto 0) & '0';
    else
        alu_res <= rd1;
    end if;
    when "011" => if (sa = '1') then
        alu_res <= '0' & rd1(15 downto 1);
    else
        alu_res <= rd1;
    end if;
        when "100" => alu_res <= rd1 and mux_out;
        when "101" => alu_res <= rd1 or mux_out;
        when "110" => alu_res <= rd1 xor mux_out;
        when "111" => alu_res <= rd1 xnor mux_out;
        when others => alu_res <= (others => '0');
    end case;
end process;

branch_address <= ext_imm + pc_plus_4;

end Behavioral;