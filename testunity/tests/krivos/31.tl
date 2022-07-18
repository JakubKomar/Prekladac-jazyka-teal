-- ord arg test 0
require "ifj21"

global s : string = "Hello world"
global l : integer = #s + 1
global i : integer = ord(s, l)
write(i)