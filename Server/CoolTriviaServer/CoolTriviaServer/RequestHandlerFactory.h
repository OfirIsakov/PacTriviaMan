#pragma once

#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;

public:
	RequestHandlerFactory(IDatabase* database);
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();

};

