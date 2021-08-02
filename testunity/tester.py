#!/usr/bin/env python3

#autor: Jakub Komarek
#login: xkomar33
#tester překladače IFJ-2021

import os

testFolder="./tests/"
testTypeEnd="go"
programToTest="./../program.exe"
ifjCode="./ifjCode"
ifj21="./ifj21"
makefile="./../makefile"

tests=[]

def main():
    programInit()
    initTests()
def programInit():
    if( not os.path.exists(ifjCode) ):
        error("ifjCode interpret is not existing")
    if(not os.path.exists(ifj21)):
        error("ifj21 interpret is not existing")
    if(os.path.exists(ifj21)):
        print("testing program is not existing, trying makefile")
        None
    os.path.exists(ifj21)
    os.path.exists(programToTest)
    return
def initTests():
    fname = []
    for root,d_names,f_names in os.walk(testFolder):
       for f in f_names:
           tests.append(test(os.path.join(root, f),f))

    print(tests)
    return
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