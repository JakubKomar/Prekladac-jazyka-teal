-- operand priority 0
require "ifj21"

global s : string = "Hello\n"
global i : number

i = (#s + #s) / 5
write(i)