#include "RoomManager.h"

RoomManager::RoomManager()
{
	m_rooms = map<int, Room>();
}

RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(LoggedUser owner, RoomData data)
{
	int lastId = this->m_rooms.rbegin()->first;
	this->m_rooms.emplace(lastId + 1, Room(data));
}

void RoomManager::deleteRoom(int ID)
{
	if (this->m_rooms.find(ID) != this->m_rooms.end()) {
		this->m_rooms.erase(this->m_rooms.find(ID));
	}
}

unsigned int RoomManager::getRoomState(int ID)
{
	return this->m_rooms.find(ID)->second.GetData().isActive;
}

vector<RoomData> RoomManager::getRooms()
{
	vector<RoomData> rooms = vector<RoomData>();

	for (auto &room : this->m_rooms)
	{
		rooms.push_back(room.second.GetData());
	}

	return rooms;
}
