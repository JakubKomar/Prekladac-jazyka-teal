-- 0
require "ifj21"

function foo() : string
    local str : string = reads()
    return str
end

global str1 : string = foo()
global str2 : string = "world\n"

write(str1, str2)
