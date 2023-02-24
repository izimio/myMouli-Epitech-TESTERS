import socket
import sys
import time
import os
from utils import *


## ==== Testing functions ====

def test(name, socket, message, expected_code, double_cmd=False, mute = False):
    global all_tests, passed_tests
    all_tests = all_tests + 1
    expected_code = str(expected_code)
    if not mute:
        print("Test on " + name)
    if not double_cmd:
        message = message + "\r\n";
    socket.settimeout(1) # set the timeout to 1 seconds
    socket.sendall(message.encode())
    response = ""
    try:
        response = socket.recv(1024).decode().strip()
    except:
        print_in_red("Timeout error: Test " + name + " timed out after 2 seconds")
        print("")
        return response
    if response.split()[0] == expected_code:
        if not mute:
            print_in_green("Return code OK")
            print_in_green("Expected: " + str(expected_code) + "\nGot: " + response.split()[0])
        passed_tests = passed_tests + 1
    else:
        if not mute:
            print_in_red("Return code KO")
            print_in_red("Expected: " + str(expected_code) + "\nGot: " + response.split()[0])
    if not mute:
        print("")
    return response

def read_data_socket(data_socket, expected):
    global all_tests, passed_tests
    time.sleep(0.2)

    all_tests += 1
    print("Testing content of the retrieved file:")
    data_socket.settimeout(1) # set the timeout to 2 seconds
    ret = ""
    try:
        ret = data_socket.recv(1024).decode().strip()
    except:
        print_in_red("Timeout error: timeout after 2 seconds")
        print("")
        return ret
    if ret != expected:
        print_in_red("KO: expected: " + expected + "\n got: " + ret)
    else:
        passed_tests += 1
        print_in_green("OK: expected: " + expected + "\n got: " + ret)
    print("")

def read_file_test(filename, expect):
    time.sleep(0.2)
    global all_tests, passed_tests
    all_tests = all_tests + 1
    try:
        with open(filename, 'rb') as f:
            data = f.read()
    except:
        print_in_red("File not found")
        return
    data = data.decode()
    if data == expect:
        passed_tests = passed_tests + 1
        print_in_green("File content OK")
        print_in_green("Expected: " + str(expect) + "\nGot: " + str(data))
    else:
        print_in_red("File content KO")
        print_in_red("Expected: " + str(expect) + "\nGot: " + str(data))
    try:
        os.remove(filename)
    except:
        pass

## /====/ Testing functions /====/

## /====/ Tests lists /====/

def connection_tests(socket):
    test("USER missing parameter", socket, "USER", 501)
    test("PASS without username", socket, "PASS", 503)
    test("USER good username 1", socket, "USER 45", 331)
    test("USER spaces", socket, "USER    ", 501)
    test("PASS wrong password", socket, "PASS 45", 530)
    test("USER good username", socket, "USER A", 331)
    test("PASS good password but wrong username", socket, "PASS", 530)
    test("USER good username overall", socket, "USER Anonymous", 331)
    test("PASS good password", socket, "PASS", 230)
    test("USER already logged in", socket, "USER Anonymous", 530)
    test("PASS already logged in", socket, "PASS", 230)

def simple_commands_tests(socket):
    pwd = get_serv_pwd(socket)
    test("PWD", socket, "PWD", 257)
    test("CWD", socket, "CWD", 550)
    test("CWD missing parameter", socket, "CWD", 550)
    test("CWD ../", socket, "CWD ../", 550)
    test("CWD /", socket, "CWD /", 550)
    test("CWD /home", socket, "CWD /home", 550)
    test("CWD src", socket, "CWD src", 250)
    test("CWD ../", socket, "CWD ../", 250)
    test("CWD ../", socket, "CWD ../", 550)
    test("CWD ./src", socket, "CWD ./src", 250)
    test("CWD ../src", socket, "CWD ../src", 250)
    test("CWD ../", socket, "CWD ../", 250)
    test("CWD /src", socket, "CWD /src", 550)
    test("CWD src", socket, "CWD src", 250)
    test("CDUP", socket, "CDUP", 200)
    test("CDUP", socket, "CDUP", 550)
    test("NOOP", socket, "NOOP", 200)
    test("HELP", socket, "HELP", 214)
    test("NOOP", socket, "NOOP", 200)
    test("QUIT", socket, "QUIT", 221)

