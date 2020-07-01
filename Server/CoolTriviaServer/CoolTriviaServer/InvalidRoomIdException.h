#pragma once
#include "MyException.h"

class InvalidRoomIdException : public MyException {
public:
	InvalidRoomIdException() : MyException("Error: Invalid Room") {}
};
