#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <thread>
#include "WSAInitializer.h"
#include "Server.h"

using std::string;
using std::cin;
using std::thread;

void serverServe();

int main()
{
	string input = "";
	thread getClients(serverServe);
	getClients.detach(); // When the main stops, the thread will stop too
	while (input.compare("EXIT") != 0)
	{
		cin >> input;
	}
	return 0;
}

void serverServe()
{
	try
	{
		std::cout << "Get into Serve!";
		WSAInitializer wsaInit;
		Server myServer;
		myServer.run();
	}
	catch (std::exception & e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
}