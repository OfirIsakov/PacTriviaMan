#pragma once

#include "Communicator.h"
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include "consts.h"
#include <exception>
#include <iostream>
#include <string.h>

using std::runtime_error;

class Server
{
public:
	void run();

private:

	Communicator m_communicator;
	IDatabase* m_database;
	SOCKET _serverSocket;

};