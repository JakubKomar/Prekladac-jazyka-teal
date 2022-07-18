-- good definition function 0
require "ifj21"
global a:function(integer):integer

function a(i:integer):integer


    return i
end

local b:integer=a(5)
write(b)