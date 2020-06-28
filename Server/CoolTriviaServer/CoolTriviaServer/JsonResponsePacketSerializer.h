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

typedef struct CloseRoomResponse
{
	unsigned int status;
} CloseRoomResponse;

typedef struct StartGameResponse
{
	unsigned int status;
} StartGameResponse;

typedef struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
} GetRoomStateResponse;

typedef struct LeaveRoomResponse
{
	unsigned int status;
} LeaveRoomResponse;




class JsonResponsePacketSerializer
{
public:

	// V1
	static vector<unsigned char> serializeResponse(LoginResponse res);
	static vector<unsigned char> serializeResponse(SignupResponse res);
	static vector<unsigned char> serializeResponse(ErrorResponse res);
	static vector<unsigned char> serializeResponse(LogoutResponse res);
	// V2.0.0
	static vector<unsigned char> serializeResponse(GetRoomsResponse res);
	static vector<unsigned char> serializeResponse(GetPlayersInRoomResponse res);
	static vector<unsigned char> serializeResponse(JoinRoomResponse res);
	static vector<unsigned char> serializeResponse(CreateRoomResponse res);
	static vector<unsigned char> serializeResponse(GetStatisticsResponse res);
	// V3.0.0
	static vector<unsigned char> serializeResponse(CloseRoomResponse res);
	static vector<unsigned char> serializeResponse(StartGameResponse res);
	static vector<unsigned char> serializeResponse(GetRoomStateResponse res);
	static vector<unsigned char> serializeResponse(LeaveRoomResponse res);

	// General create response
	static vector<unsigned char> createResponse(int codeBit, string jsonString, int length);

private:

	static vector<unsigned char> serializeStatusMsg(int code, unsigned int status);
};
