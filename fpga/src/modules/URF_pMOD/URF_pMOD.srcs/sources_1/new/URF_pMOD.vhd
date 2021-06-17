
LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ENTITY pmod_ultrasonic_range_finder IS
  GENERIC(
    clk_freq   :  INTEGER := 50);                     --frequency of system clock in MHz
  PORT(
    clk        :  IN   STD_LOGIC;                     --system clock
    reset_n    :  IN   STD_LOGIC;                     --asynchronous active-low reset
    sensor_pw  :  IN   STD_LOGIC;                     --pulse width (PW) input from ultrasonic range finder
    distance   :  OUT  STD_LOGIC_VECTOR(7 DOWNTO 0)); --binary distance output (inches)
END pmod_ultrasonic_range_finder;

ARCHITECTURE behavior OF pmod_ultrasonic_range_finder IS
  SIGNAL sensor_pw_prev  :  STD_LOGIC;  --previous value of the sensor's pulse width signal
BEGIN
  PROCESS(clk,reset_n)
    VARIABLE sub_inch_counter  :  INTEGER := 0;  --counts until time equivalent to 1 inch is reached (147us)
    VARIABLE inch_counter      :  INTEGER := 0;  --counts number of inches that have been reached
  BEGIN
    IF(reset_n = '0') THEN                             --asynchronous reset
      sub_inch_counter := 0;                             --clear sub-inch counter
      inch_counter := 0;                                 --clear inch counter
      distance <= (OTHERS => '0');                       --clear distance output register
    ELSIF(clk'EVENT AND clk = '1') THEN                --rising system clock edge  
      sensor_pw_prev <= sensor_pw;                       --store previous value of pulse width input
      IF(sensor_pw = '1') THEN                           --pulse width input is high
        IF(sub_inch_counter < 147*clk_freq) THEN           --time is less than 147us
          sub_inch_counter := sub_inch_counter + 1;          --increment sub-inch counter
        ELSE                                               --time is equal to 147us
          sub_inch_counter := 0;                             --clear sub-inch counter
          inch_counter := inch_counter + 1;                  --increment inch counter
        END IF;
      END IF;
      IF(sensor_pw_prev = '1' AND sensor_pw = '0') THEN  --falling edge of pulse width signal
        --typecast the integer inch counter into a standard logic vector binary number for output
        distance <= std_logic_vector(to_unsigned(inch_counter,distance'LENGTH));
        --clear counters for next measurement
        sub_inch_counter := 0;
        inch_counter := 0;
      END IF;
    END IF;
  END PROCESS;
END behavior;
