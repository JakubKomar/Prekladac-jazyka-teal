-- last tests... 0
require "ifj21"

local i   :  integer =9
local func2:function(integer):integer
function func(i:integer):integer
    i=func2(i)
    return i
end
function func2(i:integer):integer
    global b:integer=5
    return i*2+b
end

while(i>0)do
    global a:integer=func(i)
    write(a,"\n")
    i=i-1
end

func(5)