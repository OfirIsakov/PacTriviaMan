#include "Server.h"
#include <exception>
#include <iostream>
#include "consts.h"
#include <string.h>

Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	this->_port = PORT;
	this->_serverIp = IP;
	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		accept();
	}
}

void Server::accept()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// the function that handle the conversation with the client
	this->_serverThreads.push_back(std::thread(&Server::clientHandler, this, client_socket));
	this->_serverThreads.back().detach();

	LoginRequestHandler clientHandler;
	this->_clientsConnected.emplace(client_socket, clientHandler);
}


/*
Function will handle the client
Input:
	clientSocket - the socket of the client
Output:
	none
*/
void Server::clientHandler(SOCKET clientSocket)
{
	char* data = new char[5 + 1];
	data[5] = '\0';
	if (send(clientSocket, "Hello", 5, 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
	std::cout << "Send!" << std::endl;
	int res = recv(clientSocket, data, 5, 0);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(clientSocket);
		throw std::exception(s.c_str());
	}
	std::cout << "Data: " << data << std::endl;
}

/*
Function will return the port to listen to
Input:
	none
Output:
	the port
*/
int Server::getPort() const
{
	return this->_port;
}
