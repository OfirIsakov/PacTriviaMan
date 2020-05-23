import socket
import json
import random
import time


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
def receive_message():
	try:
		message_code = int.from_bytes(CLIENT_SOCKET.recv(CODE_BYTES_SIZE), byteorder='big', signed=False)
		message_length = int.from_bytes(CLIENT_SOCKET.recv(4), byteorder='big', signed=False)
		message = CLIENT_SOCKET.recv(message_length).decode()
	except Exception as e:
		raise e
	return (message_code, message_length, message)


# function serializes the given message and sends it
def serelize_and_send(code: int, json_message: json, title: str=''):
	print(f"Trying to send {title} request...")
	CLIENT_SOCKET.send(code.to_bytes(CODE_BYTES_SIZE, byteorder='big') + len(json.dumps(json_message)).to_bytes(LENGTH_BYTES_SIZE, byteorder='big') + json.dumps(json_message).encode()) # connect the message parts, encode it and send it
	print(f"Sent!")


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
		serelize_and_send(LOGIN_CODE, json.dumps(login), 'login to not registered user: ' + name)
		message = receive_message()
		print('received:')
		print(message)
		
		time.sleep(3)
		signup = {"username": name, "password": "1234", "mail": name + "@gmail.com"}
		serelize_and_send(SIGN_UP_CODE, json.dumps(signup), 'sign up to a new user: ' + name)
		message = receive_message()
		print('received:')
		print(message)

		time.sleep(3)
		login = {"username": name, "password": "1234"}
		serelize_and_send(LOGIN_CODE, json.dumps(login), 'login to not logged in user: ' + name)
		message = receive_message()
		print('received:')
		print(message)

		time.sleep(3)
		login = {"username": name, "password": "1234"}
		serelize_and_send(LOGIN_CODE, json.dumps(login), 'login to already logged in user: ' + name)
		message = receive_message()
		print('received:')
		print(message)

		time.sleep(3)
		signup = {"username": name, "password": "1234", "mail": name + "@gmail.com"}
		serelize_and_send(SIGN_UP_CODE, json.dumps(signup), 'login to already exists user: ' + name)
		message = receive_message()
		print('received:')
		print(message)

		input('Press enter to quit...')
	except Exception as e:
		print(f"ERROR: {e}")


if __name__ == '__main__':
	main()
