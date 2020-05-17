#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Helper.h"
#include "consts.h"

using std::string;
using std::vector;

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

	static vector<unsigned char> serializeLoginResponse(LoginResponse res);
	static vector<unsigned char> serializeSignUpResponse(SignupResponse res);
	static vector<unsigned char> serializeErrorResponse(ErrorResponse res);
	static vector<unsigned char> createResponse(int codeBit, string jsonString, int length);

};
