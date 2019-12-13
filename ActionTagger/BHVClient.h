#ifndef BHVCLIENT_H
#define BHVCLIENT_H

#include <iostream>
#include <Winsock.h>
#include <windows.h>
#include <string.h>
#include <stdio.h> 
#include <thread>


class BHVClient
{
	#define PORT 10000
	#define BUFLEN 50
	
	static std::string result;
private:
	

public:
	BHVClient();
	static void sendMessage(std::string data_string);
	static std::string getResult() { return result; }
	

};

#endif
