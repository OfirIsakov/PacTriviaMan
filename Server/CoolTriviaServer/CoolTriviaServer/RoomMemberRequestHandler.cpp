#include "RoomMemberRequestHandler.h"

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	LeaveRoomResponse leaveRoomReponse = { successStatus };

	handler = this->m_handlerFactory.createMenuRequestHandler(this->m_user.getUsername());

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(leaveRoomReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo info)
{
	//TODORO this is code copy from RoomAdminRequestHandler::getRoomState
	IRequestHandler* handler;
	vector<unsigned char> answer;
	GetRoomStateResponse roomStateReponse;
	RoomData data = this->m_room.getData();

	roomStateReponse = { successStatus, data.isActive == alreadyStartedRoom, this->m_room.getAllUsers(), data.numOfQuestionsInGame, data.timePerQuestion };

	handler = nullptr;

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(roomStateReponse);

	RequestResult result = { answer, handler };
	return result;
}

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& handlerFactory, Room room, LoggedUser user) : m_room(room), m_user(user), m_handlerFactory(handlerFactory), m_roomManager(handlerFactory.getRoomManager())
{
}

RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == leaveRoomCode ||
		info.id == getRoomStateCode;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo info)
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
			result = this->leaveRoom(info);
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

LoggedUser RoomMemberRequestHandler::getUser()
{
	return this->m_user;
}

RequestResult RoomMemberRequestHandler::roomClosed()
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	CloseRoomResponse closeRoomReponse = { successStatus };

	handler = nullptr;

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(closeRoomReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult RoomMemberRequestHandler::roomStarted()
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	CloseRoomResponse closeRoomReponse = { successStatus };

	handler = nullptr; //TODORO the handle needs to be in game handle

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(closeRoomReponse);

	RequestResult result = { answer, handler };
	return result;
}
