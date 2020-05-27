#pragma once
#include <string>
#include <io.h>
#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "CantCreateUserException.h"
#include "sqlite3.h"
#include "consts.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::runtime_error;
using std::stoi;

class SqliteDataBase : public IDatabase
{
public:
	// Ctor & Dtor
	SqliteDataBase();
	~SqliteDataBase();

	virtual bool doesUserExist(string username);
	virtual bool doesPasswordMatch(string username, string password);
	virtual void addNewUser(string username, string password, string mail);

private:
	
	sqlite3* _db;

	void openDB();
	void closeDB();

	int changeDB(const std::string command) const;

	// callbacks
	static int countCB(void* data, int argc, char** argv, char** azColName);
	static int getStringCB(void* data, int argc, char** argv, char** azColName);
};

