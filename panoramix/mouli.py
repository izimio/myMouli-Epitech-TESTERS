from utils import *
from druid import *
from villager import *
from pot import *

def coherence_test(iteration):
    line = get_random_params()
    cmd = "./panoramix " + line + " > trace && cat trace | grep 'roman' | wc -l > ret"
    prev = -1;
    atm = -1;
    print_grey("Testing on : " + cmd + "\n")
    for i in range(iteration):
        prev = atm
        os.system(cmd)
        atm = int(open_file_content("ret"))
        if (prev != -1 and prev != atm):
            print_red("\N{cross mark} Test failed, incoherent result")
            print_red("Prev number of fights: " + str(prev))
            print_red("Atm number of fights: " + str(atm))
            return
    print_green("\N{check mark} Test passed, coherent result")

def coherence_battle_sleep(iteration, grep):
    line = get_random_params()
    expected = int(line.split()[0])
    cmd = "./panoramix " + line + " > trace && cat trace | grep '" + grep + "' | wc -l > ret"
    atm = -1;
    print_grey("Testing on : " + cmd + "\n")
    for i in range(iteration):
        prev = atm
        os.system(cmd)
        atm = int(open_file_content("ret"))
        if (atm != expected):
            print_red("\N{cross mark} Test failed, incoherent result")
            print_red("Expected Villagers going to battle:\nGOT: " + str(atm) + "\nEXPECTED: "+ str(grep))
            return
    print_green("\N{check mark} Test passed, coherent result")



def test_validity():
    check_druid()
    check_villagers()
    check_pot()

print_yellow("<==========> Coherence tests <==========>\n")
print_yellow("<=====> 'Going to battle!' <=====>")
coherence_battle_sleep(150, "Going into battle!")
print_yellow("<=====> 'I'm going to sleep' <=====>")
coherence_battle_sleep(150, " going to sleep")
print_yellow("<=====> 'Take that roman scum!' <=====>")
coherence_test(150)
print("\n")
print_yellow("<==========> Validity tests <==========>\n")

test_validity()