#pragma once

#include "Communicator.h"
#include "IDatabase.h"
#include "SqliteDataBase.h"
#include "consts.h"
#include <exception>
#include <string.h>

class Server
{
public:
	void run();

private:

	Communicator m_communicator;
	IDatabase* m_database;
	SOCKET _serverSocket;

};