#include "Server.h"
#include <exception>
#include "consts.h"
#include <string.h>

void Server::run()
{
	m_communicator.bindAndListen();
}
