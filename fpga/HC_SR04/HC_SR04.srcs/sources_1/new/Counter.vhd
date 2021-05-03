-- Test

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all; -- to_unsigned()

entity Counter is
    generic (n : POSITIVE := 10);
    port ( clk  : in  STD_LOGIC;
           en   : in  STD_LOGIC;
           rst  : in  STD_LOGIC; -- Active low
           cout : out STD_LOGIC_VECTOR ((n-1) downto 0));
end Counter;

architecture Arch_Counter of Counter is
    signal count : UNSIGNED ((n-1) downto 0);
begin
    process (clk, rst)
    begin
        if (rst = '0') then
            count <= (others => '0'); -- Reset the count
        elsif (clk'event and clk = '1') then
            if (en = '1') then
                count <= count + 1;
            end if;
        end if;
    end process;
    
    cout <= STD_LOGIC_VECTOR(count);

end Arch_Counter;
