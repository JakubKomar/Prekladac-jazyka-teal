-- nested while 0
require "ifj21"

function foo(i: integer) : integer
    while i > 0 do
        while i > 1 do
            i = i - 1
            write(i)
        end
    end
end
foo(10)