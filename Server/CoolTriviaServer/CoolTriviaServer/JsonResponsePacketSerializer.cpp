#include "JsonResponsePacketSerializer.h"

// Function will serialize a message of status
vector<unsigned char> JsonResponsePacketSerializer::serializeStatusMsg(int code, unsigned int status)
{
	json myJson = json{ "status", status };
	return createResponse(code, myJson.dump(), myJson.dump().length());
}

// Function will serialize the login message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse res)
{
	return serializeStatusMsg(loginCode, res.status);
}

// Function will serialize the signup message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse res)
{
	return serializeStatusMsg(signupCode, res.status);
}

// Function will serialize the error message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse res)
{
	json errorJson = json{ "message", res.message };
	return createResponse(errorCode, errorJson.dump(), errorJson.dump().length());
}

// Function will serialize the logout message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse res)
{
	return serializeStatusMsg(logoutCode, res.status);
}

// Function will serialize the get room message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse res)
{
	string roomsStr = "";
	for (int i = 0; i < res.rooms.size() - 1; i++)
	{
		roomsStr += res.rooms[i].name;
		if (i != res.rooms.size() - 1)
		{
			roomsStr += ", ";
		}
	}
	json getRoomJson = json{ "Rooms", roomsStr };
	return createResponse(getRoomsCode, getRoomJson.dump(), getRoomJson.dump().length());
}

// Function will serialize the get players in room message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse res)
{
	string playersStr = "";
	for (int i = 0; i < res.players.size() - 1; i++)
	{
		playersStr += res.players[i];
		if (i != res.players.size() - 1)
		{
			playersStr += ", ";
		}
	}
	json getPlayersInRoomJson = json{ "PlayersInRoom", playersStr };
	return createResponse(getPlayersInRoomCode, getPlayersInRoomJson.dump(), getPlayersInRoomJson.dump().length());
}

// Function will serialize the join room message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse res)
{
	return serializeStatusMsg(joinRoomCode, res.status);
}

// Function will serialize the create room message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse res)
{
	return serializeStatusMsg(createRoomCode, res.status);
}

// Function will serialize the get statistics message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse res)
{
	string userStatsStr = "", highScoresStr = "";
	for (int i = 0; i < res.statistics.size() - 1; i++)
	{
		if (i < 5)
			highScoresStr += res.statistics[i] + ","; // Separate the scores
		else
			userStatsStr += res.statistics[i] + ","; // Separate the stats
	}
	userStatsStr += res.statistics[res.statistics.size() - 1];

	json getStatisticsJson = json{ { "UserStatistics", userStatsStr }, { "HighScores", highScoresStr } };
	return createResponse(getStatisticsCode, getStatisticsJson.dump(), getStatisticsJson.dump().length());
}

// Function will serialize the close game message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse res)
{
	return serializeStatusMsg(closeRoomCode, res.status);
}

// Function will serialize the start game message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(StartGameResponse res)
{
	return serializeStatusMsg(startGameCode, res.status);
}

// Function will serialize the get room state message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse res)
{
	string listOfPlayers = "";
	for (int i = 0; i < res.players.size() - 1; i++)
	{
		listOfPlayers += res.players[i] + ","; // Separate the names
	}
	listOfPlayers += res.players[res.players.size() - 1];

	json getRoomStateJson = json{ { "status", res.status }, { "hasGameBegun", res.hasGameBegun }, { "players", listOfPlayers }, { "questionCount", res.questionCount }, { "answerTimeout", res.answerTimeout } };
	return createResponse(getRoomStateCode, getRoomStateJson.dump(), getRoomStateJson.dump().length());
}

// Function will serialize the leave room message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse res)
{
	return serializeStatusMsg(leaveRoomCode, res.status);
}

// Function will create the response by the correct parameters
vector<unsigned char> JsonResponsePacketSerializer::createResponse(int codeBit, string jsonString, int length)
{
	vector<unsigned char> buffer = {}, temp = {};

	// code bit
	buffer.push_back((unsigned char)codeBit);

	// length bits
	temp = Helper::convertIntToFourBytes(length);
	buffer.insert(buffer.end(), temp.begin(), temp.end());

	// json bits
	for (int i = 0; i < jsonString.length(); i++)
	{
		buffer.push_back(jsonString[i]);
	}

	return buffer;
}
