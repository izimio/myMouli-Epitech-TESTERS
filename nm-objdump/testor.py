import sys
import os
from subprocess import check_output
import subprocess


def print_in_red(text, end="\n"):
    print("\033[90m {}\033[00m".format(text), end=end)


def print_in_green(text, end="\n"):
    print("\033[95m {}\033[00m".format(text, end=end))


if len(sys.argv) < 2:
    print("Usage: <binary to test>")
    sys.exit(1)


def get_file_dir_files():
    file_dir = "bins/"
    files = os.listdir(file_dir)
    return files


def read_file(file):
    with open(file, "r") as f:
        return f.read()

def get_good_out(bin):
    if len(bin.stdout) > 0:
        return bin.stdout, bin.returncode
    return bin.stderr, bin.returncode

def test_binary(binary, test):
    my_binary = subprocess.run(["./my_" + binary + " " + test], capture_output=True, text=True, shell=True)
    binary = subprocess.run([binary + " " + test], capture_output=True, text=True, shell=True)

    my_out, my_ret = get_good_out(my_binary)
    out, ret = get_good_out(binary)
    gud_ret = ret

    if ret != 0:
        gud_ret = 84
    if (
            my_ret == 0
            and ret != 0
    ) or ret != 0 and my_ret != 84:
        print_in_red("Test failed: return code mismatch for " + test)
        print_in_red("Expected: " + str(gud_ret), end=" ")
        print_in_red("Got: " + str(my_ret), end=" ")
    elif  my_out != out:
        print_in_red("Test failed: output mismatch for " + test)
        print_in_red("Expected: " + out[0:100])
        print_in_red("Got: " + my_out[0:100])
        
    else:
        print_in_green("Test passed: " + test)


def fill_nm(files):
    my_nm = ""
    nm = ""
    for file in files:
        test_binary("nm", "bins/" + file)


def fill_objdump(files):
    my_nm = ""
    nm = ""
    for file in files:
        my_nm = os.popen("./my_objdump " + "bins/" + file).read()
        nm = os.popen("objdump " + "bins/" + file).read()
        if my_nm != nm:
            print_in_red("Error with " + file)
            print(my_nm)
        else:
            print_in_green("OK with " + file)


def test_nm(files):
    all_in_one = " bins/".join(files)
    all_in_one = "bins/" + all_in_one
    fill_nm(files)
    test_binary("nm", "bins/ls")
    test_binary("nm", "/usr/bin/ls")
    test_binary("nm", "/usr/lib/libc.so.6")
    test_binary("nm", "/usr/lib/libc-2.27.so")
    test_binary("nm", "../")
    test_binary("nm", "bins/" + files[0] + " " + "bins/" + files[1])
    test_binary("nm", all_in_one)


def test_objdump(files):
    fill_objdump(files)


files = get_file_dir_files()
if sys.argv[1] == "nm":
    test_nm(files)
    os.remove("my_nm")
elif sys.argv[1] == "objdump":
    test_objdump(files)
    os.remove("my_objdump")
else:
    print("Usage: <binary to test>")
    sys.exit(1)
