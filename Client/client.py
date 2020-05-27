import socket
import json
import random
import time

from threading import Thread


IP = "127.0.0.1"
DEFAULT_PORT = 8820
CODE_BYTES_SIZE = 1
LENGTH_BYTES_SIZE = 4
SIGN_UP_CODE = 1
LOGIN_CODE = 2
MIN_PORT = 1024
MAX_PORT = 65535
CLIENT_SOCKET = None


# the function receives the message form the server in the known protocol, else throws error
# return format (message_code, message_length, raw_message)
def receive_message(socket):
	try:
		message_code = int.from_bytes(socket.recv(CODE_BYTES_SIZE), byteorder='big', signed=False)
		message_length = int.from_bytes(socket.recv(4), byteorder='big', signed=False)
		message = socket.recv(message_length).decode()
	except Exception as e:
		raise e
	return (message_code, message_length, message)


# function serializes the given message and sends it
def serelize_and_send(code: int, json_message: json, socket, title: str=''):
	print(f"Trying to send {title} request...")
	send_data = json.dumps(json_message)[1:-1].replace('\\', '')
	print(send_data)
	socket.send(code.to_bytes(CODE_BYTES_SIZE, byteorder='big') + len(send_data).to_bytes(LENGTH_BYTES_SIZE, byteorder='big') + send_data.encode()) # connect the message parts, encode it and send it
	print(f"Sent!")


# function tries to log into an account
def login_to_user(name: str, server_port: int):
	print(f"Connecting to {IP} on port {server_port}...")
	new_client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create TCP socket
	new_client_socket.connect((IP, server_port)) # try to connect to the server
	print(f"Connected!")

	time.sleep(3)
	login = {"username": name, "password": "1234"}
	serelize_and_send(LOGIN_CODE, json.dumps(login), new_client_socket, 'login to already logged in user: ' + name)
	message = receive_message(new_client_socket)
	print('received:')
	print(message)

	time.sleep(3)
	signup = {"username": name, "password": "1234", "mail": name + "@gmail.com"}
	serelize_and_send(SIGN_UP_CODE, json.dumps(signup), new_client_socket, 'sign up to already exists user: ' + name)
	message = receive_message(new_client_socket)
	print('received:')
	print(message)




def main():
	global CLIENT_SOCKET
	try:
		server_port = input("Input port number(between 1024-65535) or leave empty for default(8820): ") or DEFAULT_PORT # get input of user for a port or use default on
		try:
			server_port = int(server_port)
			if not (MIN_PORT < server_port < MAX_PORT):
				server_port = DEFAULT_PORT
		except Exception:
			server_port = DEFAULT_PORT


		print(f"Connecting to {IP} on port {server_port}...")
		CLIENT_SOCKET = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create TCP socket
		CLIENT_SOCKET.connect((IP, server_port)) # try to connect to the server
		print(f"Connected!")

		name = str(random.randint(1, 1000000000000))

		login = {"username": name, "password": "1234"}
		serelize_and_send(LOGIN_CODE, json.dumps(login), CLIENT_SOCKET, 'login to not registered user: ' + name)
		message = receive_message(CLIENT_SOCKET)
		print('received:')
		print(message)
		
		time.sleep(3)
		signup = {"username": name, "password": "1234", "mail": name + "@gmail.com"}
		serelize_and_send(SIGN_UP_CODE, json.dumps(signup), CLIENT_SOCKET, 'sign up to a new user: ' + name)
		message = receive_message(CLIENT_SOCKET)
		print('received:')
		print(message)

		time.sleep(3)
		login = {"username": name, "password": "1234"}
		serelize_and_send(LOGIN_CODE, json.dumps(login), CLIENT_SOCKET, 'login to not logged in user: ' + name)
		message = receive_message(CLIENT_SOCKET)
		print('received:')
		print(message)

		print('Opening another client to try to log into the same account...')
		new_account_thread = Thread(target=login_to_user, args=(name, server_port))
		new_account_thread.start()
		new_account_thread.join()

		input('Press enter to quit...')
	except Exception as e:
		print(f"ERROR: {e}")


if __name__ == '__main__':
	main()
