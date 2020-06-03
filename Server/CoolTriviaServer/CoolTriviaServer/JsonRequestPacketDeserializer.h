#pragma once

#include "IRequestHandler.h"
#include "Helper.h"

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(vector<unsigned char> Buffer);
	static SignupRequest deserializeSignupRequest(vector<unsigned char> Buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(vector<unsigned char> Buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(vector<unsigned char> Buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(vector<unsigned char> Buffer);
};

