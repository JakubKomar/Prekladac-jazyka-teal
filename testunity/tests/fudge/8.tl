-- premmena n dostane zakomentovanu hodnotu 6
require "ifj21"
global a : integer = 6
function main() : integer
    local n : integer = #a
    write(n,a)
end
main()