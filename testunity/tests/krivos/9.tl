-- operand priority 0
require "ifj21"

global i : string = "Hello "
global j : string = "world\n"

if( #(i..j) == #i + #j) then
    write("nice\n")
else 
    write("not nice\n")
end