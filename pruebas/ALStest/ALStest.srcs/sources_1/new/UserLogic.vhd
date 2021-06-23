
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity UserLogic is
    port (clock : in  STD_LOGIC;
          reset : in  STD_LOGIC;
          
          umiso : in  STD_LOGIC;
          usclk : BUFFER STD_LOGIC;
          uss_n : BUFFER STD_LOGIC_VECTOR (0 downto 0);
          
          urx   : in  STD_LOGIC; -- receive cable (pin)
          utx   : out STD_LOGIC; -- transmit cable (pin)
          
          rcv_d : out STD_LOGIC_VECTOR (7 downto 0);
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
    
    
    component UART is
        GENERIC(
            clk_freq  :  INTEGER    := 100_000_000;  --frequency of system clock in Hertz
            baud_rate :  INTEGER    := 9_600;      --data link baud rate in bits/second
            os_rate   :  INTEGER    := 16;          --oversampling rate to find center of receive bits (in samples per baud period)
            d_width   :  INTEGER    := 8;           --data bus width
            parity    :  INTEGER    := 1;           --0 for no parity, 1 for parity
            parity_eo :  STD_LOGIC  := '0');        --'0' for even, '1' for odd parity
        PORT(
            clk      :  IN   STD_LOGIC;                             --system clock
            reset_n  :  IN   STD_LOGIC;                             --ascynchronous reset
            tx_ena   :  IN   STD_LOGIC;                             --initiate transmission
            tx_data  :  IN   STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);  --data to transmit
            rx       :  IN   STD_LOGIC;                             --receive pin
            rx_busy  :  OUT  STD_LOGIC;                             --data reception in progress
            rx_error :  OUT  STD_LOGIC;                             --start, parity, or stop bit error detected
            rx_data  :  OUT  STD_LOGIC_VECTOR(d_width-1 DOWNTO 0);  --data received
            tx_busy  :  OUT  STD_LOGIC;                             --transmission in progress
            tx       :  OUT  STD_LOGIC);                            --transmit pin  
    end component UART;
    
    
    constant c_CNT_1HZ : natural := 50000000;
    signal count1HZ    : natural range 0 to c_CNT_1HZ;
    signal light_data  : STD_LOGIC_VECTOR (7 downto 0);
    signal send_data   : STD_LOGIC_VECTOR (7 downto 0);
  
    signal sendUART  : STD_LOGIC; -- tx_ena
    signal urx_busy  : STD_LOGIC;
    signal urx_error : STD_LOGIC;
    signal rcv_data  : STD_LOGIC_VECTOR (7 downto 0);
    signal utx_busy  : STD_LOGIC;
    
begin
    als_to_user : ALS_pMOD
    generic map (spi_clk_div => 13)
    port map(clk      => clock,
             reset_n  => reset,
             als_data => light_data,
             miso     => umiso,
             sclk     => usclk,
             ss_n     => uss_n);
    
    uart_to_user : UART
    generic map (clk_freq  => 100_000_000,
                 baud_rate => 9_600,
                 os_rate   => 16,
                 d_width   => 8,
                 parity    => 0,
                 parity_eo => '0')
    port map (clk      => clock,
              reset_n  => reset,
              tx_ena   => sendUART,
              tx_data  => send_data,
              rx       => urx,
              rx_busy  => urx_busy,
              rx_error => urx_error,
              rx_data  => rcv_d,
              tx_busy  => utx_busy,
              tx       => utx);
    
    
    process (clock)
    begin
        if (rising_edge(clock)) then
            if (count1HZ = (c_CNT_1HZ - 1)) then
                count1HZ <= 0;
                als_d <= light_data;
                send_data <= light_data;   
                sendUART <= '1';
            else
                count1HZ <= count1HZ + 1;
            end if;
        end if;
    end process;
end Arch_UserLogic;
