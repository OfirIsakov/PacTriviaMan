#include "Server.h"

void Server::run()
{
	m_database = new SqliteDataBase();
	m_communicator.bindAndListen();
}
