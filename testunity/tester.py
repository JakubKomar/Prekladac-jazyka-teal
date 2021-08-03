#!/usr/bin/env python3

#autor: Jakub Komarek
#login: xkomar33
#tester překladače IFJ-2021

import os

testFolder="./tests/"   
testTypeEnd="go"        #koncovka testovaných souborů
programToTest="./../ifj21"
ifjCode="./programs/ifjCode"     #strojový interpret cílového jazyka
ifj21="./programs/ifj21interpret"         #interpret počátečního jazyka  
makefile="./../makefile"

tests=[]

def main():
    programInit()
    initTests()
def programInit():
    if(not os.path.exists(ifjCode) ):
        error("ifjCode interpret is not existing")
    if(not os.path.exists(ifj21)):
        error("ifj21 interpret is not existing")
    if(not os.path.exists(programToTest)):
        if(not os.path.exists(makefile)):
            error("program not existing and cant be made by makefile")
        else:
            print("testing program is not existing, trying makefile")
            os.system("cd .. && make")
            if(not os.path.exists(programToTest)):
                error("testing program cant be made")
def initTests():
    fname = []
    for root,d_names,f_names in os.walk(testFolder):
       for f in f_names:
           tests.append(test(os.path.join(root, f),f))

    print(tests)
def error(text="Unknown error",retCode=-1):
    print(text)
    exit(retCode)
class test(object):
    name=None
    path=None
    exRetCode=0
    RetCode=0
    def __init__(self,Path,Name):
        self.path=Path
        self.name=Name

    def startTest(self):

        return
    def __repr__(self):
        return "<Test - name: %-15s, path: %-60s ,expected return code: %-3d,return code: %-3d>\n" % (self.name, self.path, self.exRetCode,self.RetCode)



main()