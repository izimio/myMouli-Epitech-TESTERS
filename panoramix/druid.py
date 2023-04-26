from utils import *

def get_druid_phrase(max, nb):
    if (nb == max):
        return "Druid: I'm ready... but sleepy..."
    if (nb == -1):
        return "Druid: I'm out of viscum. I'm going back to... zZz"
    return "Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only make " + str(nb) + " more refills after this one."

def check_druid_array(arr, size):
    max = size
    if (len(arr) != size + 2):
        print_ko("Druid not speaking enough")
        return False

    for line in arr:
        if line != get_druid_phrase(max, size):
            print_ko("Druid phrase not found")
            print_red("I was looking for: " + get_druid_phrase(max, size))
            return False
        size -= 1
    print_ok("Druid phrases OK")
    return True

def check_druid():
    print_yellow("<=====> Druid tests <=====>")
    trace = execute_and_get_trace(get_random_params(21, 1, 1, 20))
    arr = get_arr_of_villager(trace, "Druid:")
    return check_druid_array(arr, 20)