
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity msgDecod is
    port (first4  : in  STD_LOGIC_VECTOR (7 downto 4);
          msgKind : out STD_LOGIC_VECTOR (1 downto 0));
end msgDecod;

architecture Arch_msgDecod of msgDecod is
begin
    process
    begin
        if (first4(7) = '1') then
            msgKind <= "00"; -- umbral Luz
        elsif (first4(7) = '0' and first4(6) = '1') then
            msgKind <= "01"; -- umbral tmp
        elsif (first4(7) = '0' and first4(6) = '0' and first4(5) = '1') then
            msgKind <= "10"; -- persianas
        elsif (first4(7) = '0' and first4(6) = '0' and first4(5) = '0' and first4(4) = '1') then
            msgKind <= "11"; -- Ambient
        end if;
    end process;
end Arch_msgDecod;
