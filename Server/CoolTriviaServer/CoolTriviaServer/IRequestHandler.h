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

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
