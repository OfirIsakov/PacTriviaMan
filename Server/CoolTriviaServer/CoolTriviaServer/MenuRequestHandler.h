#pragma once

#include "IRequestHandler.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"
#include "InvalidRoomIdException.h"
#include "RoomManager.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(RequestInfo info);
	RequestResult getRooms(RequestInfo info);
	RequestResult getPlayersInRoom(RequestInfo info);
	RequestResult getStatistics(RequestInfo info);
	RequestResult joinRoom(RequestInfo info);
	RequestResult createRoom(RequestInfo info);


public:
	MenuRequestHandler(RequestHandlerFactory& m_handlerFactory, LoggedUser user);
	~MenuRequestHandler();

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

	// getters
	LoggedUser getLoggedUser();
};

