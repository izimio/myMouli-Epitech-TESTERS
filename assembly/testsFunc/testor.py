import sys
import os
import subprocess

def print_in_green(text):
    print("\033[1;32m" + text + "\033[0m")


def print_in_orange(text):
    print("\033[1;33m" + text + "\033[0m")

nbTest = 97 + 45
ret = 0
no_bonus = 0
if len(sys.argv) >= 2 and sys.argv[1] == "no-bonus":
    no_bonus = 1
#preleminaries

os.system("make re")


os.system("gcc -w testsFunc/test.c")

result = subprocess.run(["./a.out"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

ret += result.returncode
if not no_bonus:
    os.system("gcc -w testsFunc/bonus.c")
    result = subprocess.run(["./a.out"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ret += result.returncode
else:
    nbTest -= 45

os.system("make fclean && rm a.out")
if ret == nbTest:
    print_in_green("-------------------------------------")
    print_in_green("|   All tests passed on " + str(nbTest) + " tests" + "   |")
    print_in_green("-------------------------------------")
    
else:
    print_in_orange("-----------------------------------")
    print_in_orange("|   You passed " + str(ret) + " tests on " + str(nbTest) + "   |")
    print_in_orange("-----------------------------------")
    