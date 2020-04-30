#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <thread>

using std::vector;
using std::string;
using std::thread;

class Server
{
public:
	Server();
	~Server();
	void serve(int port);
	int getPort() const;

private:

	void accept();
	void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;
	vector<thread> _serverThreads;
	string _serverIp;
	int _port;
	string _usersConnected;

};