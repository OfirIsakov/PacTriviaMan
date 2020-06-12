#pragma once

#include <vector>
#include "LoggedUser.h"
#include "RoomIsFullException.h"

typedef struct RoomData
{
	unsigned int id;
	string name;
	int maxPlayers;
	unsigned int timePerQuestion;
	unsigned int isActive;
} RoomData;

using std::vector;
using std::find;

class Room
{
	RoomData m_metadata;
	vector<LoggedUser> m_users;

public:
	Room(RoomData data);
	~Room();

	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	vector<string> getAllUsers();

	// getters
	RoomData GetData();

};

