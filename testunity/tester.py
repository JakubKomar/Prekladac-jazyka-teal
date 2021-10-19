#!/usr/bin/env python3

#autor: Jakub Komarek
#login: xkomar33
#tester překladače IFJ-2021

import os
import sys
import re
import subprocess 
import argparse
testFolder="./tests/"   
testTypeRegex=r"\.lua$"       #koncovka testovaných souborů
programToTest="./../ifj21"
ifjCode="./ic21int"     #strojový interpret cílového jazyka
ifj21="./ic21int"         #interpret počátečního jazyka  
makefile="./../makefile"
f_noOut=False
f_scannerOnly=False
tests=[]

# progress bar převzat z :https://gist.github.com/vladignatyev/06860ec2040cb497f0f3
def progress(count, total, status=''):
    bar_len = 96
    filled_len = int(round(bar_len * count / float(total)))

    percents = round(100.0 * count / float(total), 1)
    bar = '=' * filled_len + '-' * (bar_len - filled_len)

    sys.stdout.write('[%s] %s%s ...%s\r' % (bar, percents, '%', status))
    sys.stdout.flush() 

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
    i=0
    for test in tests:
        progress(i, len(tests)-1, status='Testing')
        test.startTest()
        i+=1


def printResults():
    counterPassed=0
    counterFailed=0
    for test in tests:
        if test.pased==True:
            counterPassed+=1
        else:
            counterFailed+=1
    print("\n\nTest results:")
    print("passed/failed: \033[0;32m"+str(counterPassed)+"\033[0m/\033[0;31m"+str(counterFailed)+"\033[0m\n")
    if(counterFailed):
        print("\033[0;31mFailed:\033[0m")
        for i in range(98):
            print("_",end="")
        print("\n%-60s  | %-3s |%-5s| %-20s |" % (" Path ", "ret","E.ret","Fail reason"))
        for i in range(98):
            print("_",end="")
        print("")
        for test in tests:
            if test.pased==False:
                print(test)
        for i in range(98):
            print("_",end="")
        print("")
    if(counterPassed):
        print("\033[0;32mPassed:\033[0m")
        for i in range(98):
            print("_",end="")
        print("\n%-60s  | %-3s |%-5s| %-20s |" % (" Path ", "ret","E.ret","Fail reason"))
        for i in range(98):
            print("_",end="")
        print("")
        for test in tests:
            if test.pased==True:
                print(test)
        for i in range(98):
            print("_",end="")
        print("")

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
    failReson=""

    def __init__(self,path,Name):
        self.path=path
        try:
            f = open(path, "r")
        except:
            raise FileExistsError
        info=f.readline()
        f.close()
        if re.match(r"^--.*\d{1,}$",info):
            self.exRetCode=int(re.findall(r"\d{1,}$",info)[0])
        else:
            self.exRetCode=0
        self.name=Name
        self.pased=False

    def startTest(self):
        try:
            if f_scannerOnly:
                output = subprocess.check_output(programToTest+" -d"+" -s"+" 2>/dev/null <"+self.path,shell=True,stderr=subprocess.DEVNULL,timeout=1)
            else:
                output = subprocess.check_output(programToTest+" 2>/dev/null <"+self.path,shell=True,stderr=subprocess.DEVNULL,timeout=1)
            if(self.exRetCode!=0):
                self.pased=False
                return
            self.RetCode=0
            if not f_noOut:
                #to do-porovnání výstupů od vzorového interpretu
                expectedOutput=output
                if output==expectedOutput :
                    self.pased=True
                else:
                    self.pased=False
            else:
                self.pased=True
        except subprocess.CalledProcessError as grepexc:
            self.RetCode=grepexc.returncode
            if self.RetCode==self.exRetCode:
                self.pased=True
            else:
                self.pased=False
                self.failReson="wrong return code"
        except subprocess.TimeoutExpired:
            self.pased=False
            self.failReson="time out"

    def __repr__(self):
        return "<Test - name: %-25s, path: %-60s ,expected return code: %-3d,return code: %-3d,fail reson: %-2d>" % (self.name, self.path, self.exRetCode,self.RetCode,self.failReson)

    def __str__(self):
        return " %-60s | %-3d | %-3d | %-20s |" % (self.path, self.RetCode,self.exRetCode,self.failReson)


parser = argparse.ArgumentParser(description='Tester pro ifj překaldač.')
parser.add_argument("-p", "--path",type=str,default=testFolder,help="Path to tests")    
parser.add_argument("-s",action="store_true", help="Scanner only mod")   
parser.add_argument("-o", action="store_true",help="Dont compere outputs") 

args = parser.parse_args()
f_noOut=args.o 
f_scannerOnly=args.s 

testFolder=args.path
main()