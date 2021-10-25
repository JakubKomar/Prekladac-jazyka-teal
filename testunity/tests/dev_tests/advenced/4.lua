-- zahazovani ret params 0
require "ifj21"
function fooo():number,string,number,string
    return 95+45+32/5,"hello",32.9/0.4
end

local a:number
local b:string
local c:number=fooo()
write(c)
a,b,c=fooo()
write(a,b,c)
a,b=fooo()
write(a,b)