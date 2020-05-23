#include "Server.h"

Server::Server()
{
	try
	{
		this->m_database = new SqliteDataBase();
		this->m_handlerFactory = new RequestHandlerFactory(this->m_database);
		this->m_communicator = new Communicator(*(this->m_handlerFactory));
	}
	catch (const runtime_error & e)
	{
		std::cerr << e.what();
		_exit(1);
	}
}

Server::~Server()
{
}

// Function will run the server - open DB, bind, listen and get clients
void Server::run()
{
	this->m_communicator->bindAndListen();
}

