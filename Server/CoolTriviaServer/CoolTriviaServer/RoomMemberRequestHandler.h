#pragma once

#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "Room.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "consts.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult leaveRoom(RequestInfo info);
	RequestResult getRoomState(RequestInfo info);
public:
	RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user);
	~RoomMemberRequestHandler();

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
};

