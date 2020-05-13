#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(unsigned char* Buffer)
{
	json messageInfo = json::parse(Buffer);

	LoginRequest request = { messageInfo["username"], messageInfo["password"] };

	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(unsigned char* Buffer)
{
	json messageInfo = json::parse(Buffer);

	SignupRequest request = { messageInfo["username"], messageInfo["password"], messageInfo["email"] };

	return request;
}
