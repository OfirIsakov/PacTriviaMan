#pragma once

#include <iostream>
#include <vector>
#include <ctime>

using std::string;
using std::time_t;
using std::vector;
class IRequestHandler;

typedef struct RequestInfo
{
	int id; // message code
	time_t receivalTime; // seconds since epoch
	vector<unsigned char> buffer;
} RequestInfo;

typedef struct RequestResult
{
	vector<unsigned char> response;
	IRequestHandler* newHandler;
} RequestResult;

typedef struct LoginRequest
{
	string username;
	string password;
} LoginRequest;

typedef struct SignupRequest
{
	string username;
	string password;
	string mail;
} SignupRequest;

typedef struct GetPlayersInRoomRequest
{
	unsigned int roomId;
} GetPlayersInRoomRequest;

typedef struct JoinRoomRequest
{
	unsigned int roomId;
} JoinRoomRequest;

typedef struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
} CreateRoomRequest;

typedef struct SubmitAnswerRequest
{
	unsigned int answerId;
} SubmitAnswerRequest;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
