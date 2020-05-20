#include "Communicator.h"
#include <iostream>
#include <ctime>
#include "consts.h"
#include "LoginRequestHandler.h"
#include "Helper.h"

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

// Function will binds the IP and port and listen to it
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

// Function will handle a new client when it connect to the server
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
	none
Output:
	none
*/
void Communicator::handleNewClient()
{
	// get the user socket
	SOCKET clientSocket = this->m_clients.rbegin()->first;
	IRequestHandler* currentHandler = this->m_clients.rbegin()->second;

	// init local vars
	char* code;
	char* jsonLengthBytes;
	int jsonLength;
	char* rawJson;
	vector<unsigned char> jsonInBytes;

	while (true)
	{
		try
		{
			code = Helper::readFromSocket(clientSocket, partCode);
			jsonLengthBytes = Helper::readFromSocket(clientSocket, partJsonLength);

			jsonLength = Helper::convertFourBytesToInt((unsigned char*)jsonLengthBytes);
			rawJson = Helper::readFromSocket(clientSocket, jsonLength);

			string a = string(rawJson);
			std::copy(a.begin(), a.end(), std::back_inserter(jsonInBytes)); // turn the rawJson Buffer into byte vector

			RequestInfo info = { code[0], time(nullptr), jsonInBytes };

			RequestResult result = currentHandler->handleRequest(info);

			delete currentHandler;
			currentHandler = result.newHandler;
			for (auto it = this->m_clients.begin(); it != this->m_clients.end(); it++) {
				if (it->first == clientSocket) {
					it->second = currentHandler;
					break;
				}
			}

			Helper::sendData(clientSocket, result.response);

			// free up the space so no leaks
			delete[] code;
			delete[] jsonLengthBytes;
			delete[] rawJson;
		}
		catch (const std::exception&)
		{
			// delete the client element from the map
			for (auto it = this->m_clients.begin(); it != this->m_clients.end(); it++) {
				if (it->first == clientSocket) {
					this->m_clients.erase(it);
					break;
				}
			}
			closesocket(clientSocket);
			// exit while loop
			break;
		}

	}
}
