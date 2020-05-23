#pragma once

#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"

class Communicator;
class LoginRequestHandler;
class Server;

class RequestHandlerFactory
{
	LoginManager m_loginManager;
	IDatabase* m_database;

public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

};

