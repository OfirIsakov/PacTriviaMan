#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory), m_loginManager(handlerFactory.getLoginManager())
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == loginCode || info.id == signupCode;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
	IRequestHandler* nextHandler;
	RequestResult result;
	vector<unsigned char> answer;
	ErrorResponse errorReponse;

	switch (info.id)
	{
	case signupCode:
		result = this->signup(info);

		break;
	case loginCode:
		result = this->login(info);

		break;
	default:
		nextHandler = nullptr;
		errorReponse = { "ERROR" };
		answer = JsonResponsePacketSerializer::serializeResponse(errorReponse);
		result = { answer , nextHandler };
		break;
	}
	return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	SignupResponse signupReponse;

	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(info.buffer); // deserialize the buffer

	try
	{
		this->m_loginManager.signup(signupRequest.username, signupRequest.password, signupRequest.mail);
		signupReponse = { successStatus };
	}
	catch (const UserAlreadyExistsException&)
	{
		signupReponse = { userExists };
	}
	catch (const exception&)
	{
		signupReponse = { wrongDataStatus };
	}
	handler = nullptr;

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(signupReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult LoginRequestHandler::login(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	LoginResponse loginReponse;

	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer); // deserialize the buffer

	try
	{
		this->m_loginManager.login(loginRequest.username, loginRequest.password);
		handler = m_handlerFactory.createMenuRequestHandler(loginRequest.username);
		loginReponse = { successStatus };
	}
	catch (const AlreadyLoggedInException&)
	{
		handler = nullptr;
		loginReponse = { alreadyConnectedStatus};
	}
	catch (const exception&)
	{
		handler = nullptr;
		loginReponse = { wrongDataStatus };
	}

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(loginReponse);

	RequestResult result = { answer, handler };
	return result;
}
