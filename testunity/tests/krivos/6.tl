-- operand priority 0
require "ifj21"

global s : string = "Hello"
global i : integer

i = #(s..s) / 2
write(i)