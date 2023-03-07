import os
import sys

def get_directories():
    return [x for x in os.listdir() if os.path.isdir(x)]

if len(sys.argv) == 1:
    print("Passe the folder you'd like to keep as an argument")
    sys.exit(1)

def get_args():
    args = sys.argv[1:]
    for arg in args:
        args = arg.lower()
    return args

def remove_directories(directories, args):
    dir_found = False

    for directory in directories:
        if directory.lower() in args:
            dir_found = True
    if not dir_found:
        print("No directory found with args: ", args)
        sys.exit(1)
    for directory in directories:
        if directory.lower() not in args:
            os.system("rm -rf " + directory)

args = get_args()
directories = get_directories()

print("Directories: ", directories)
print("Args: ", args)

remove_directories(directories, args)