#include "GameRequestHandler.h"

RequestResult GameRequestHandler::getQuestion(RequestInfo info)
{
	return RequestResult();
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo info)
{
	return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	GetGameResultsResponse gameResultReponse;
	vector<Room> rooms;

	handler = m_handlerFactory.createMenuRequestHandler(this->m_user);

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(gameResultReponse);

	RequestResult result = { answer, handler };
	return result;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo info)
{
	IRequestHandler* handler;
	vector<unsigned char> answer;
	LeaveGameResponse leaveGameReponse = { successStatus };
	vector<Room> rooms;

	this->m_game.removePlayer(this->m_user.getUsername());

	handler = m_handlerFactory.createMenuRequestHandler(this->m_user);

	// serialize new answer
	answer = JsonResponsePacketSerializer::serializeResponse(leaveGameReponse);

	RequestResult result = { answer, handler };
	return result;
}

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& handlerFactory, Game game, LoggedUser user) : m_handlerFactory(handlerFactory), m_user(user), m_game(game), m_gameManager(handlerFactory.getGameManager())
{
}

GameRequestHandler::~GameRequestHandler()
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo info)
{
	return info.id == leaveGameCode ||
		info.id == getQuestionCode ||
		info.id == submitAnswerCode ||
		info.id == getGameResultCode;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo info)
{
	IRequestHandler* nextHandler;
	RequestResult result;
	vector<unsigned char> answer;
	ErrorResponse errorReponse;

	try
	{
		switch (info.id)
		{
		case leaveGameCode:
			result = this->leaveGame(info);

			break;
		case getQuestionCode:
			result = this->getQuestion(info);

			break;
		case submitAnswerCode:
			result = this->submitAnswer(info);

			break;
		case getGameResultCode:
			result = this->getGameResults(info);

			break;
		default:
			nextHandler = nullptr;
			errorReponse = { "ERROR" };
			answer = JsonResponsePacketSerializer::serializeResponse(errorReponse);
			result = { answer , nextHandler };
			break;
		}
	}
	catch (const std::exception&)
	{
		nextHandler = nullptr;
		errorReponse = { "ERROR" };
		answer = JsonResponsePacketSerializer::serializeResponse(errorReponse);
		result = { answer , nextHandler };
	}
	return result;
}
