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
		answer = JsonResponsePacketSerializer::serializeErrorResponse(errorReponse);
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
	}
	catch (const std::exception&)
	{
		// currenty not doing anything here because you need to login after singup
	}
	handler = new LoginRequestHandler(this->m_handlerFactory);

	// serialize new answer
	signupReponse = { 1 };
	answer = JsonResponsePacketSerializer::serializeSignUpResponse(signupReponse);

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
		handler = new MenuRequestHandler();
	}
	catch (const std::exception&)
	{
		handler = new LoginRequestHandler(this->m_handlerFactory);
	}

	// serialize new answer
	loginReponse = { 1 };
	answer = JsonResponsePacketSerializer::serializeLoginResponse(loginReponse);

	RequestResult result = { answer, handler };
	return result;
}
