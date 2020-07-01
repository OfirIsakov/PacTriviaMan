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
#include <vector>

#include "json.hpp"

using json = nlohmann::json;
using std::string;
using std::vector;

class Helper
{
public:
	static char* readFromSocket(SOCKET sc, int bytesNum, int flags = 0);
	static void sendData(SOCKET sc, vector<unsigned char> message);
	static int convertFourBytesToInt(unsigned char buffer[]);
	static vector<unsigned char> convertIntToFourBytes(int num);
};