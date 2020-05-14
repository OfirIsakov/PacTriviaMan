#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == login || info.id == signup;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	//TODO serilize an answer to the client and add the next state for the user
	RequestResult result = {  }; //TODO The new state should be `MenuRequestHandler` but in this current version its not implemented or declared
	return result;
}
