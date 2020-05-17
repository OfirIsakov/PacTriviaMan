#include "JsonResponsePacketSerializer.h"

// Function will serialize the login message
unsigned char* JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse res)
{
	json loginJson = json::parse("{\"status\":" + std::to_string(res.status) + "}");
	unsigned char* buffer = new unsigned char[loginJson.dump.length() + 5];

	buffer = (char)login + Helper::convertIntToFourBytes(loginJson.dump.length()) + loginJson.dump;
	return buffer;
}

// Function will serialize the signup message
unsigned char* JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse res)
{
	json signupJson = json::parse("{\"status\":" + std::to_string(res.status) + "}");
	unsigned char* buffer = new unsigned char[signupJson.dump.length() + 5];

	buffer = (char)signup + Helper::convertIntToFourBytes(signupJson.dump.length()) + signupJson.dump;
	return buffer;
}

// Function will serialize the error message
unsigned char* JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse res)
{
	json errorJson = json::parse("{\"message\":" + res.message + "}");
	unsigned char* buffer = new unsigned char[errorJson.dump.length() + 5];

	buffer = (char)error + Helper::convertIntToFourBytes(errorJson.dump.length()) + errorJson.dump;
	return buffer;
}