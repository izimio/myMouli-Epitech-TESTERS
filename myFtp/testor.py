import socket
import sys

def print_in_green(message):
    print("\033[92m {}\033[00m" .format(message))

def print_in_red(message):
    print("\033[93m {}\033[00m" .format(message))


def test(name, socket, message, expected_code):
    print(name)
    socket.sendall(message.encode())
    response = socket.recv(1024).decode().strip().split()[0]

    if response == expected_code:
        print_in_green("OK")
    else:
        print_in_red("KO")

server_host = sys.argv[1]
server_port = int(sys.argv[2])

if len(sys.argv) < 3:
    print("Usage: python testor.py <host> <port>")
    sys.exit(1)

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print("Connecting to server...")
try:
    client_socket.connect((server_host, server_port))
except:
    print_in_red("Connection failed")
    sys.exit(1)

print("Connection established")

test("USER", client_socket, "", "220")

client_socket.close()

