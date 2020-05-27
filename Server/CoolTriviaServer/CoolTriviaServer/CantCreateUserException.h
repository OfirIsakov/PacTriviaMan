#pragma once
#include "MyException.h"

class CantCreateUserException : public MyException {
public:
	CantCreateUserException() : MyException("Error: Can't create the user, there is user with the same username") {}
};
