-- premenna typu INT dostala hodnotu typu double 4
require "ifj21"
global a : integer = 5.5
function main() : integer
    local n : integer = 3
    local n1 : integer = n
	local n2 : integer = n*n1 
    write(n,n1,n2,a)
end
main()