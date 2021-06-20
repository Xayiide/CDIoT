
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity UF_Persianas is
    port (msgKind : in  STD_LOGIC_VECTOR (1 downto 0);
          RX0     : in  STD_LOGIC;
          RX4     : in  STD_LOGIC;
          bitCtrlPers   : out STD_LOGIC;
          regEstadoPers : out STD_LOGIC);
end UF_Persianas;

architecture Arch_UF_Persianas of UF_Persianas is
begin
    process
    begin
        if (msgKind = "10") then
            if (RX4 = '0') then -- Persianas por control manual
                bitCtrlPers <= '1';
                regEstadoPers <= RX0;
            elsif (RX4 = '1') then -- Persianas Auto
                bitCtrlPers <= '0';
            end if;
        end if;
    end process;
end Arch_UF_Persianas;

-- Conectaremos bitCtrlPers al registro de control de las persianas (1 bit) que luego irá como
-- bit de control al multiplexor que controla quién escribe en el bit de estado de las persianas
-- Además conectaremos regEstadoPers al bit del registro de estado de las persianas
