
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity LEDs is
    port (clk       : in  STD_LOGIC;
          en        : in  STD_LOGIC;
          sw0       : in  STD_LOGIC;
          sw1       : in  STD_LOGIC;
          led_drive : out STD_LOGIC);
end LEDs;

architecture Arch_LEDs of LEDs is
    constant c_CNT_25HZ : natural := 2000000;
    constant c_CNT_5HZ  : natural := 10000000;
    constant c_CNT_2HZ  : natural := 25000000;
    constant c_CNT_1HZ  : natural := 50000000;
    
    signal count25HZ : natural range 0 to c_CNT_25HZ;
    signal count5HZ  : natural range 0 to c_CNT_5HZ;
    signal count2HZ  : natural range 0 to c_CNT_2HZ;
    signal count1HZ  : natural range 0 to c_CNT_1HZ;
    
    signal toggle25HZ : STD_LOGIC := '0';
    signal toggle5HZ  : STD_LOGIC := '0';
    signal toggle2HZ  : STD_LOGIC := '0';
    signal toggle1HZ  : STD_LOGIC := '0';
    
    signal w_LED_SELECT : STD_LOGIC; -- needed signal for mux
    
begin
    p_25_HZ : process (clk) is
    begin
        if (rising_edge(clk)) then
            if (count25HZ = (c_CNT_25HZ - 1)) then -- -1 since counter starts at 0
                toggle25HZ <= not toggle25HZ;      -- Da la vuelta
                count25HZ <= 0;
            else
                count25HZ <= count25HZ + 1;
            end if;
        end if;
    end process p_25_HZ;

    p_5_HZ : process (clk) is
    begin
        if (rising_edge(clk)) then
            if (count5HZ = (c_CNT_5HZ - 1)) then -- -1 since counter starts at 0
                toggle5HZ <= not toggle5HZ;      -- Da la vuelta
                count5HZ <= 0;
            else
                count5HZ <= count5HZ + 1;
            end if;
        end if;
    end process p_5_HZ;

    p_2_HZ : process (clk) is
    begin
        if (rising_edge(clk)) then
            if (count2HZ = (c_CNT_2HZ - 1)) then -- -1 since counter starts at 0
                toggle2HZ <= not toggle2HZ;      -- Da la vuelta
                count2HZ <= 0;
            else
                count2HZ <= count2HZ + 1;
            end if;
        end if;
    end process p_2_HZ;

    p_1_HZ : process (clk) is
    begin
        if (rising_edge(clk)) then
            if (count1HZ = (c_CNT_1HZ - 1)) then -- -1 since counter starts at 0
                toggle1HZ <= not toggle1HZ;      -- Da la vuelta
                count1HZ <= 0;
            else
                count1HZ <= count1HZ + 1;
            end if;
        end if;
    end process p_1_HZ;

    -- creeate a multiplexor 
    w_LED_SELECT <= toggle25HZ when (sw0 = '0' and sw1 = '0') else
                    toggle5HZ  when (sw0 = '0' and sw1 = '1') else
                    toggle2HZ  when (sw0 = '1' and sw1 = '0') else
                    toggle1HZ;
                    
    led_drive <= w_LED_SELECT and en;

end Arch_LEDs;
