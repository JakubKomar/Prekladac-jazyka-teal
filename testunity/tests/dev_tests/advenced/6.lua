-- prekryvani madnes 0
require "ifj21"

function fooo():number,string,number,string
    return 95+45+32/5,"hello",32.9/0.4
end

local a:integer=5
write(a)
if 1 then
    local a:integer=9
    local b:integer=2
    write(a)
    while b>0 do
        local a:integer=9595
        write(a)
        if b==2 then
            local a:number=95
            write(a)
            local b:string
            local c:number=fooo()
            write(c)
            a,b,c=fooo()
            write(a,b,c)
            a,b=fooo()
            write(a,b)
        else
            local a:integer=95
            write(a)
        end
        write(a)
        b=b-1
    end
end
write(a)