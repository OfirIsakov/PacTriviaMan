#pragma once

#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"
#include "GameManager.h"
#include "StatisticsManager.h"
#include "RoomManager.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
	LoginManager m_loginManager;
	IDatabase* m_database;
	RoomManager m_roomManager;
	GameManager m_gameManager;
	StatisticsManager m_StatisticsManager;

public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	// states generators
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room room, LoggedUser user);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(Room room, LoggedUser user);
	GameRequestHandler* createGameRequestHandler(Game game, LoggedUser user);
	StatisticsManager& getStatisticsManager();

	// getters
	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	GameManager& getGameManager();

};

