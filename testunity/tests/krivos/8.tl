-- operand priority 0
require "ifj21"

global i : integer = 10
global j : integer = 50

if( i + j // j - 1 == i) then
    write("nice\n")
else 
    write("not nice\n")
end