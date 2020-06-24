#include "StatisticsManager.h"

// Function will return the statistics 
// The syntax of the vector:
// {user1:bestscore1, user2:bestscore2, user3:bestscore3, user4:bestscore4, user5:bestscore5, user1:numOfGames:TotalAnswers:TotalCorrectAnswers:AvgTimeForAnswer, ...}
// If there are less than 5 users, the left spaces (from the top 5) will be "0"
vector<string> StatisticsManager::getStatistics()
{
	vector<string> topFive, usersStatistics;

	topFive = m_database->getTopFive();
	usersStatistics = getUsersStatistics();

	topFive.insert(topFive.end(), usersStatistics.begin(), usersStatistics.end());
	
	return topFive; // The concatenated vector
}

// Function will return the statistics of all the users
vector<string> StatisticsManager::getUsersStatistics()
{
	vector<string> result, usernames = m_database->getUsernames();

	for (auto& username : usernames)
	{
		result.push_back(getUserStats(username));
	}
	return result;
}

// Function will return all the statistics of the user
string StatisticsManager::getUserStats(string username)
{
	return username + ":" + to_string(m_database->getNumOfPlayerGames(username))
					+ ":" + to_string(m_database->getNumOfTotalAnswers(username))
					+ ":" + to_string(m_database->getNumOfCorrectAnswers(username))
					+ ":" + to_string(m_database->getPlayerAverageAnswerTime(username));
}