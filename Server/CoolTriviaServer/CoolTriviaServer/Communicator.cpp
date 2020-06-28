#include "Communicator.h"
#include <iostream>
#include <ctime>
#include "consts.h"
#include "LoginRequestHandler.h"
#include "Helper.h"

// Communicator Constructor
Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_serverSocket == INVALID_SOCKET)
		throw exception(__FUNCTION__ " - socket");
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
		throw exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw exception(__FUNCTION__ " - listen");
	cout << "Listening on port " << PORT << endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		cout << "Waiting for client connection request" << endl;
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
		throw exception(__FUNCTION__);

	cout << "Client accepted. Server and client can speak. Connected socket: " << client_socket << endl;

	LoginRequestHandler* clientHandler = this->m_handlerFactory.createLoginRequestHandler();
	this->m_clients.emplace(client_socket, clientHandler);
	// the function that handle the conversation with the client
	thread cThread(&Communicator::handleNewClient, this);
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


			string tempBuffer = string(rawJson);
			copy(tempBuffer.begin(), tempBuffer.end(), back_inserter(jsonInBytes)); // turn the rawJson Buffer into byte vector

			RequestInfo info = { code[0], time(nullptr), jsonInBytes };

			RequestResult result = currentHandler->handleRequest(info);

			// this logic if for sending every user that a room started or closed
			if (dynamic_cast<RoomAdminRequestHandler*>(currentHandler)) // check if the game started, and if yes send to all the users
			{
				if (((RoomAdminRequestHandler*)currentHandler)->getRoomState() == alreadyStartedRoom ||
					((RoomAdminRequestHandler*)currentHandler)->getRoomState() == closedRoom) {
					vector<string> users = ((RoomAdminRequestHandler*)currentHandler)->getAllUsersInRoom();
					for (auto& it : this->m_clients) {
						if (dynamic_cast<RoomMemberRequestHandler*>(it.second)) { // check if the user is in a waiting game state
							string currUser = ((RoomMemberRequestHandler*)it.second)->getUser().getUsername();
							for (auto& user : users) {
								if (user == currUser) {
									if (((RoomAdminRequestHandler*)currentHandler)->getRoomState() == alreadyStartedRoom) {
										RequestResult tmpResult = ((RoomMemberRequestHandler*)it.second)->roomStarted();
										delete it.second;
										it.second = tmpResult.newHandler;
										Helper::sendData(it.first, tmpResult.response);
										break;
									}
									else if (((RoomAdminRequestHandler*)currentHandler)->getRoomState() == closedRoom) {
										RequestResult tmpResult = ((RoomMemberRequestHandler*)it.second)->roomClosed();
										Helper::sendData(it.first, tmpResult.response);
										break;
									}
								}
							}
						}
					}
				}
			}

			if (result.newHandler) {
				delete currentHandler;
				currentHandler = result.newHandler;
			}
			for (auto it = this->m_clients.begin(); it != this->m_clients.end(); it++) {
				if (it->first == clientSocket) {
					it->second = currentHandler;
					break;
				}
			}
			Helper::sendData(clientSocket, result.response);

			// clear the buffer
			jsonInBytes.clear();
			// free up the space so no leaks
			delete[] code;
			delete[] jsonLengthBytes;
			if (strlen(rawJson) > 0) {
				delete[] rawJson;
			}
		}
		catch (const exception & e)
		{
			cout << "Error in socket: " << clientSocket << endl;
			cout << e.what() << endl;
			// remove it form the logged users
			if (dynamic_cast<MenuRequestHandler*>(currentHandler))
			{
				this->m_handlerFactory.getLoginManager().logout(((MenuRequestHandler*)currentHandler)->getLoggedUser().getUsername());
			}
			//TODORO add the check for all states except LoginRequestHandler
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
