-- multiple returns 0
require "ifj21"

function concat (x : string, y : string) : string, integer
    return x .. y, 0 end
function main()
    local x : string = reads()
    x, ret = concat( x , "svete\n")
    if(ret == 0) then
        write(x)
    end
end
main()