def simple_commands_tests_refused(socket):
    test("PWD", socket, "PWD", 530)
    test("CWD", socket, "CWD", 530)
    test("CWD missing parameter", socket, "CWD", 530)
    test("CWD ../", socket, "CWD ../", 530)
    test("CWD /", socket, "CWD /", 530)
    test("CWD /home", socket, "CWD /home", 530)
    test("CDUP", socket, "CDUP", 530)
    test("NOOP", socket, "NOOP", 530)
    test("HELP", socket, "HELP", 530)
    test("NOOP", socket, "NOOP", 530)
    test("NOOP", socket, "NOOP", 530)
    test("STOR", socket, "STOR", 530)
    test("RETR", socket, "RETR", 530)
    test("LIST", socket, "LIST", 530)
    test("STOR ./", socket, "STOR ./", 530)
    test("RETR", socket, "RETR ./", 530)
    test("LIST", socket, "LIST ./", 530)
    test("STOR ../", socket, "STOR ../", 530)
    test("RETR", socket, "RETR ../", 530)
    connect_client(socket)
    test("STOR", socket, "STOR", 425)
    test("RETR", socket, "RETR", 425)
    test("LIST", socket, "LIST", 425)
    test("STOR ./", socket, "STOR ./", 425)
    test("RETR", socket, "RETR ./", 425)
    test("LIST", socket, "LIST ./", 425)
    test("STOR ../", socket, "STOR ../", 425)
    test("RETR", socket, "RETR ../", 425)
    test("QUIT", socket, "QUIT", 221)

def double_commands(socket):
    connect_client(socket)
    test("PWD\\r\\nPASS\\r\\n", socket, "PWD\r\nPASS", 257)
    test("NOOP\\r\\nQUIT", socket, "NOOP\r\nQUIT", 230, True)
    test("\\r\\n", socket, "\r\n", 221, True)
    # test("End dumping1", socket, "\r\n", 257, False)
    # test("End dumping2", socket, "", 200, False)
    # test("CWD", socket, "CWD\r\nCWD", 550, True)
    # test("CWD missing parameter", socket, "CWD\r\nCWD", 550, True)
    # test("CWD ../", socket, "CWD ../\r\nCWD ../", 250, True)
    # test("CWD /", socket, "CWD /\r\nCWD /", 250, True)
    # test("CWD /home", socket, "CWD /home\r\nCWD /home", 250, True)
    # test("CDUP", socket, "CDUP\r\nCDUP", 200, True)
    # test("NOOP", socket, "NOOP\r\nNOOP", 200, True)
    # test("HELP", socket, "HELP\r\nHELP", 214, True)
    # test("NOOP", socket, "NOOP\r\nNOOP", 200, True)
    # test("QUIT", socket, "QUIT\r\nQUIT", 221, True)

def list_tests(socket, mode):
    data_socket = None
    data_socket = get_right_data_soket(data_socket, socket, mode)
    if data_socket is None:
        print_in_red("KO: PASV/PORT test failed, can't continue testing")
        return

    test("LIST", socket, "LIST", 501)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("LIST ./", socket, "LIST ./", 150)
    test("LIST ./", socket, "LIST ./", 425)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("LIST ../", socket, "LIST ../", 550)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("CWD src", socket, "CWD src", 250)
    test("LIST ../", socket, "LIST ../", 150)
    test("Dumping", socket, "", 226)
    data_socket.close()

def retr_tests(socket, mode):
    data_socket = None
    data_socket = get_right_data_soket(data_socket, socket, mode)
    if data_socket is None:
        print_in_red("KO: PASV/PORT test failed, can't continue testing")
        return

    test("CWD ..", socket, "CWD ..", 250)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("RETR", socket, "RETR", 501)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("RETR ./", socket, "RETR ./", 150)
    test("Dumping", socket, "", 226)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("RETR ../Makefile", socket, "RETR ../Makefile", 550)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("RETR file", socket, "RETR file", 150)
    test("Dumping", socket, "", 226)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("RETR src/../src/../file", socket, "RETR src/../src/../file", 150)
    read_data_socket(data_socket, "Hello World!\ndump")
    test("Dumping", socket, "", 226)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("RETR src/../src/file", socket, "RETR src/../src/file", 550)
    data_socket.close()

