#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <vector>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "json.hpp"

using json = nlohmann::json;
using std::string;

class Helper
{
	static char* readFromSocket(SOCKET sc, int bytesNum, int flags = 0);
	static void sendData(SOCKET sc, std::string message);
	static std::string padNumber(int num, int digits);
};