#include "MenuRequestHandler.h"

RequestResult MenuRequestHandler::signout(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	LogoutResponse logoutReponse;
	vector<Room> rooms;

	rooms = this->m_roomManager.getRooms();
	for (auto& room : rooms)
	{
		room.removeUser(this->m_user);
	}
	this->m_handlerFactory.getLoginManager().logout(this->m_user.getUsername());
	logoutReponse = { successStatus };

	handler = m_handlerFactory.createLoginRequestHandler();

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(logoutReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	GetRoomsResponse getRoomsReponse;
	vector<RoomData> rooms;

	rooms = this->m_roomManager.getRoomsData();
	getRoomsReponse = { successStatus, rooms };

	handler = nullptr;

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(getRoomsReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	GetPlayersInRoomResponse getRoomsReponse;

	GetPlayersInRoomRequest playersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(info.buffer); // deserialize the buffer

	Room room = this->m_roomManager.getRoom(playersInRoomRequest.roomId);
	getRoomsReponse = { room.getAllUsers() };

	handler = nullptr;

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(getRoomsReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult MenuRequestHandler::getStatistics(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	GetStatisticsResponse getStatisticsReponse;

	getStatisticsReponse = { successStatus, this->m_statisticsManager.getStatistics(m_user.getUsername()) };

	handler = nullptr;

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(getStatisticsReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	JoinRoomResponse joinRoomReponse;

	JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer); // deserialize the buffer

	Room room = this->m_roomManager.getRoom(joinRoomRequest.roomId);
	try
	{
		if (this->m_roomManager.getRoomState(joinRoomRequest.roomId) == alreadyStartedRoom) {

		}
		room.addUser(this->m_user);
		joinRoomReponse = { successStatus };
	}
	catch (const exception&)
	{
		joinRoomReponse = { roomIsFullStatus };
	}

	handler = nullptr; //TODORO the handler needs to be changed to "in room handler"

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(joinRoomReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	CreateRoomResponse createRoomReponse;
	CreateRoomRequest createRoomRequest;

	createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer); // deserialize the buffer

	int id = this->m_roomManager.getRoomsData().rbegin()->id;
	string name = createRoomRequest.roomName;
	int maxPlayers = createRoomRequest.maxUsers;
	unsigned int timePerQuestion = createRoomRequest.answerTimeout;
	unsigned int isActive = waitingForPlayersRoom;
	RoomData data = { id, name, maxPlayers, timePerQuestion ,isActive };
	this->m_roomManager.createRoom(this->m_user, data);
	createRoomReponse = { successStatus };

	handler = nullptr; //TODORO the handler needs to be changed to "in room handler"

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(createRoomReponse);

	RequestResult result = { answer, handler };
	return result;
}

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser user) : m_handlerFactory(handlerFactory), m_user(user), m_roomManager(handlerFactory.getRoomManager()), m_statisticsManager(handlerFactory.getStatisticsManager())
{
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == createRoomCode ||
		info.id == getRoomsCode ||
		info.id == getPlayersInRoomCode ||
		info.id == joinRoomCode ||
		info.id == getStatisticsCode ||
		info.id == logoutCode;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo info)
{
	IRequestHandler* nextHandler;
	RequestResult result;
	vector<unsigned char> answer;
	ErrorResponse errorReponse;

	try
	{
		switch (info.id)
		{
		case createRoomCode:
			result = this->createRoom(info);

			break;
		case getRoomsCode:
			result = this->getRooms(info);

			break;
		case getPlayersInRoomCode:
			result = this->getPlayersInRoom(info);

			break;
		case joinRoomCode:
			result = this->joinRoom(info);

			break;
		case getStatisticsCode:
			result = this->getStatistics(info);

			break;
		case logoutCode:
			result = this->signout(info);

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

LoggedUser MenuRequestHandler::getLoggedUser()
{
	return this->m_user;
}
