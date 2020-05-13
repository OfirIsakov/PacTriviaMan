#pragma once

#include "IRequestHandler.h"
#include "Helper.h"

class JsonRequestPacketDeserializer
{

	static LoginRequest deserializeLoginRequest(unsigned char* Buffer);
	static SignupRequest deserializeSignupRequest(unsigned char* Buffer);
};

