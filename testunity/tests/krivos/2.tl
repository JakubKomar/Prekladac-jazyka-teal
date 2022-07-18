-- integer/float 0
require "ifj21"

global i : integer = 51

function foo()
    local j: number = 2.5
    write(i/j)
end 
foo()
