#include "JsonResponsePacketSerializer.h"


unsigned char* JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse res)
{
	json loginJson = json::parse("{\"status\":" + std::to_string(res.status) + "}");
	unsigned char* buffer[loginJson.dump.length() + 5];
	buffer[0] = (char)login;

	return buffer;
}

unsigned char* JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse res)
{
	json signupJson = json::parse("{\"status\":" + std::to_string(res.status) + "}");
	int jsonStringLen = signupJson.dump.length();
	unsigned char* buffer[signupJson.dump.length() + 5];
	
	buffer[0] = (char)signup;
	// helper
	char arr[4];

	buffer[1] = (signupJson.dump.length() >> 24) & 0xFF;
	buffer[2] = (signupJson.dump.length() >> 16) & 0xFF;
	buffer[3] = (signupJson.dump.length() >> 8) & 0xFF;
	buffer[4] = signupJson.dump.length() & 0xFF;


	return buffer;
}

unsigned char* serializeErrorResponse(ErrorResponse res)
{

}