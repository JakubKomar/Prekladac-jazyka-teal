-- ret params function test 0
require "ifj21"

function func(a:integer,b:string,c:number):integer,string,string

    return a,"ahoj","ahoj"
end

local a:integer=95,85,45+55,"ahoj"

local b:string

local c:string

a,b=func(2,"zmrd",2)
write(a,b)