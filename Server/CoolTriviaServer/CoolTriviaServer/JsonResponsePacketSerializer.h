#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "Helper.h"
#include "Room.h"
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

typedef struct LogoutResponse
{
	unsigned int status;
} LogoutResponse;

typedef struct GetRoomsResponse
{
	unsigned int status;
	vector<RoomData> rooms;
} GetRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	vector<string> players;
} GetPlayersInRoomResponse;

typedef struct GetStatisticsResponse
{
	unsigned int status;
	vector<string> statistics;
} GetStatisticsResponse;

typedef struct JoinRoomResponse
{
	unsigned int status;
} JoinRoomResponse;

typedef struct CreateRoomResponse
{
	unsigned int status;
} CreateRoomResponse;


class JsonResponsePacketSerializer
{
public:

	static vector<unsigned char> serializeResponse(LoginResponse res);
	static vector<unsigned char> serializeResponse(SignupResponse res);
	static vector<unsigned char> serializeResponse(ErrorResponse res);
	static vector<unsigned char> serializeResponse(LogoutResponse res);
	static vector<unsigned char> serializeResponse(GetRoomsResponse res);
	static vector<unsigned char> serializeResponse(GetPlayersInRoomResponse res);
	static vector<unsigned char> serializeResponse(JoinRoomResponse res);
	static vector<unsigned char> serializeResponse(CreateRoomResponse res);
	static vector<unsigned char> serializeResponse(GetStatisticsResponse res);


	static vector<unsigned char> createResponse(int codeBit, string jsonString, int length);

};
