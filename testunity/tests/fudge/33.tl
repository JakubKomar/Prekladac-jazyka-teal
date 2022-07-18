-- params function test 0
require "ifj21"

function func(a:integer,b:number,c:integer,d:string,e:string) 
    write("nil",b,c,"nil",e)
end

func(nil,2.5,99921, nil ,"slovo")