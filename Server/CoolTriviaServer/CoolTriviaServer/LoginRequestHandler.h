#pragma once

#include <exception>
#include "IRequestHandler.h"
#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "consts.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"

using std::exception;

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult login(RequestInfo info);
	RequestResult signup(RequestInfo info);
public:
	LoginRequestHandler(RequestHandlerFactory& m_handlerFactory);
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

};


