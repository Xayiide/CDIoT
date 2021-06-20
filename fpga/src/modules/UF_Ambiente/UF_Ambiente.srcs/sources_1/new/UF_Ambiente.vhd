----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 06/20/2021 04:03:35 PM
-- Design Name: 
-- Module Name: UF_Ambiente - Arch_UF_Ambiente
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity UF_Ambiente is
    port (msgKind : in STD_LOGIC_VECTOR (1 downto 0);
          RX3     : in STD_LOGIC;
          RX2     : in STD_LOGIC;
          RX0     : in STD_LOGIC;
          bitCtrlAire    : out STD_LOGIC;
          bitCtrlCalef   : out STD_LOGIC;
          regEstadoAire  : out STD_LOGIC;
          regEstadoCalef : out STD_LOGIC);
end UF_Ambiente;

architecture Arch_UF_Ambiente of UF_Ambiente is
begin
    process
    begin
        if    (RX3 = '0' and RX2 = '0') then -- Aire
            bitCtrlAire    <= '1';
            regEstadoAire  <= RX0;
            if (RX0 = '1') then
                regEstadoCalef <= '0';
            end if;
        elsif (RX3 = '0' and RX2 = '1') then -- Calef
            bitCtrlCalef   <= '1';
            regEstadoCalef <= RX0;
            if (RX0 = '1') then
                regEstadoAire <= '0';
            end if;
        elsif (RX3 = '1' and RX2 = '0') then -- tmpAuto
            bitCtrlCalef <= '0';
            bitCtrlAire  <= '0';
        end if;
    end process;
end Arch_UF_Ambiente;

-- Conectamos bitCtrlAire y bitCtrlTemp a sus registros de 1 bit correspondientes que luego se conectarán como
-- bit de control al multiplexor que da entrada al registro de estado (bit de aire o bit de calefacción)
-- Conectamos regEstadoCalef y regEstadoAire a los registros de calefacción o aire