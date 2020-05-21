#include "LoggedUser.h"

// LoggedUser Constructor
LoggedUser::LoggedUser(string username)
{
	this->m_username = username;
}

// LoggedUser Destructor
LoggedUser::~LoggedUser()
{

}

// Function will return the username of the logged user
string LoggedUser::getUsername()
{
	return this->m_username;
}