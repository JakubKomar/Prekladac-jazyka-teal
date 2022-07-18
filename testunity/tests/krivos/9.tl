-- operand priority 0
require "ifj21"

global i : string = "Hello "
global j : string = "world\n"

global k : number = #(i..j)
global l : number = #i + #j

write(k, " ", l, "\n")