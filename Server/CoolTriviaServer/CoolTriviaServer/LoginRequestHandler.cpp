#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == LOGIN || info.id == SIGNUP;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	//TODO serilize an answer to the client and make the next state for the user
	RequestResult result = {  };
	return result;
}
