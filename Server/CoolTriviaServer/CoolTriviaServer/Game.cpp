#include "Game.h"

Game::Game()
{
	this->m_questions = vector<Question>();
	this->m_players = map<LoggedUser, GameData>();
}

Game::~Game()
{
}

void Game::getQuestionForUser(LoggedUser user)
{
	for (auto& it : this->m_players)
	{
		if (((LoggedUser)it.first).getUsername() == user.getUsername()) {
			//TODORO what i do here? return question?
			break;
		}
	}
}

void Game::submitAnswer(LoggedUser user, string answer)
{
}

void Game::removePlayer(LoggedUser user)
{
}
