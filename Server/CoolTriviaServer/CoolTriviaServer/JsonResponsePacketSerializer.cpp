#include "JsonResponsePacketSerializer.h"

// Function will serialize the login message
vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse res)
{
	json loginJson = json({ "status", res.status });	
	return createResponse(login, loginJson.dump(), loginJson.dump().length());
}

// Function will serialize the signup message
vector<unsigned char> JsonResponsePacketSerializer::serializeSignUpResponse(SignupResponse res)
{
	json signupJson = json({ "status", res.status });
	return createResponse(signup, signupJson.dump(), signupJson.dump().length());
}

// Function will serialize the error message
vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse res)
{
	json errorJson = json({ "message", res.message });
	return createResponse(error, errorJson.dump(), errorJson.dump().length());
}

// Function will create the response by the correct parameters
vector<unsigned char> JsonResponsePacketSerializer::createResponse(int codeBit, string jsonString, int length)
{
	string jsonString = "";
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
