import sys
import os

def print_in_red(text):
    print("\033[90m {}\033[00m" .format(text))

def print_in_green(text):
    print("\033[95m {}\033[00m" .format(text))


if len(sys.argv) < 2:
    print("Usage: <binary to test>")
    sys.exit(1)

def get_file_dir_files():
    file_dir = "bins/"
    files = os.listdir(file_dir)
    return files

def fill_nm(files):
    my_nm = ""
    nm = ""
    for file in files:
        my_nm = os.popen("./my_nm " + "bins/" + file).read()
        nm = os.popen("nm " + "bins/" + file).read()
        if my_nm != nm:
            print_in_red("Error with " + file)
        else:
            print_in_green("OK with " + file)

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

files = get_file_dir_files()
if sys.argv[1] == "nm":
    fill_nm(files)
    os.remove("my_nm")
elif sys.argv[1] == "objdump":
    fill_objdump(files)
    os.remove("my_objdump")
else:
    print("Usage: <binary to test>")
    sys.exit(1)
