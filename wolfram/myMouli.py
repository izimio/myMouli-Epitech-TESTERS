import os
from random import seed
from random import randint

seed(randint(0,1000))

lst = []

## Error Rule
rule_err1= "---rule 110 --lines 1"
rule_err2= "rule 110 --lines 1"
rule_err3 = "-rule 110 --lines 1"
rule_err4 = "--rule 3O --lines 1"

rule_tests = [rule_err1, rule_err2, rule_err3, rule_err4]

## Error Lines
lines_err1 = " --rules 30 --lines 10A"
lines_err2 = "--rules 90 --lines -1"
lines_err3 = "--rules 110 --lines "

lines_tests = [lines_err1, lines_err2, lines_err3]

## Error Start

start_err1 = "--rules 30 --lines 10 --start 10A"
start_err2 = "--rules 90 --lines 10 --start -1"
start_err3 = "--rules 90 --lines 10 --start"

start_tests = [start_err1, start_err2, start_err3]

## error Window

window_err1 = "--rules 30 --lines 10 --window 10A"
window_err2 = "--rules 90 --lines 10 --window -1"
window_err3 = "--rules 90 --lines 10 --window"

window_tests = [window_err1, window_err2, window_err3]

## Error Move

move_err1 = "--rules 30 --lines 10 --move 10A"
move_err2 = "--rules 90 --lines 10 --move"

move_tests = [move_err1, move_err2]

## Error Tricky

tricky_err1 = ""

tricky_tests = [tricky_err1]


def do_in_file(cmd):
   ret = os.system("./wolfram " + cmd + " > " + "trace/trueTrace")
   if ret == 0:
       print_red("KO" + " on " + cmd)
   else:
       print_green("OK" + " on " + cmd)
       

def test_battery(tests):
    for test in tests:
        do_in_file(test)
    print("")
        
def print_green (string):
    print("\033[92m" + string + "\033[0m")

def print_red (string):
    print("\033[91m" + string + "\033[0m")
 
print("Testing Rule params")
test_battery(rule_tests)

print("Testing Lines params")
test_battery(lines_tests)

print("Testing Start params")
test_battery(start_tests)

print("Testing Window params")
test_battery(window_tests)

print("Testing Move params")
test_battery(move_tests)