#pragma once

class IDatabase
{
public:
	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string, string) = 0;
	virtual void addNewUser(string, string, string) = 0;
};