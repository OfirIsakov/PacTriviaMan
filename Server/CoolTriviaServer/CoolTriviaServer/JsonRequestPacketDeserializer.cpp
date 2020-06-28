#include "JsonRequestPacketDeserializer.h"

// Function will deserialize the login buffer and returns the login struct
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<unsigned char> Buffer)
{
	json messageInfo = json::parse(Buffer.begin(), Buffer.end());


	LoginRequest request = { messageInfo.at("username"), messageInfo.at("password") };

	return request;
}

// Function will deserialize the signup buffer and returns the signup struct
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<unsigned char> Buffer)
{
	json messageInfo = json::parse(Buffer.begin(), Buffer.end());

	SignupRequest request = { messageInfo.at("username"), messageInfo.at("password"), messageInfo.at("mail") };

	return request;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(vector<unsigned char> Buffer)
{
	json messageInfo = json::parse(Buffer.begin(), Buffer.end());

	GetPlayersInRoomRequest request = { messageInfo.at("roomId") };

	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(vector<unsigned char> Buffer)
{
	json messageInfo = json::parse(Buffer.begin(), Buffer.end());

	JoinRoomRequest request = { messageInfo.at("roomId") };

	return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(vector<unsigned char> Buffer)
{
	json messageInfo = json::parse(Buffer.begin(), Buffer.end());

	CreateRoomRequest request = { messageInfo.at("roomName"), messageInfo.at("maxUsers"), messageInfo.at("questionCount"), messageInfo.at("answerTimeout") };

	return request;
}
