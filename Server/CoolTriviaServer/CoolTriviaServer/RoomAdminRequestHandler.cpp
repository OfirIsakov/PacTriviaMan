#include "RoomAdminRequestHandler.h"

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	CloseRoomResponse closeRoomReponse = { successStatus };

	this->m_roomManager.setRoomState(this->m_room.getData().id, closedRoom);

	handler = m_handlerFactory.createMenuRequestHandler(this->m_user);

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(closeRoomReponse);
	
	RequestResult result = { answer, handler };
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	StartGameResponse startRoomReponse = { successStatus };

	this->m_roomManager.setRoomState(this->m_room.getData().id, alreadyStartedRoom);

	handler = nullptr; //TODORO the handle needs to be in game handle

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(startRoomReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	GetRoomStateResponse roomStateReponse;
	RoomData data = this->m_room.getData();

	roomStateReponse = {successStatus, data.isActive == alreadyStartedRoom, this->m_room.getAllUsers(), data.numOfQuestionsInGame, data.timePerQuestion};

	handler = nullptr;

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(roomStateReponse);

	RequestResult result = { answer, handler };
	return result;
}

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user) : m_room(room), m_user(user), m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager())
{
}

RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == closeRoomCode ||
		info.id == startGameCode ||
		info.id == getRoomStateCode;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo info)
{
	IRequestHandler* nextHandler;
	RequestResult result;
	vector<unsigned char> answer;
	ErrorResponse errorReponse;

	try
	{
		switch (info.id)
		{
		case leaveRoomCode:
			result = this->closeRoom(info);
			break;
		case startGameCode:
			result = this->startGame(info);
			break;
		case getRoomStateCode:
			result = this->getRoomState(info);
			break;
		default:
			nextHandler = nullptr;
			errorReponse = { "ERROR" };
			answer = JsonResponsePacketSerializer::serializeResponse(errorReponse);
			result = { answer , nextHandler };
			break;
		}
	}
	catch (const std::exception&)
	{
		nextHandler = nullptr;
		errorReponse = { "ERROR" };
		answer = JsonResponsePacketSerializer::serializeResponse(errorReponse);
		result = { answer , nextHandler };
	}
	return result;
}

int RoomAdminRequestHandler::getRoomState()
{
	return this->m_room.getData().isActive;
}

vector<string> RoomAdminRequestHandler::getAllUsersInRoom()
{
	return this->m_room.getAllUsers();
}
