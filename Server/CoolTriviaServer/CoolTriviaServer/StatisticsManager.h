#pragma once

#include <sstream>
#include "SqliteDataBase.h"

using std::ostringstream;

class StatisticsManager
{
public:

	vector<string> getStatistics(string username);

private:
	IDatabase* m_database;
	string getUserStats(string username);
};

