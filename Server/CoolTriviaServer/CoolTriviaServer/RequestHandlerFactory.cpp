#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_StatisticsManager(database)
{
	this->m_database = database;
	this->m_loginManager = LoginManager(database);
	this->m_roomManager = RoomManager();
}

RequestHandlerFactory::~RequestHandlerFactory()
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
	return new MenuRequestHandler(*this, user);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(Room room, LoggedUser user)
{

	return new RoomAdminRequestHandler(*this, room, user);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(Room room, LoggedUser user)
{

	return new RoomMemberRequestHandler(*this, room, user);
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_StatisticsManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
	return this->m_loginManager;
}
