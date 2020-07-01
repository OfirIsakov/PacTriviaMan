#include "Helper.h"

// recieve data from socket according byteSize
//WARNING: dont forget to delete it
char* Helper::readFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[(long)bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}

// send data to socket
void Helper::sendData(SOCKET sc, vector<unsigned char> message)
{
	string buffer(message.begin(), message.end());
	const char* data = buffer.c_str();

	if (send(sc, data, buffer.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

// function converts the four given bytes into an int
int Helper::convertFourBytesToInt(unsigned char buffer[])
{
	return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3]);
}

/*
Fucntion will convert in to four bytes as a unsigned char array
Input:
	num - the number to convert
Output:
	the array - 4 bytes
*/
vector<unsigned char> Helper::convertIntToFourBytes(int num)
{
	vector<unsigned char> buffer;
	
	for (int i = 0; i < 4; i++)
	{
		buffer.push_back((num >> (24 - i * 8)) & 0xFF);
	}
	return buffer;
}
