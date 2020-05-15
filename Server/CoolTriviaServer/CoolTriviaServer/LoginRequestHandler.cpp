#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == login || info.id == signup;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	SignupRequest signupRequest;
	LoginRequest loginRequest;

	SignupResponse signupReponse;
	LoginResponse loginReponse;
	ErrorResponse errorReponse;

	unsigned char* answer;
	switch (info.id)
	{
	case signup:
		signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer);
		//TODO add logic to work on buffer here

		signupReponse = { 1 };
		answer = JsonResponsePacketSerializer::serializeSignUpResponse(signupReponse);
		break;
	case login:
		loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
		//TODO add logic to work on buffer here

		loginReponse = { 1 };
		answer = JsonResponsePacketSerializer::serializeLoginResponse(loginReponse);
		break;
	default:
		errorReponse = { "ERROR" };
		answer = JsonResponsePacketSerializer::serializeErrorResponse(errorReponse);
		break;
	}
	LoginRequestHandler* nextHandler = new LoginRequestHandler(); //TODO The new state should be `MenuRequestHandler` but in this current version its not implemented  or declared
	RequestResult result = { answer, nextHandler };
	return result;
}
