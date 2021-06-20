
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity UF_UmbralLuz is
    port (msgKind : in  STD_LOGIC_VECTOR (1 downto 0);
          RXdat   : in  STD_LOGIC_VECTOR (6 downto 0);
          outDat  : out STD_LOGIC_VECTOR (6 downto 0));
end UF_UmbralLuz;

architecture Arch_UF_UmbralLuz of UF_UmbralLuz is
begin
    process
        variable lastDat : STD_LOGIC_VECTOR (6 downto 0) := "0100000";
    begin
        if (msgKind = "00") then
            lastDat := RXdat;
            outDat <= lastDat;
        else
            outDat <= lastDat; 
        end if;
    end process;

end Arch_UF_UmbralLuz;

-- outDat se conectará a los 7 bits más significativos del registro umbral de luz