#include "SqliteDataBase.h"

// SqliteDataBase Constructor
SqliteDataBase::SqliteDataBase()
{
	openDB();
}

// SqliteDataBase Destructor
SqliteDataBase::~SqliteDataBase()
{
	closeDB();
}

// Function will open the data base
void SqliteDataBase::openDB()
{
	string dbName = DB_FILE_NAME;
	string insertQuestions = "";
	int existDB = _access(dbName.c_str(), 0);
	int res = sqlite3_open(dbName.c_str(), &this->_db);
	if (res != SQLITE_OK)
	{
		this->_db = nullptr;
		throw runtime_error("Can't Open DB");
	}
	if (existDB == -1) // create a new one
	{
		for (auto& command : SET_DB)
		{
			changeDB(command);
		}
		insertQuestions = createInsertQuery();
		changeDB(insertQuestions);
	}
}

// Function will create the query of insert the questions
string SqliteDataBase::createInsertQuery()
{
	string query = "INSERT INTO Questions (question, correct_ans, ans1, ans2, ans3) VALUES ";
	for (int i = 0; i < NUM_OF_Q; i++)
	{
		query += "( ";
		for (int j = 0; j < NUM_OF_DETAILS; j++)
		{
			query += QUES_ANS[i][j];
			if (j != NUM_OF_DETAILS - 1) // Check is it the last element
			{
				query += ",";
			}
		}
		query += " )";
		if (i != NUM_OF_Q - 1) // Check if it the last question
		{
			query += ",";
		}
		else
		{
			query += ";";
		}
	}
	return query;
}

// Function will close the database
void SqliteDataBase::closeDB()
{
	sqlite3_close(this->_db);
	this->_db = nullptr;
}

// Function will add things to the database by the command
int SqliteDataBase::changeDB(const string command) const
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(this->_db, command.c_str(), nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return -1;
	}
	return 0;
}

// Function will check if the user is exist
bool SqliteDataBase::doesUserExist(string username)
{
	// get the users
	string getUsersCmd = "SELECT COUNT(*) FROM Users WHERE username = \"" + username + "\";";
	int usernames;
	char* errMessage;
	int res = sqlite3_exec(this->_db, getUsersCmd.c_str(), getIntCB, &usernames, &errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return true; // avoid to insert new user
	}

	return usernames != 0;
}

// Function will check if the password is match to the user
bool SqliteDataBase::doesPasswordMatch(string username, string password)
{
	string userPassword;
	string getUserPassCmd = "SELECT password FROM Users WHERE username = \"" + username + "\";";
	char* errMessage;
	int res = sqlite3_exec(this->_db, getUserPassCmd.c_str(), getStringCB, &userPassword, &errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return true;  // avoid to insert new user
	}
	return userPassword.compare(password) == 0;
}

// Function will add to the DB a new user
void SqliteDataBase::addNewUser(string username, string passsword, string mail)
{
	if (doesUserExist(username))
	{
		throw UserAlreadyExistsException();
	}
	string addUserCmd = "INSERT INTO Users (username, password, mail) VALUES (\"" + username + "\", \"" + passsword + "\", \"" + mail + "\");";

	changeDB(addUserCmd);
}

// Function is a callback that return int
int SqliteDataBase::getIntCB(void* data, int argc, char** argv, char** azColName)
{
	int* num = static_cast<int*>(data);
	if (argc > 0)
		*num = stoi(argv[0]);
	else
		*num = 0;
	return 0;
}

// Function is a callback that order the usernames
int SqliteDataBase::getStringCB(void* data, int argc, char** argv, char** azColName)
{
	string* str = reinterpret_cast<string*>(data);
	if (argc > 0)
		*str = argv[0];
	else
		*str = "";
	return 0;
}

// Function will return the average answer time of the user
float SqliteDataBase::getPlayerAverageAnswerTime(string username)
{
	string getAvgTimesCmd = "SELECT AVG(answer_time) FROM Data WHERE username = \"" + username + "\";";
	string avgStr = "";
	char* errMessage;
	int res = sqlite3_exec(this->_db, getAvgTimesCmd.c_str(), getStringCB, &avgStr, &errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return ERROR;
	}
	return stof(avgStr);
}

// Function will return number of correct answers of the user
int SqliteDataBase::getNumOfCorrectAnswers(string username)
{
	string getCorrectAnsCmd = "SELECT question_id FROM Data WHERE username = \"" + username + "\" AND is_correct = 1;";
	vector<int>* correctAnswers;
	char* errMessage;
	int res = sqlite3_exec(this->_db, getCorrectAnsCmd.c_str(), getIntVectorCB, &correctAnswers, &errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return ERROR;
	}
	return correctAnswers->size();
}

// Function will return the number of total answers of the user
int SqliteDataBase::getNumOfTotalAnswers(string username)
{
	string getAnswersCmd = "SELECT question_id FROM Data WHERE username = \"" + username + "\";";
	vector<int>* answers;
	char* errMessage;
	int res = sqlite3_exec(this->_db, getAnswersCmd.c_str(), getIntVectorCB, &answers, &errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return ERROR;
	}
	return answers->size();
}

// Function will return the number of games that the user took part in
int SqliteDataBase::getNumOfPlayerGames(string username)
{
	string getGamesCmd = "SELECT game_id FROM Data WHERE username = \"" + username + "\" ORDER BY game_id ASC;";
	vector<int> games;
	char* errMessage;
	int res = sqlite3_exec(this->_db, getGamesCmd.c_str(), getIntVectorCB, &games, &errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return ERROR;
	}

	return set<int>(games.begin(), games.end()).size(); // ignore the duplicates
}

// Function is a callback that return Vector of int by the command
int SqliteDataBase::getIntVectorCB(void* data, int argc, char** argv, char** azColName)
{
	vector<int>* vec = reinterpret_cast<vector<int>*>(data);
	for (int i = 0; i < argc; i++)
	{
		vec->push_back(stoi(argv[i]));
	}

	return 0;
}

// Function will return all the users
vector<string> SqliteDataBase::getUsernames()
{
	string getUsersCmd = "SELECT username FROM Users";
	vector<string> usernames;
	char* errMessage;
	int res = sqlite3_exec(this->_db, getUsersCmd.c_str(), getStringVectorCB, &usernames, &errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return vector<string>();
	}
	return usernames;
}

// Function is a callback that return a vector of strings
int SqliteDataBase::getStringVectorCB(void* data, int argc, char** argv, char** azColName)
{
	vector<string>* vec = reinterpret_cast<vector<string>*>(data);
	for (int i = 0; i < argc; i++)
	{
		vec->push_back(argv[i]);
	}
	return 0;
}

// Function will return the top 5 players with the highest score 
vector<string> SqliteDataBase::getTopFive()
{
	int res, counter = 0;
	char* errMessage;
	vector<string> usernames = getUsernames(), result;
	map<int, string> resultMap;
	// Get the scores
	for (auto& username : usernames)
	{
		resultMap.insert(pair<int, string>(getNumOfCorrectAnswers(username), username));
	}
	// Keep the top 5
	map<int, string>::iterator it = resultMap.begin();
	int len = resultMap.size();
	for (int i = 0; i < len - 5; i++) {
		resultMap.erase(it);
		it = resultMap.begin();
	}
	if (resultMap.size() < 5) // In case that there are less than 5 players
	{
		for (int i = 0; i < 5 - len; i++)
		{
			resultMap.insert(pair<int, string>(0, ""));
		}
	}
	// Parse the map to vector
	for (int i = 0; i < 5; i++)
	{
		result.push_back(it->second + ":" + to_string(it->first));
		it++;
	}

	return result;
}