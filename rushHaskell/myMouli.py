import os
from random import seed
from random import randint

seed(randint(0,1000))

lst = []
alreadySort = [1,2,3,4,5,6]
simpleSort = [4,5,7,-0,4,1,4]

onlyNeg = [-5,-100,-4,-70,50,-5,-5,-10]
onlyPos = [10,12,70,1,50,40,30,70,1,5]
onlyOne = [1]

simpleList = "1 2 3 4 5 6 7 8 9 10"

lstGood = [alreadySort, simpleSort, onlyNeg, onlyPos, onlyOne]
lstWrong = ["1 2 4 8 7 -5 l", "1 4 -8 po 4", "4 5 7 8 4 --4 1"]
ko1 = ["sa sb", "1 2 3", "KO"]
ko2 = ["sa sa", "1 2 3", "OK"]
ko3 = ["sb sb", "1 2 3", "OK"]
ko4 = ["sb sb", "1 2 3", "OK"]
ko5 = ["ra rra", "1 2 3", "OK"]
ko6 = ["pb pb rb rb pa pa ", "1 2 3", "OK"]
ko7 = ["pb pa pb sa", "1 2 3 4 5", "KO"]
ko8 = ["pb rrr rrr rr rr pa", "1 2 3 4 5", "OK"]
ko9 = ["pb rrr rrr rr rr pa", "1 2 3 4 5", "OK"]
ko10 = ["pb rrr rrr rr rr pa", "1 2 3 4 5", "OK"]
ko10 = ["pb sa sb sc pb pb pb pb pb pb pb pb pa pa pa pa pa pa pa pa rrb rrb rrr rr pa pb pb sb sb pa", "1 2 3 4 5", "KO"]
ko11 = ["pb sa sb sc pb pb pb pb pb pb pb pb pa pa pa pa pa pa pa pa rrb rrb rrr rr pa pb pb sb sb pa pa", "1 2 3 4 5", "OK"]

lstKO = [ko1, ko2, ko3, ko4, ko5, ko6, ko7, ko8, ko9, ko10, ko11]

def expectOK():
    for elem in lstGood:
        relem = int_arr_to_str(elem)
        trace = get_trace(relem)
        if trace != "OK\n":
            print("KO on" + relem)
        else:
            print("\033[92mOK\033[0m on " + relem)

def expect84():
    for elem in lstWrong:
        trace = get_trace_ret(elem)
        if trace == 0:
            print("KO on" + elem)
        else:
            print("\033[92mOK\033[0m on " + elem)

def expectKO():
    for elem in lstKO:
        trace = get_trace_custom(str(elem[0]), str(elem[1]))
        if not trace.startswith(elem[2]):
            print("KO on " + elem[1] + " with " + elem[0])
        else:
            print("\033[92mOK\033[0m on " + elem[1] + " with " + elem[0])

def int_arr_to_str(elem):
    return ' '.join({str(i) for i in elem})

def get_trace_custom(op, lst):
    os.system("echo "+ op + " | ../pushswap_checker " + lst + " > trace")
    try:
        text_file = open("trace", "r")
        data = text_file.read()
        text_file.close()
    except:
        exit(84)
    os.system("rm trace")
    return data

def get_trace(lst):
    os.system("./push_swap " + lst + "|" + " ../pushswap_checker " + lst + " > trace")
    try:
        text_file = open("trace", "r")
        data = text_file.read()
        text_file.close()
    except:
        exit(84)
    os.system("rm trace")
    return data

def get_trace_ret(lst):
    return os.system("./push_swap " + lst + "|" + " ../pushswap_checker " + lst + " > trace")

print("Expect OK\n")
expectOK()
print("\n")

print("Expect KO\n")
expectKO()
print("\n")

print("Expect 84\n")
expect84()
