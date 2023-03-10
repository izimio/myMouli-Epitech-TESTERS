import os
from random import seed
from random import randint
import sys

def getArgs(args):
    try:
        return int(args[1])
    except:
        return 100


seed(randint(0,1000))

lst = []
looper = getArgs(sys.argv)

def getRand(min, max):
    return randint(min, max)

def generateRuleParam():
    rand = getRand(1, 1000)
    rule = ""
    if rand % 2  == 0:
        rule = "30"
    elif rand % 3 == 0:
        rule = "90"
    else:
        rule = "110"
        
    ret = "--rule " + rule + " "
    return ret

def generateParam(param, min, max):
    rand = getRand(min, max)
    return "--" + param + " " + str(rand) + " "
    
def generateAllParams():
    ret = ""
    ret += generateRuleParam()
    ret += generateParam("lines", 0, 500)
    ret += generateParam("start", 0, 500)
    ret += generateParam("window", 0, 250)
    ret += generateParam("move", -50, 50)
    return ret
    
cmd = (generateAllParams())

def diff_files(cmd):
    ret = os.system("diff trace/trueTrace trace/yourTrace > trace/diff")
    if ret == 0:
        print("\033[92mOK\033[0m" + " on " + cmd)
    else:
        print("\033[91mKO\033[0m" + " on " + cmd)
        print("Check diff file for info")
    return ret
        
def do_in_file(cmd):
    os.system("./refBin " + cmd + " > " + "trace/trueTrace")
    os.system("./wolfram " + cmd + " > " + "trace/yourTrace")

for _ in range(looper):
    cmd = generateAllParams()
    do_in_file(cmd)
    if diff_files(cmd) != 0:
        break
        