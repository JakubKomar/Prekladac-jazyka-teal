-- Typová nekompatibilita mezi návratovou hodnotou a odpovídající proměnnou pro její uložení vede nachybu 5
require "ifj21"

function a():integer

return 6
end
local b:string=a(5)