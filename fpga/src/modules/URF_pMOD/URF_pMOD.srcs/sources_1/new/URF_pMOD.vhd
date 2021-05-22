
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;


entity URF_pMOD is
    generic (clk_freq : INTEGER := 50); -- in MHz
    port (clk       : in  STD_LOGIC;                     -- System clock
          rst       : in  STD_LOGIC;                     -- Async active-low
          sensor_pw : in  STD_LOGIC;                     -- PW input from sensor
          distance  : out STD_LOGIC_VECTOR(7 downto 0)); -- Binary distance output
end URF_pMOD;


architecture Arch_URF_pMOD of URF_pMOD is
    signal sensor_pw_prev : STD_LOGIC;
begin
    process (clk, rst)
        variable pw_counter : INTEGER := 0;
        variable inch_counter     : INTEGER := 0;
    begin
        if (rst = '0') then
            pw_counter   := 0;
            inch_counter := 0;
            distance <= (others => '0');
        elsif (clk'event and clk = '1') then
            sensor_pw_prev <= sensor_pw;
            if (sensor_pw = '1') then
                if (pw_counter < (147 * clk_freq)) then
                    pw_counter := pw_counter + 1;
                else
                    pw_counter := 0;
                    inch_counter := inch_counter + 1;
                end if;
            end if;
            if (sensor_pw_prev = '1' and sensor_pw = '0') then
                distance <= std_logic_vector(to_unsigned(inch_counter, distance'LENGTH));
                pw_counter   := 0;
                inch_counter := 0;
            end if;
        end if;
    end process;
end Arch_URF_pMOD;
