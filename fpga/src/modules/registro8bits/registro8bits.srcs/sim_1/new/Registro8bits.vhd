
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Registro8bits is
    generic (n : POSITIVE := 8);
    port (Q   : out STD_LOGIC_VECTOR ((n-1) downto 0);
          D   : in  STD_LOGIC_VECTOR ((n-1) downto 0);
          rst : in  STD_LOGIC;
          clk : in  STD_LOGIC);
end Registro8bits;


architecture Arch_Registro8bits of Registro8bits is
begin
    clk_proc : process (clk)
    begin
        if (rising_edge(clk)) then
            if rst = '1' then
                Q <= (others => '0'); -- reset 
            else
                Q <= D;
            end if;
        end if;
    end process;

end Arch_Registro8bits;
