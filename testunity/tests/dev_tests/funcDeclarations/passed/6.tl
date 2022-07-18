-- ret params function test 0
require "ifj21"


global func:function(integer,number):number,integer,string,integer
function func(a:integer,b:number):number,integer,string,integer
    write(a,b)
    return 1+1,a
end
local a:number
local b:integer
local c:string
local d:number
a,b,c,d=func(1,25.6)
write(a,b)