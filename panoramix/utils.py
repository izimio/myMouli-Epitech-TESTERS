
import os
import random

def execute_and_get_trace(line):
    print_grey("Testing on " + line)
    os.system("./panoramix " + line + " > trace")
    return open_file_content("trace").split("\n")

def get_arr_of_villager(trace, wanted):
    arr = []
    for line in trace:
        if line.startswith(wanted):
            arr.append(line)
    return arr

def print_green(s):
    print("\033[92m" + s + "\033[0m")

def print_red(s):
    print("\033[91m" + s + "\033[0m")

def print_yellow(s):
    print("\033[93m" + s + "\033[0m")

def print_grey(s):
    print("\033[90m" + s + "\033[0m")

def print_ok(s):
    print_green("\N{check mark} " + s + "\n")

def print_ko(s):
    print_red("\N{cross mark} " + s + "\n")

def get_random_params(nb_villagers= random.randint(1, 20), pot_size= random.randint(10, 50), nb_fight= random.randint(1, 10), nb_refills= random.randint(1, 15)):
    while nb_villagers * nb_fight > (pot_size * nb_refills + 1):
        nb_villagers= random.randint(1, 20)
        pot_size= random.randint(1, 50)
        nb_fight= random.randint(1, 10)
        nb_refills= random.randint(1, 15)

    s = ""
    s += str(nb_villagers) + " "
    s += str(pot_size) + " "
    s += str(nb_fight) + " "
    s += str(nb_refills)
    return s

def open_file_content(file):
    try:
        f = open(file, "r")
        content = f.read()
        f.close()
        return content
    except:
        return ""