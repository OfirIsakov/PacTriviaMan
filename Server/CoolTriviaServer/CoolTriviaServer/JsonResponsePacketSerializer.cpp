#include "JsonResponsePacketSerializer.h"

// Function will serialize the login message
unsigned char* JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse res)
{
	json signupJson = json({ "status", res.status });
	string stringBuffer;
	int bufferLength = signupJson.dump().length() + 5;
	unsigned char* buffer = new unsigned char[bufferLength];
	std::fill(buffer, buffer + signupJson.dump().length() + 5, '\0'); // reseting the array

	// code bit
	char codeBuffer[2] = { 0 };
	codeBuffer[0] = (char)login;
	stringBuffer += string(codeBuffer);

	// length bit
	char* tmp;
	tmp = (char*)Helper::convertIntToFourBytes(signupJson.dump().length());
	stringBuffer += string(tmp, 4);

	// json bit
	stringBuffer += string(signupJson.dump().c_str(), signupJson.dump().length());

	for (int i = 0; i < bufferLength; i++) {
		buffer[i] = stringBuffer[i];
	}

	return buffer;
}

// Function will serialize the signup message
unsigned char* JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse res)
{
	json signupJson = json({ "status", res.status });
	string stringBuffer;
	int bufferLength = signupJson.dump().length() + 5;
	unsigned char* buffer = new unsigned char[bufferLength];
	std::fill(buffer, buffer + signupJson.dump().length() + 5, '\0'); // reseting the array

	// code bit
	char codeBuffer[2] = { 0 };
	codeBuffer[0] = (char)signup;
	stringBuffer += string(codeBuffer);

	// length bit
	char* tmp;
	tmp = (char*)Helper::convertIntToFourBytes(signupJson.dump().length());
	stringBuffer += string(tmp, 4);

	// json bit
	stringBuffer += string(signupJson.dump().c_str(), signupJson.dump().length());

	for (int i = 0; i < bufferLength; i++) {
		buffer[i] = stringBuffer[i];
	}

	return buffer;
}

// Function will serialize the error message
unsigned char* JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse res)
{
	json errorJson = json({ "message", res.message });
	string stringBuffer;
	int bufferLength = errorJson.dump().length() + 5;
	unsigned char* buffer = new unsigned char[bufferLength];
	std::fill(buffer, buffer + errorJson.dump().length() + 5, '\0'); // reseting the array

	// code bit
	char codeBuffer[2] = { 0 };
	codeBuffer[0] = (char)error;
	stringBuffer += string(codeBuffer);

	// length bit
	char* tmp;
	tmp = (char*)Helper::convertIntToFourBytes(errorJson.dump().length());
	stringBuffer += string(tmp, 4);

	// json bit
	stringBuffer += string(errorJson.dump().c_str(), errorJson.dump().length());

	for (int i = 0; i < bufferLength; i++) {
		buffer[i] = stringBuffer[i];
	}

	return buffer;
}