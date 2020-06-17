#pragma once
#include "MyException.h"

class RoomIsFullException : public MyException {
public:
	RoomIsFullException() : MyException("Error: The room is full!") {}
};
