#pragma once

#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"

class LoginRequestHandler;

class RequestHandlerFactory
{
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;

public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(string username);

	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

	// getters
	LoginManager& getLoginManager();

};

