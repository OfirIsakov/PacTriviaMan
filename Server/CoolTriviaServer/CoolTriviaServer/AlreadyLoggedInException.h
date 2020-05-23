#pragma once
#include "MyException.h"

class AlreadyLoggedInException : public MyException {
public:
	AlreadyLoggedInException() : MyException("Error: User is already logged in!") {}
};