def stor_test(socket, mode):
    pwd = get_serv_pwd(socket)
    data_socket = None
    data_socket = get_right_data_soket(data_socket, socket, mode)
    if data_socket is None:
        print_in_red("KO: PASV/PORT test failed, can't continue testing")
        return
    
    test("STOR", socket, "STOR", 501)
    test("STOR ./", socket, "STOR ./", 550)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("STOR src/pouet", socket, "STOR src/pouet", 150)
    data_socket.send("Hello World!\ndump\r\n".encode())
    read_file_test(pwd + "/src/pouet", "Hello World!\ndump\r\n")
    data_socket.close()
    test("Dumping", socket, "", 226)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("STOR ../pouet", socket, "STOR ../pouet", 550)
    data_socket = get_right_data_soket(data_socket, socket, mode)
    test("STOR src/../src/../src/test", socket, "STOR src/../src/../src/test", 150)
    data_socket.send("Bien joue si tu passes\r\nTout\r\nces\r\ntests\r\nhahha\n".encode())
    read_file_test(pwd + "/src/../src/../src/test", "Bien joue si tu passes\r\nTout\r\nces\r\ntests\r\nhahha\n")
    data_socket.close()
    test("Dumping", socket, "", 226)
    data_socket.close()

def pasv_tests(socket):
    connect_client(socket)

    list_tests(socket, mode="PASV")
    retr_tests(socket, mode="PASV")
    stor_test(socket, mode="PASV")

def port_tests(socket):
    connect_client(socket)

    list_tests(socket, mode="PORT")
    retr_tests(socket, mode="PORT")
    stor_test(socket, mode="PORT")
## ====  Tests lists ====


## ==== Setup ====

def preliminaries(socket):
    print("Connecting to server...")
    try:
        socket.connect((server_host, server_port))
    except:
        print_in_red("Connection failed")
        sys.exit(1)
    print_in_green("Connection established")
    got = socket.recv(1024).decode().strip().split()[0]
    if got == "220":
        print_in_green("OK")
        print_in_green("Expected: 220\nGot: " + got)
    else:
        print_in_red("KO")
        print_in_red("Expected: 220\nGot: " + got)
    print("")

def connect_client(socket):
    print("Connecting new client with credentials")
    test("USER Anonymous", socket, "USER Anonymous", 331, mute = True)
    test("PASS", socket, "PASS", 230, mute = True)
    print("")
## /====/ Setup /====/

def connect_to_pasv(prev_socket):
    time.sleep(0.1)
    ret = test("PASV", prev_socket, "PASV", 227, mute=True)
    port = get_port_addr(ret)

    socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        socket1.connect((server_host, port))
    except:
        return None
    return socket1

def connect_to_port(prev_socket):
    socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    socket1.bind((server_host, 0))
    socket1.listen(1)
    port = socket1.getsockname()[1]
    P1 = port // 256
    P2 = port % 256
    test("PORT " + str(port), prev_socket, "PORT " + "127,0,0,1," + str(P1) + "," + str(P2), 200)
    try:
        socket2, addr = socket1.accept()
    except:
        return None
    return socket2

def get_right_data_soket(data_socket, socket, mode):
    if data_socket is not None:
        data_socket.close()
    if mode == "PASV":
        return connect_to_pasv(socket)
    else:
        return connect_to_port(socket)

def init_tree():
    if not os.path.exists("src"):
        os.makedirs("src")
    if not os.path.exists("file"):
        with open("file", "w") as f:
            f.write("Hello World!\ndump")

## === MAIN === ##
if len(sys.argv) < 3 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
    print("Usage: python testor.py <host> <port>")
    print_in_orange("/!\ You need to launch your myFtp with whatever port you want and link the path to the src folder of this tester /!\\")
    sys.exit(1)

server_host = sys.argv[1]
server_port = int(sys.argv[2])
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket4 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket5 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
all_tests = 0
passed_tests = 0

init_tree()
print("==== Connection tests ====\n")
preliminaries(client_socket)
connection_tests(client_socket)
print("==== Simple command ====\n")
simple_commands_tests(client_socket)
client_socket.close()

print("==== Simple command refused ====\n")
preliminaries(client_socket2)
simple_commands_tests_refused(client_socket2)
client_socket2.close()

# print("==== Double commands buffering ====\n")
# preliminaries(client_socket3)
# double_commands(client_socket3)
# client_socket3.close()

print("==== Testing data command (PASV) ====\n")
preliminaries(client_socket4)
pasv_tests(client_socket4)
client_socket4.close()

print("==== Testing data command (PORT) ====\n")
preliminaries(client_socket5)
port_tests(client_socket5)
client_socket5.close()

if passed_tests == all_tests:
    print_in_green("********************")
    print_in_green("* All tests passed *")
    print_in_green("********************")
    print("Passed " + str(passed_tests) + "/" + str(all_tests) + " tests")
else:
    print_in_red("---------------------")
    print_in_red("| Some tests failed |")
    print_in_red("---------------------")
    print("Passed " + str(passed_tests) + "/" + str(all_tests) + " tests")
client_socket.close()