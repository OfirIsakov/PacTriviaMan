#pragma once

#include <string>
#include "Helper.h"
#include "consts.h"

using std::string;

typedef struct LoginResponse
{
	unsigned int status;
} LoginResponse;

typedef struct SignupResponse
{
	unsigned int status;
} SignupResponse;

typedef struct ErrorResponse
{
	string message;
} ErrorResponse;


class JsonResponsePacketSerializer
{
public:

	static unsigned char* serializeLoginResponse(LoginResponse res);
	static unsigned char* serializeSignUpResponse(SignupResponse res);
	static unsigned char* serializeErrorResponse(ErrorResponse res);

};
