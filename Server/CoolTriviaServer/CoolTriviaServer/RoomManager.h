#pragma once

#include "Room.h"
#include "InvalidRoomIdException.h"
#include <map>

using std::map;

class RoomManager
{
	map<int, Room> m_rooms; // map<ID, Room>
public:
	RoomManager();
	~RoomManager();

	void createRoom(LoggedUser owner, RoomData data);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	void setRoomState(int ID, int state);
	vector<RoomData> getRoomsData();
	vector<Room> getRooms();
	Room getRoom(int ID);
};

