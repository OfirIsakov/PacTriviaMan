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
	for (auto &a: Buffer) {
		std::cout << a;
	}
	std::cout << std::endl;
	json messageInfo = json::parse(Buffer.begin(), Buffer.end());

	SignupRequest request = { messageInfo.at("username"), messageInfo.at("password"), messageInfo.at("mail") };

	return request;
}
