#include "JsonResponsePacketSerializer.h"

// Function will serialize the login message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse res)
{
	json loginJson = json({ "status", res.status });	
	return createResponse(loginCode, loginJson.dump(), loginJson.dump().length());
}

// Function will serialize the signup message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse res)
{
	json signupJson = json({ "status", res.status });
	return createResponse(signupCode, signupJson.dump(), signupJson.dump().length());
}

// Function will serialize the error message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse res)
{
	json errorJson = json({ "message", res.message });
	return createResponse(errorCode, errorJson.dump(), errorJson.dump().length());
}

// Function will serialize the logout message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse res)
{
	json logoutJson = json({ "status", res.status });
	return createResponse(logoutCode, logoutJson.dump(), logoutJson.dump().length());
}

// Function will serialize the get room message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse res)
{
	string roomsStr = "";
	for (int i = 0; i < res.rooms.size() - 1; i++)
	{
		roomsStr += res.rooms[i].getName();
		if (i != res.rooms.size() - 1)
		{
			roomsStr += ", ";
		}
	}
	json getRoomJson = json({ "Rooms", roomsStr });
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
	json getPlayersInRoomJson = json({ "PlayersInRoom", playersStr });
	return createResponse(getPlayersInCode, getPlayersInRoomJson.dump(), getPlayersInRoomJson.dump().length());
}

// Function will serialize the join room message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse res)
{
	json joinRoomJson = json({ "status", res.status });
	return createResponse(joinRoomCode, joinRoomJson.dump(), joinRoomJson.dump().length());
}

// Function will serialize the create room message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse res)
{
	json createRoomJson = json({ "status", res.status });
	return createResponse(createRoomCode, createRoomJson.dump(), createRoomJson.dump().length());
}

// Function will serialize the get statistics message
vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse res)
{
	// TODO
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
