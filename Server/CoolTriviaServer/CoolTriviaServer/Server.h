#pragma once

#include <exception>
#include <iostream>
#include <string.h>

#include "IDatabase.h"
#include "Communicator.h"
#include "SqliteDataBase.h"
#include "RequestHandlerFactory.h"
#include "consts.h"

using std::runtime_error;

class Server
{
public:
	Server();
	~Server();
	void run();

private:

	Communicator* m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory* m_handlerFactory;

};