#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(vector<unsigned char> Buffer)
{
	string jsonBuffer(Buffer.begin(), Buffer.end());
	json messageInfo = json::parse(jsonBuffer);

	LoginRequest request = { messageInfo.at("username"), messageInfo.at("password") };

	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(vector<unsigned char> Buffer)
{
	//for (const unsigned char& c : Buffer)
	//	std::cout << c;

	string jsonBuffer(Buffer.begin(), Buffer.end());
	json messageInfo = json::parse(jsonBuffer);

	SignupRequest request = { messageInfo.at("username"), messageInfo.at("password"), messageInfo.at("mail") };

	return request;
}
