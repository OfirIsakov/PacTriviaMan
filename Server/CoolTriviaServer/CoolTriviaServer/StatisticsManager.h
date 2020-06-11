#pragma once

#include <sstream>
#include "SqliteDataBase.h"

using std::ostringstream;

class StatisticsManager
{
public:

	vector<string> getStatistics();

private:
	IDatabase* m_database;

	vector<string> getTopFive();
	vector<string> getUsersStatistics();
	string getUserStats(string username);
};

