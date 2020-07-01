#pragma once
#include <iostream>
#include <map>
#include "Question.h"
#include "LoggedUser.h"

typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount = 0;
	unsigned int wrongAnswerCount = 0;
	unsigned int averageAnswerTime;
} GameData;

using std::map;

class Game
{
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
public:
	Game();
	~Game();

	void getQuestionForUser(LoggedUser user);
	void submitAnswer(LoggedUser user, string answer);
	void removePlayer(LoggedUser user);
};

