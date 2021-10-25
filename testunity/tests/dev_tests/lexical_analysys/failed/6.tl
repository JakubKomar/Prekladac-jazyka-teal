-- Bad escape sequence 1
require "ifj21"
function main() -- uzivatelska funkce bez parametru
    local a : string = "daw\256daw"
end
main() -- prikaz hlavniho tela programu