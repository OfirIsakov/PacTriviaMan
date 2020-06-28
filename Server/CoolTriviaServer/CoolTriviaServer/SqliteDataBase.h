#pragma once
#include <string>
#include <io.h>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
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
using std::stof;
using std::set;
using std::map;
using std::pair;
using std::reverse;

class SqliteDataBase : public IDatabase
{
public:
	// Ctor & Dtor
	SqliteDataBase();
	~SqliteDataBase();

	virtual bool doesUserExist(string username);
	virtual bool doesPasswordMatch(string username, string password);
	virtual void addNewUser(string username, string password, string mail);
	virtual float getPlayerAverageAnswerTime(string username);
	virtual int getNumOfCorrectAnswers(string username);
	virtual int getNumOfTotalAnswers(string username);
	virtual int getNumOfPlayerGames(string username);
	virtual vector<string> getTopUsernames();
	virtual vector<string> getTopFive();

private:

	sqlite3* _db;

	void openDB();
	void closeDB();

	int changeDB(const string command) const;

	string createInsertQuery();

	// callbacks
	static int getIntCB(void* data, int argc, char** argv, char** azColName);
	static int getStringCB(void* data, int argc, char** argv, char** azColName);
	static int getIntVectorCB(void* data, int argc, char** argv, char** azColName);
	static int getStringVectorCB(void* data, int argc, char** argv, char** azColName);
};
