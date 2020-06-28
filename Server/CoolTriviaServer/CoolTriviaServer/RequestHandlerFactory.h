#pragma once

#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

class RequestHandlerFactory
{
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
	StatisticsManager m_StatisticsManager;

public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	// states generators
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(string username);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room room, string username);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(Room room, string username);

	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();

	// getters
	LoginManager& getLoginManager();

};

