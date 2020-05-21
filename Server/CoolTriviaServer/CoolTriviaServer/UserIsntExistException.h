#pragma once
#include "MyException.h"

class UserIsntExistException : public MyException {
public:
	UserIsntExistException() : MyException("Error: The user isn't exist") {}
};
