#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
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
using std::copy;
using std::back_inserter;
using std::cout;
using std::endl;


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

