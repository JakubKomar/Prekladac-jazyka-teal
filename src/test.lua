-- ret params function test 0
require "ifj21"

local s:string="hello world"
local sub:string=substr(s, 5, 9)
local o:integer=ord(s,4)
write(sub, "\n", o, "\n")