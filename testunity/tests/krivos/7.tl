-- operand priority 0
require "ifj21"

global i : integer = 10
global j : integer = 50
global k : number = i + j / j - 0.2

write(k, "\n")