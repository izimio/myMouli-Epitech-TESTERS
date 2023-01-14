import os
import sys

def getArgsLooper(args):
    try:
        return int(args[1])
    except:
        return 100

exclude = [True, True]
def getArgsExclude(args):
    for arg in args:
        if arg == "--noloop":
            exclude[0] = False
        if arg == "--nomouli":
            exclude[1] = False
            
looper = getArgsLooper(sys.argv)
getArgsExclude(sys.argv)

def mouli():
    if exclude[1]:
        print("=====> Starting myMouli.py <=====\n")
        os.system("python3 myMouli.py")
    if exclude[0]:
        print("=====> Starting loop.py <=====")
        os.system("python3 loop.py " + str(looper))
    
mouli()