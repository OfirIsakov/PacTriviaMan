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
	Room room = Room(data);
	room.addUser(owner);
	this->m_rooms.emplace(data.id, room);
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
		return this->m_rooms.find(ID)->second.getData().isActive;
	}
	throw InvalidRoomIdException();
}

void RoomManager::setRoomState(int ID, int state)
{
	RoomData data = this->getRoom(ID).getData();
	data.isActive = state;
	this->getRoom(ID).setData(data);
}

vector<RoomData> RoomManager::getRoomsData()
{
	vector<RoomData> rooms = vector<RoomData>();

	for (auto &room : this->m_rooms)
	{
		rooms.push_back(room.second.getData());
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
