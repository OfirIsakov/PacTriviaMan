#include "Room.h"

Room::Room(RoomData data)
{
	m_metadata = data;
	m_users = vector<LoggedUser>();
}

Room::~Room()
{
}

void Room::addUser(LoggedUser user)
{
	if (this->m_metadata.maxPlayers > this->m_users.size()) {
		this->m_users.push_back(user);
	}
	else {
		throw RoomIsFullException();
	}
}

void Room::removeUser(LoggedUser user)
{
	for (auto it = this->m_users.begin(); it != this->m_users.end(); it++)
	{
		if (it->getUsername() == user.getUsername()) {
			this->m_users.erase(it);
			break;
		}
	}
}

vector<string> Room::getAllUsers()
{
	vector<string> userNames = vector<string>();
	for (auto &user : this->m_users) {
		userNames.push_back(user.getUsername());
	}
	return userNames;
}

RoomData Room::getData()
{
	return this->m_metadata;
}

void Room::setData(RoomData metadata)
{
	this->m_metadata = metadata;
}
