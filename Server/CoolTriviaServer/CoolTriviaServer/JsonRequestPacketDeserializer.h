#pragma once

#include "IRequestHandler.h"
#include "Helper.h"
#include <typeinfo>

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(vector<unsigned char> Buffer);
	static SignupRequest deserializeSignupRequest(vector<unsigned char> Buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(vector<unsigned char> Buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(vector<unsigned char> Buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(vector<unsigned char> Buffer);
	static SubmitAnswerRequest deserialideserializerSubmitAnswerRequestzeLoginRequest(vector<unsigned char> Buffer);
};

