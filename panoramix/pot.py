from utils import *

def check_villager_behavior_easy(arr, fights, i):
    prev_line = ""

    for line in arr:
        if "Take that roman scum!" in line:
            fights -= 1
            if "I need a drink... I see" not in prev_line:
                print_ko("Villager " + str(i) + " didn't drink before fighting")
                return False
        prev_line = line

    if fights > 0:
        print_ko("Villager " + str(i) + " didn't fight enough")
        return False
    if fights < 0:
        print_ko("Villager " + str(i) + " fought too much")
        return False
    return True

def check_villager_behavior_pot(arr, i):
    prev_line = ""

    for line in arr:
        if "Hey Pano wake up! We need more potion." in line:
            if "I need a drink... I see 0 servings left." not in prev_line:
                print_ko("Villager " + str(i) + " didn't asked before drinking")
                return False
        prev_line = line
    return True

def check_no_over_portion():
    err = 0
    trace = execute_and_get_trace(get_random_params(5, 700, 7, 20))
    for i in range(5):
        arr = get_arr_of_villager(trace, "Villager " + str(i) + ":")
        if not check_villager_behavior_easy(arr, 7, i):
            err += 1
    if err == 0:
        print_ok("1/2 OK")
    trace = execute_and_get_trace(get_random_params(5, 5, 7, 20))
    for i in range(5):
        arr = get_arr_of_villager(trace, "Villager " + str(i) + ":")
        if not check_villager_behavior_pot(arr, i):
            err += 1
    if err == 0:
        print_ok("2/2 OK | No villager over portionned or under portionned")

def check_pot():
    print_yellow("<=====> Pot tests <=====>")
    check_no_over_portion()
