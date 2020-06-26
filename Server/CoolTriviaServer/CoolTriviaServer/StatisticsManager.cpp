#include "StatisticsManager.h"

// Function will return the statistics 
// The syntax of the vector:
// {user1:bestscore1, user2:bestscore2, user3:bestscore3, user4:bestscore4, user5:bestscore5, user1:numOfGames:TotalAnswers:TotalCorrectAnswers:AvgTimeForAnswer, ...}
// If there are less than 5 users, the left spaces (from the top 5) will be "0"
vector<string> StatisticsManager::getStatistics(string username)
{
	vector<string> topFive;

	topFive = m_database->getTopFive();

	topFive.push_back(getUserStats(username));
	
	return topFive; // Final vector
}

// Function will return all the statistics of the user
string StatisticsManager::getUserStats(string username)
{
	return username + ":" + to_string(m_database->getNumOfPlayerGames(username))
					+ ":" + to_string(m_database->getNumOfTotalAnswers(username))
					+ ":" + to_string(m_database->getNumOfCorrectAnswers(username))
					+ ":" + to_string(m_database->getPlayerAverageAnswerTime(username));
}