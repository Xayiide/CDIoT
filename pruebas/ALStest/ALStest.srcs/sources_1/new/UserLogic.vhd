
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity UserLogic is
    port (clock : in  STD_LOGIC;
          reset : in  STD_LOGIC;
          umiso : in  STD_LOGIC;
          usclk : BUFFER STD_LOGIC;
          uss_n : BUFFER STD_LOGIC_VECTOR (0 downto 0);
          als_d : out STD_LOGIC_VECTOR (7 downto 0));
end UserLogic;

architecture Arch_UserLogic of UserLogic is
    component ALS_pMOD is
        GENERIC(
            spi_clk_div :   INTEGER := 13);  -- spi_clk_div = clk/8 (answer rounded up, clk in MHz) (13 -> 100MHz)
        PORT(
            clk         :   IN      STD_LOGIC;                          --system clock
            reset_n     :   IN      STD_LOGIC;                          --active low reset
            miso        :   IN      STD_LOGIC;                          --SPI master in, slave out
            sclk        :   BUFFER  STD_LOGIC;                          --SPI clock
            ss_n        :   BUFFER  STD_LOGIC_VECTOR(0 DOWNTO 0);       --SPI slave select
            als_data    :   OUT     STD_LOGIC_VECTOR(7 DOWNTO 0));      --ambient light sensor data
    end component ALS_pMOD;
    
    constant c_CNT_1HZ : natural := 50000000;
    signal count1HZ    : natural range 0 to c_CNT_1HZ;
    signal light_data  : STD_LOGIC_VECTOR (7 downto 0);
  
begin
    als_to_user : ALS_pMOD
    generic map (spi_clk_div => 13)
    port map(clk      => clock,
             reset_n  => reset,
             als_data => light_data,
             miso     => umiso,
             sclk     => usclk,
             ss_n     => uss_n);
             
    process (clock)
    begin
        if (rising_edge(clock)) then
            if (count1HZ = (c_CNT_1HZ - 1)) then
                count1HZ <= 0;
                als_d <= light_data;
            else
                count1HZ <= count1HZ + 1;
            end if;
        end if;
    end process;
end Arch_UserLogic;
