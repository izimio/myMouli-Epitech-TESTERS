import socket
import sys
import time
import os

## ==== Print functions ====

def print_in_green(message):
    print("\033[92m {}\033[00m" .format(message))

def print_in_red(message):
    print("\033[93m {}\033[00m" .format(message))

def print_in_blue(message):
    print("\033[94m {}\033[00m" .format(message))

def print_in_orange(message):
    print("\033[95m {}\033[00m" .format(message))

def get_port_addr(buff):
    try:
        tmp = buff.split("(")[1].split(")")[0].split(",")
        return int(tmp[1]) * 256 + int(tmp[2])
    except:
        return -1 
## /====/ Print functions /====/

## ==== Utils functions ====

def get_serv_pwd(socket):
    socket.sendall("PWD\r\n".encode())
    data = socket.recv(1024).decode().strip().split()[1]
    data = data[1:-1]
    return data
## /====/ Utils functions /====/

