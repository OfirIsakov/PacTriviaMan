#include "Communicator.h"
#include <iostream>
#include "consts.h"
#include "LoginRequestHandler.h"

// Communicator Constructor
Communicator::Communicator()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

// Communicator Destructor
Communicator::~Communicator()
{
	// Release the LoginRequestHendler
	for (auto it : m_clients)
	{
		delete it.second;
	}

	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*) & sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		startHandleRequests();
	}
}


void Communicator::startHandleRequests()
{
	// notice that we step out to the global namespace
	// for the resolution of the function accept

	// this accepts the client and create a specific socket from server to this client
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);

	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	LoginRequestHandler* clientHandler = new LoginRequestHandler();
	this->m_clients.emplace(client_socket, clientHandler);
	// the function that handle the conversation with the client
	std::thread cThread(&Communicator::handleNewClient, this);
	cThread.detach();
}

/*
Function will handle the client
Input:
	clientSocket - the socket of the client
Output:
	none
*/
void Communicator::handleNewClient()
{
	SOCKET clientSocket = m_clients.rbegin()->first;
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