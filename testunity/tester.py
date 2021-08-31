#!/usr/bin/env python3

#autor: Jakub Komarek
#login: xkomar33
#tester překladače IFJ-2021

import os
import re
import subprocess 
import argparse
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
    failReson=0
    def __init__(self,path,Name):
        self.path=path
        try:
            f = open(path, "r")
        except:
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
        try:
            output = subprocess.check_output(programToTest,stderr=subprocess.DEVNULL,timeout=1)
            if(self.exRetCode!=0):
                self.pased=False
                return
            #print(output)
            self.RetCode=0
            #to do-porovnání výstupů od vzorového interpretu
            expectedOutput=output
            if output==expectedOutput :
                self.pased=True
            else:
                self.pased=False
        except subprocess.CalledProcessError as grepexc:
            self.RetCode=grepexc.returncode
            if self.RetCode==self.exRetCode:
                self.pased=True
            else:
                self.pased=False
        except subprocess.TimeoutExpired:
            self.failReson=1

    def __repr__(self):
        return "<Test - name: %-25s, path: %-60s ,expected return code: %-3d,return code: %-3d,fail reson: %-2d>" % (self.name, self.path, self.exRetCode,self.RetCode,self.failReson)

parser = argparse.ArgumentParser(description='Tester pro ifj překaldač.')
parser.add_argument("-p", "--path",type=str,default=testFolder,
                    help="Path to tests")                   
args = parser.parse_args()
testFolder=args.path
main()