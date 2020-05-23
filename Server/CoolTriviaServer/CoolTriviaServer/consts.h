#pragma once

// server settings
#define PORT 8820
#define IP "127.0.0.1"

// Database settings
#define DB_FILE_NAME "triviaDB.sqlite"

// message codes
enum messageCodes
{
	signupCode = 1,
	loginCode = 2,
	errorCode = 3
};

// protocol consts
enum protocolParts
{
	partCode = 1,
	partJsonLength = 4
};
