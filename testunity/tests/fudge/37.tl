-- deleni nulovou konstantou  9
require "ifj21"
global a : number = 5
global b : number = 1
if a > 1 then
	b = a / 0
else
	b = a + 5
end
write(b)