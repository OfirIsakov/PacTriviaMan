#include "LoginManager.h"

// Function will add the new user into the DB (if the user meets the parameters)
void LoginManager::signup(string username, string password, string mail)
{
	m_database->addNewUser(username, password, mail); // might throw exception...
}

// Function will login the user if the parames is correct
void LoginManager::login(string username, string password)
{
	// Check if the user exist
	if (!m_database->doesUserExist(username))
	{
		throw UserIsntExistException();
	}
	// Check if the password match to the user
	if (!m_database->doesPasswordMatch(username, password))
	{
		throw PasswordIsntMatchException();
	}
	// Login successful - add to the vector
	m_loggedUsers.push_back(LoggedUser(username));
}

// Function will remove the user from the vector
void LoginManager::logout(string username)
{
	for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); it++)
	{
		if ((*it).getUsername().compare(username) == 0)
		{
			m_loggedUsers.erase(it);
			break;
		}
	}
}