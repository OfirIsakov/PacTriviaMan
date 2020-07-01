#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "Room.h"
#include "RoomManager.h"
#include "consts.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult startGame(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);
public:
	RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user);
	~RoomAdminRequestHandler();

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
	RequestResult closeRoom(RequestInfo info);

	//getters
	int getRoomState();
	vector<string> getAllUsersInRoom();
};

