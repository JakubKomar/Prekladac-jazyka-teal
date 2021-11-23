-- ret params function test 0
require "ifj21"

global func:function(integer,number):number,integer,string,number
function func(a:integer,b:number):number,integer,string,number
    write(a,b)
    return a,a,"ahoj",32.95
end

local a:number
local b:number
local c:string
local d:number
a,b,c,d=func(1,25.6)
write(a,b,c,d)