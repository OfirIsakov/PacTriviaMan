#pragma once

#include "SqliteDataBase.h"
#include "LoggedUser.h"
#include "UserIsntExistException.h"
#include "PasswordIsntMatchException.h"
#include "AlreadyLoggedInException.h"

class LoginManager
{
public:
	
	void signup(string username, string password, string mail);
	void login(string username, string password);
	void logout(string username);

private:

	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;
};

