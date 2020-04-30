import socket


IP = "127.0.0.1"
DEFAULT_PORT = 8820
MSG = "Hello"
MIN_PORT = 1024
MAX_PORT = 65535


def main():
	try:
		server_port = input("Input port number(between 1024-65535) or leave empty for default(8820): ") or DEFAULT_PORT # get input of user for a port or use default on
		try:
			server_port = int(server_port)
			if not (MIN_PORT < server_port < MAX_PORT):
				server_port = DEFAULT_PORT
		except Exception:
			server_port = DEFAULT_PORT

		print(f"Connecting to {IP} on port {server_port}...")
		client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # create TCP socket
		client_socket.connect((IP, server_port)) # try to connect to the server
		print(f"Connected!")

		# receive msg from server
		print(f"Trying to receive 5 bytes...")
		recvieved_msg = client_socket.recv(len(MSG)).decode()
		if recvieved_msg.lower() == MSG.lower(): # check if we got the message
			print(f"Got message \"{recvieved_msg}\"")
		else:
			print(f"Didn't receive the message: \"{MSG}\" but received: \"{recvieved_msg}\"")

		# send msg to the server
		print(f"Sending message: \"{MSG}\"")
		client_socket.send(MSG.encode()) # encode message and send it
		print(f"Sent!")
	except Exception as e:
		print(f"ERROR: {e}")


if __name__ == '__main__':
	main()
