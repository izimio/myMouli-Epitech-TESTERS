from utils import *


def check_all_villagers_are_here():
    
    trace = execute_and_get_trace(get_random_params(21, 50, 1, 1))
    plain_trace = "\n".join(trace)

    for i in range(21):
        if ("Villager " + str(i) + ":") not in plain_trace:
            print_ko("Villager " + str(i) + " is missing")
            return False
    print_ok("All villagers are here")

def check_all_villagers_comes_and_goes():
    trace = execute_and_get_trace(get_random_params(21, 50, 1, 1))
    for i in range(21):
        arr = get_arr_of_villager(trace, "Villager " + str(i) + ":")
        if (len(arr) < 2):
            print_ko("Villager " + str(i) + " doesn't come and go")
            return False
        if (arr[0] != "Villager " + str(i) + ": Going into battle!"):
            print_ko("Villager " + str(i) + " never came to battle :(")
            return False
        if (arr[-1] != "Villager " + str(i) + ": I'm going to sleep now."):
            print_ko("Villager " + str(i) + " never went to sleep")
            return False
    print_ok("All villagers come and go")
            
def check_villagers():
    print_yellow("<=====> Villagers tests <=====>\n")
    check_all_villagers_are_here()
    check_all_villagers_comes_and_goes()