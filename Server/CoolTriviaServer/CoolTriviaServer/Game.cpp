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

// Function will submit the answer and change the gamedata according to the answer
void Game::submitAnswer(LoggedUser user, string answer)
{
	for (auto& player : m_players)
	{
		if (((LoggedUser)player.first).getUsername() == user.getUsername())
		{
			if (player.second.currentQuestion.getCorrentAnswer() == answer)
			{
				player.second.correctAnswerCount += 1;
			}
			else
			{
				player.second.wrongAnswerCount += 1;
			}
		}
	}
}

void Game::removePlayer(LoggedUser user)
{
}
