#pragma once
#include "IRequestHandler.h"
#include "Game.h"
#include "LoggedUser.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler :
	public IRequestHandler
{
	Game m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult getQuestion(RequestInfo info);
	RequestResult submitAnswer(RequestInfo info);
	RequestResult getGameResults(RequestInfo info);
	RequestResult leaveGame(RequestInfo info);
public:
	GameRequestHandler(RequestHandlerFactory& handlerFactory, Game game, LoggedUser user);
	~GameRequestHandler();

	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);

};

