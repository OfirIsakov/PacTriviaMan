#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
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

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(string username)
{
	return new MenuRequestHandler(*this, LoggedUser(username));
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler()
{

	return new RoomAdminRequestHandler(*this);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler()
{

	return new RoomMemberRequestHandler(*this);
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
