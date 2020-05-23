#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <thread>
#include <map>

#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"


using std::vector;
using std::string;
using std::thread;
using std::map;
using std::find;
using std::localtime;


class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();

	void bindAndListen();

private:

	void startHandleRequests();
	void handleNewClient();

	RequestHandlerFactory& m_handlerFactory;
	SOCKET _serverSocket;
	map<SOCKET, IRequestHandler*> m_clients;
};

