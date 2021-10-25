-- Typova nekompatibilita mezi navratovou hodnotou a odpovidajici promennou pro jeji ulozeni vede nachybu 5
require "ifj21"

function a():integer

return 6
end
local b:string=a(5)