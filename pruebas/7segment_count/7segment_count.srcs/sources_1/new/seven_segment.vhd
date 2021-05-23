


-- We have four (4) 7-segment displays
-- We're gonna count up every second and show it on different
-- displays
-- We have to refresh each display every x milliseconds
-- We have to choose which display (3 to 0) to use each time

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity seven_segment is
    port (clk   : in  STD_LOGIC;
          rst   : in  STD_LOGIC;
          disp_select    : out STD_LOGIC_VECTOR (3 downto 0);
          disp_segments  : out STD_LOGIC_VECTOR (6 downto 0));
end seven_segment;


architecture Arch_seven_segment of seven_segment is
    signal one_s_counter : STD_LOGIC_VECTOR (27 downto 0);
    signal one_s_enable  : STD_LOGIC;
    signal displayed_dig : STD_LOGIC_VECTOR (15 downto 0);
    signal LED_BCD       : STD_LOGIC_VECTOR (3 downto 0);
    signal refresh_count : STD_LOGIC_VECTOR (19 downto 0);
    signal LED_counter   : STD_LOGIC_VECTOR (1 downto 0);
begin
    process (LED_BCD)
    begin
        case LED_BCD is
            when "0000" => disp_segments <= "0000001"; -- 0
            when "0001" => disp_segments <= "1001111"; -- 1
            when "0010" => disp_segments <= "0010010"; -- 2
            when "0011" => disp_segments <= "0000110"; -- 3
            
            when "0100" => disp_segments <= "1001100"; -- 4
            when "0101" => disp_segments <= "0100100"; -- 5
            when "0110" => disp_segments <= "0100000"; -- 6
            when "0111" => disp_segments <= "0001111"; -- 7
            
            when "1000" => disp_segments <= "0000000"; -- 8
            when "1001" => disp_segments <= "0000100"; -- 9
            when "1010" => disp_segments <= "0000010"; -- a
            when "1011" => disp_segments <= "1100000"; -- b
            
            when "1100" => disp_segments <= "0110001"; -- c
            when "1101" => disp_segments <= "1000010"; -- d
            when "1110" => disp_segments <= "0110000"; -- e
            when "1111" => disp_segments <= "0111000"; -- f
        end case;
    end process;

    process (clk, rst)
    begin
        if (rst = '1') then
            refresh_count <= (others => '0');
        elsif (rising_edge(clk)) then
            refresh_count <= refresh_count + 1;
        end if;
    end process;
    LED_counter <= refresh_count(19 downto 18);

    process (LED_counter)
    begin
        case LED_counter is
        when "00" =>
            disp_select <= "0111"; -- Led1 ON, others OFF
            LED_BCD <= displayed_dig(15 downto 12);
        when "01" =>
            disp_select <= "1011"; -- Led2 ON, others OFF
            LED_BCD <= displayed_dig(11 downto 8);
        when "10" =>
            disp_select <= "1101"; -- Led3 ON, others OFF
            LED_BCD <= displayed_dig(7 downto 4);
        when "11" =>
            disp_select <= "1110"; -- Led4 ON, others OFF
            LED_BCD <= displayed_dig(3 downto 0);
        end case;
    end process;
    
    process (clk, rst)
    begin
        if (rst = '1') then
            one_s_counter <= (others => '0');
        elsif (rising_edge(clk)) then
            if (one_s_counter >= x"5F5E0FF") then
                one_s_counter <= (others => '0');
            else
                one_s_counter <= one_s_counter + "0000001";
            end if;
        end if;
    end process;
    one_s_enable <= '1' when one_s_counter = x"5F5E0FF" else '0';
    
    process (clk, rst)
    begin
        if (rst = '1') then
            displayed_dig <= (others => '0');
        elsif (rising_edge(clk)) then
            if (one_s_enable = '1') then
                displayed_dig <= displayed_dig + x"0001";
            end if;
        end if;
    end process;

end Arch_seven_segment;
