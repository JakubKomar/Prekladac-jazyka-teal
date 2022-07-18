-- substr wrong arg test 8
require "ifj21"

global s : string = substr("Hello world", 5, nil)
write(s)