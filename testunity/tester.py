#!/usr/bin/env python3

#autor: Jakub Komarek
#login: xkomar33
#tester překladače IFJ-2021

import os
import re
testFolder="./tests/"   
testTypeRegex=r"\.go$"       #koncovka testovaných souborů
programToTest="./../ifj21"
ifjCode="./programs/ifjCode"     #strojový interpret cílového jazyka
ifj21="./programs/ifj21interpret"         #interpret počátečního jazyka  
makefile="./../makefile"

tests=[]

def main():
    programInit()
    initTests()
    startTesting()
    printResults()
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
def startTesting():
    for test in tests:
        test.startTest()
def printResults():
    counterPassed=0
    counterFailed=0
    for test in tests:
        if test.pased==True:
            counterPassed+=1
        else:
            counterFailed+=1
    print("Test results:")
    print("passed/failed:\t"+str(counterPassed)+"/"+str(counterFailed))
    print("Failed:")
    for test in tests:
        if test.pased==False:
            print(test)
    print("Passed:")
    for test in tests:
        if test.pased==True:
            print(test)

def initTests():
    fname = []
    for root,d_names,f_names in os.walk(testFolder):
       for f in f_names:
           if(re.search(testTypeRegex,f, re.IGNORECASE)):
               try:
                   tests.append(test(os.path.join(root, f),f))
               except:
                   pass
def error(text="Unknown error",retCode=-1):
    print(text)
    exit(retCode)
class test(object):
    name=None
    path=None
    pased=None
    exRetCode=0
    RetCode=0
    def __init__(self,path,Name):
        self.path=path
        f = open(path, "r")
        if f==None:
            raise FileExistsError
        info=f.readline()
        f.close()
        if re.match(r"^//.*\d{1,}$",info):
            self.exRetCode=int(re.findall(r"\d{1,}$",info)[0])
        else:
            self.exRetCode=0
        self.name=Name
        self.pased=False
    def startTest(self):
        #to do - spuštění testu a vyhodnocení
        return
    def __repr__(self):
        return "<Test - name: %-25s, path: %-60s ,expected return code: %-3d,return code: %-3d>" % (self.name, self.path, self.exRetCode,self.RetCode)



main()