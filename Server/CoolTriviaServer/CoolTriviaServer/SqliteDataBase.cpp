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
	string createUsers = "", createQuestions = "", insertQuestions = "";
	int existDB = _access(dbName.c_str(), 0);
	int res = sqlite3_open(dbName.c_str(), &this->_db);
	if (res != SQLITE_OK)
	{
		this->_db = nullptr;
		throw runtime_error("Can't Open DB");
	}
	if (existDB == -1) // create a new one
	{
		createUsers = "CREATE TABLE Users (id integer PRIMARY KEY AUTOINCREMENT NOT NULL, username text NOT NULL, password text NOT NULL, mail text NOT NULL);";
		createQuestions = "CREATE TABLE Questions (id integer PRIMARY KEY AUTOINCREMENT NOT NULL, question text NOT NULL, correct_ans text NOT NULL, ans1 text NOT NULL, ans2 text NOT NULL, ans3 text NOT NULL);";
		insertQuestions = createInsertQuery();
		
		changeDB(createUsers);
		changeDB(createQuestions);
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
	string getUsersCmd = "SELECT COUNT(*) FROM USERS WHERE USERNAME = \"" + username + "\";";
	int usernames;
	char* errMessage;
	int res = sqlite3_exec(this->_db, getUsersCmd.c_str(), countCB, &usernames, &errMessage);
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
	string getUserPassCmd = "SELECT PASSWORD FROM USERS WHERE USERNAME = \"" + username + "\";";
	char* errMessage;
	int res = sqlite3_exec(this->_db, getUserPassCmd.c_str(), getStringCB, &userPassword, &errMessage);
	if (res != SQLITE_OK)
	{
		cout << errMessage << endl;
		return true; // avoid to insert new user
	}

	return userPassword.compare(password) == 0;
}

// Function will add to the DB a new user
void SqliteDataBase::addNewUser(string username, string passsword, string mail)
{
	if (doesUserExist(username))
	{
		throw CantCreateUserException();
	}
	string addUserCmd = "INSERT INTO USERS (USERNAME, PASSWORD, MAIL) VALUES (\"" + username + "\", \"" + passsword + "\", \"" + mail + "\");";

	changeDB(addUserCmd);
}

// Function is a callback that count the usernames with the same name as the new user
int SqliteDataBase::countCB(void* data, int argc, char** argv, char** azColName)
{
	int* count = static_cast<int*>(data);
	*count = stoi(argv[0]);
	return 0;
}

// Function is a callback that order the usernames
int SqliteDataBase::getStringCB(void* data, int argc, char** argv, char** azColName)
{
	string* pass = reinterpret_cast<string*>(data);
	*pass = argv[0];
	return 0;
}