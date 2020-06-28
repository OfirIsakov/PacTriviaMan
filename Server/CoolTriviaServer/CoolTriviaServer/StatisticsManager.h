#pragma once

#include "SqliteDataBase.h"

using std::ostringstream;

class StatisticsManager
{
public:

	StatisticsManager(IDatabase* m_database);
	~StatisticsManager();

	vector<string> getStatistics(string username);

private:
	IDatabase* m_database;
	string getUserStats(string username);
};

