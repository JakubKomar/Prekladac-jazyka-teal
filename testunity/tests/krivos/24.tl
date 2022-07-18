-- substr wrong arg test 0
require "ifj21"

global s : string = substr("Hello world", 5, 2)
write(s)