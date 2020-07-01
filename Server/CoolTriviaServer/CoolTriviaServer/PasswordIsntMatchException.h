#pragma once
#include "MyException.h"

class PasswordIsntMatchException : public MyException {
public:
	PasswordIsntMatchException() : MyException("Error: The password isn't match to the username") {}
};
