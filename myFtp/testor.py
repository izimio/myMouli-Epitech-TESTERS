import socket
import sys

def print_in_green(message):
    print("\033[92m {}\033[00m" .format(message))

def print_in_red(message):
    print("\033[93m {}\033[00m" .format(message))


def test(name, socket, message, expected_code):
    global all_tests, passed_tests
    all_tests = all_tests + 1
    expected_code = str(expected_code)
    print("Test on " + name)
    message = message + "\r\n";
    socket.sendall(message.encode())
    response = socket.recv(1024).decode().strip().split()[0]

    if response == expected_code:
        print_in_green("Return code OK")
        passed_tests = passed_tests + 1
    else:
        print_in_red("Return code KO")
        print_in_red("Expected: " + str(expected_code) + "\nGot: " + response)
    print("")


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
    else:
        print_in_red("KO")
        print_in_red("Expected: 220\nGot: " + got)
    print("")

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
    test("PWD", socket, "PWD", 257)
    # test("CWD", socket, "CWD", 550)
    # test("CWD missing parameter", socket, "CWD", 550)
    # test("CWD ../", socket, "CWD ../", 250)
    # test("CWD /", socket, "CWD /", 250)
    # test("CWD /home", socket, "CWD /home", 250)
    # test("CDUP", socket, "CDUP", 200)
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
    test("QUIT", socket, "QUIT", 221)

## === MAIN === ##
if len(sys.argv) < 3:
    print("Usage: python testor.py <host> <port>")
    sys.exit(1)

server_host = sys.argv[1]
server_port = int(sys.argv[2])
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
all_tests = 0
passed_tests = 0


preliminaries(client_socket)

print("==== Connection tests ====\n")
connection_tests(client_socket)
print("==== Simple command ====\n")
simple_commands_tests(client_socket)

preliminaries(client_socket2)
print("==== Simple command refused ====\n")
simple_commands_tests_refused(client_socket2)

print("Passed " + str(passed_tests) + "/" + str(all_tests) + " tests")
client_socket.close()

