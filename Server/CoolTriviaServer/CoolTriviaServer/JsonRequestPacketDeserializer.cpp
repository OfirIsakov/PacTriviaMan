#include "JsonRequestPacketDeserializer.h"

// Function will deserialize the login buffer and returns the login struct
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<unsigned char> Buffer)
{
	string jsonBuffer(Buffer.begin(), Buffer.end());
	json messageInfo = json::parse(jsonBuffer);

	LoginRequest request = { messageInfo.at("username"), messageInfo.at("password") };

	return request;
}

// Function will deserialize the signup buffer and returns the signup struct
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<unsigned char> Buffer)
{
	string jsonBuffer(Buffer.begin(), Buffer.end());
	json messageInfo = json::parse(jsonBuffer);

	SignupRequest request = { messageInfo.at("username"), messageInfo.at("password"), messageInfo.at("mail") };

	return request;
}
