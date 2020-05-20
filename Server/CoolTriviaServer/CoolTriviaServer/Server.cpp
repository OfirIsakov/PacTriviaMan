#include "Server.h"

// Function will run the server - open DB, bind, listen and get clients
void Server::run()
{
	try
	{
		m_database = new SqliteDataBase();
	}
	catch (const runtime_error& e)
	{
		std::cerr << e.what();
		_exit(1);
	}
	m_communicator.bindAndListen();
}
