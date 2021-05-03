
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity DistCalc is
    port ( clk   : in  STD_LOGIC;
           rst   : in  STD_LOGIC;
           pulse : in  STD_LOGIC;
           dist  : out STD_LOGIC_VECTOR (8 downto 0)); -- 9 bits distance signal
end DistCalc;

architecture Arch_DistCalc of DistCalc is

begin


end Arch_DistCalc;
