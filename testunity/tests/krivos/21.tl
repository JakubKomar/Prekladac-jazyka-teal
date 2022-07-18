-- tointeger nil test 0
require "ifj21"

global j : number = nil
global i : integer = tointeger(j)
write(i)
