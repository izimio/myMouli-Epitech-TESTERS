#!/usr/bin/env python3

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
    for directory in directories:
        if directory.lower() not in args:
            os.system("rm -rf " + directory)
    os.system("rm -f README.md init.py")

args = get_args()
directories = get_directories()
dir_found = False

def ask_is_ok():
    while True:
        answer = input("Are you sure you want to delete these directories? (y/n): ")
        if answer in ("y", "n"):
            break
        print("Invalid input. Please enter y or n.")
    if answer == "y":
        return True
    else:
        exit(1)
    
for directory in directories:
    if directory.lower() in args:
        dir_found = True
if not dir_found:
    print("No directory found with args: ", args)
    exit(1)

print("Folders to keep: ", args)
ask_is_ok()
remove_directories(directories, args)