-- integer/float 0
require "ifj21"

global i : integer = 50

function foo()
    local j: number = 2.5
    write(i/j)
end 
foo()
