#pragma once
#include <string>
#include <io.h>
#include <iostream>
#include <vector>
#include "IDatabase.h"
#include "sqlite3.h"
#include "consts.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

class SqliteDataBase : public IDatabase
{
public:
	// Ctor & Dtor
	SqliteDataBase();
	~SqliteDataBase();

	virtual bool doesUserExist(string username);
	virtual bool doesPasswordMatch(string, string);
	virtual void addNewUser(string, string, string);

private:
	
	sqlite3* _db;

	void openDB();
	void closeDB();

	int changeDB(const std::string command) const;

	// callbacks
	static int getVectorStringCB(void* data, int argc, char** argv, char** azColName);
	static int getStringCB(void* data, int argc, char** argv, char** azColName);
};

