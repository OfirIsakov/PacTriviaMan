#pragma once

// server settings
#define PORT 8820
#define IP "127.0.0.1"

// Database settings
#define DB_FILE_NAME "triviaDB.sqlite"

// message codes
enum messageCodes
{
	signup = 1,
	login = 2,
	error = 3
};

// protocol consts
enum protocolParts
{
	partCode = 1,
	partJsonLength = 4
};
