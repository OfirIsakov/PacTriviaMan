#include "LoginManager.h"

// Function will add the new user into the DB (if the user meets the parameters)
void LoginManager::signup(string username, string password, string mail)
{
	this->m_database->addNewUser(username, password, mail); // might throw exception...
}

// Function will login the user if the parames is correct
void LoginManager::login(string username, string password)
{
	// Check if the user exist
	if (!this->m_database->doesUserExist(username))
	{
		throw UserIsntExistException();
	}
	// Check if the password match to the user
	if (!this->m_database->doesPasswordMatch(username, password))
	{
		throw PasswordIsntMatchException();
	}
	//
	for (auto &user: this->m_loggedUsers) {
		if (user.getUsername() == username) {
			throw AlreadyLoggedInException();
		}
	}
	// Login successful - add to the vector
	this->m_loggedUsers.push_back(LoggedUser(username));
}

// Function will remove the user from the vector
void LoginManager::logout(string username)
{
	for (auto it = this->m_loggedUsers.begin(); it != this->m_loggedUsers.end(); it++)
	{
		if ((*it).getUsername().compare(username) == 0)
		{
			this->m_loggedUsers.erase(it);
			break;
		}
	}
}