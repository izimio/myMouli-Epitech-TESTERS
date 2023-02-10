import sys
import os


no_mouli = 0
if len(sys.argv) >= 1 and sys.argv[0] == "no-mouli":
    no_mouli = 1
#preleminaries

os.system("make re")

ret = os.system("gcc -w tests/test.c && ./a.out")

if ret == 0 or no_mouli:
    os.system("gcc -w tests/bonus.c && ./a.out")

os.system("make fclean && rm a.out")