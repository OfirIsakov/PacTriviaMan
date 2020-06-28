#pragma once
#include "MyException.h"

class UserAlreadyExistsException : public MyException {
public:
	UserAlreadyExistsException() : MyException("Error: Can't create the user, there is user with the same username") {}
};
