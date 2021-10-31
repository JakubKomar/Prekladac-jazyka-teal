-- ret params function test 0
require "ifj21"

local s:string=reads()
local i:integer=readi()
local j:integer=reads()

local sub:string=substr(s, i, j)
write(sub, "\n")