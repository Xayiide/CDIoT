
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity LEDswitch is
    port (clk : in  STD_LOGIC;
          sw0 : in  STD_LOGIC;
          led : out STD_LOGIC);
end LEDswitch;

architecture Arch_LEDswitch of LEDswitch is

begin
    process (clk) is
    begin
        if (rising_edge(clk)) then
            if (sw0 = '0') then
                led <= '0';
            else
                led <= '1';
            end if;
        end if;
    end process;
end Arch_LEDswitch;
