--  0
require "ifj21"

function foo(b:number,c:number):number
    local result:number
    if c==0 then
        return 
    else
        result=b/c
    end

    return result
end

write("\n1 cislo:")
local b:number =readn()
write("\n2 cislo:")
local c:number =readn()

local d:number =foo(b,c)
if d==nil then
    write("\nchyba")
else
    write("\nvysledek:",d)
end