import os
from random import seed
from random import randint

seed(randint(0,1000))

lst = []

data = ""
def get_trace():
    os.system("./push_swap " + lst + "|" + " ../pushswap_checker " + lst + " > trace")
    try:
        text_file = open("trace", "r")
        data = text_file.read()
        text_file.close()
    except:
        exit(84)
    os.system("rm trace")
    return data


def create_list():
    lstSize = randint(1, 1000)
    if lstSize == 0:
        return ""
    print("list of " + str(lstSize))
    return ' '.join([str(randint(-5000, 5000)) for _ in range(lstSize)])

for _ in range(500):
    lst = create_list()
    trace = get_trace()
    if trace != "OK\n":
        print("WRONG KO for lst, check file for info")
        os.system("echo " + lst + " > lst_ko")
        break
    print("\033[92mGG\033[0m")
        