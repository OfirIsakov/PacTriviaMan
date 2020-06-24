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
	this->m_rooms.emplace(data.id, Room(data));
}

void RoomManager::deleteRoom(int ID)
{
	if (this->m_rooms.find(ID) != this->m_rooms.end()) {
		this->m_rooms.erase(this->m_rooms.find(ID));
	}
}

unsigned int RoomManager::getRoomState(int ID)
{
	if (this->m_rooms.find(ID) != this->m_rooms.end()) {
		return this->m_rooms.find(ID)->second.GetData().isActive;
	}
	throw InvalidRoomIdException();
}

vector<RoomData> RoomManager::getRoomsData()
{
	vector<RoomData> rooms = vector<RoomData>();

	for (auto &room : this->m_rooms)
	{
		rooms.push_back(room.second.GetData());
	}

	return rooms;
}

vector<Room> RoomManager::getRooms()
{
	vector<Room> rooms = vector<Room>();

	for (auto& room : this->m_rooms)
	{
		rooms.push_back(room.second);
	}

	return rooms;
}

Room RoomManager::getRoom(int ID)
{
	if (this->m_rooms.find(ID) != this->m_rooms.end()) {
		return this->m_rooms.find(ID)->second;
	}
	throw InvalidRoomIdException();
}
