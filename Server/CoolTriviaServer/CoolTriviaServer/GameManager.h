#pragma once
#include "IDatabase.h"
#include "Room.h"
#include "Game.h"

class GameManager
{
	IDatabase* m_database;
	vector<Game> m_games;
public:
	Game createGame(Room room);
	void deleteGame(Game game);
};

