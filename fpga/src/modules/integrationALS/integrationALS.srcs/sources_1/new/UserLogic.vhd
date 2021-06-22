
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity UserLogic is
    port (i_clk    : in  STD_LOGIC;
          i_rst    : in  STD_LOGIC;
          i_ldat   : in  STD_LOGIC_VECTOR (7 downto 0);
          o_txen   : out STD_LOGIC;
          o_txdat  : out STD_LOGIC;
          o_txbusy : out STD_LOGIC);
end UserLogic;


architecture Arch_UserLogic of UserLogic is
    component ALS_pMOD is
        generic (
            spi_clk_div :   INTEGER := 13);
        port (
            clk         :   IN      STD_LOGIC;                          --system clock
            reset_n     :   IN      STD_LOGIC;                          --active low reset
            miso        :   IN      STD_LOGIC;                          --SPI master in, slave out
            sclk        :   BUFFER  STD_LOGIC;                          --SPI clock
            ss_n        :   BUFFER  STD_LOGIC_VECTOR(0 DOWNTO 0);       --SPI slave select
            als_data    :   OUT     STD_LOGIC_VECTOR(7 DOWNTO 0));      --ambient light sensor data
    end component;
    
    
    
begin
    -mapals : ALS_pMOD
        generic map (spi_clk_div <= 13)
        port map (clk <= i_clk,
                  reset_n <= i_rst,
                  miso <= );

end Arch_UserLogic;
