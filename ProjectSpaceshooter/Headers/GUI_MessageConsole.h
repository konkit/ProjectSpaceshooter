#pragma once

#include <ctime>

#define MESSAGE_CONSOLE_CAPACITY 5

class MessageConsole	{
public:
	MessageConsole()	{
		addNewMessage("Boot completed");
	}


	std::string getMessages()	{
		std::string result;

		for( std::string i : messages )	{
			result += i + "\n";
		}

		return result;
	}

	std::string getMessage(int num)	{
		if( num < 0 || num > MESSAGE_CONSOLE_CAPACITY )	{
			throw My_Exception("Array out of bounds \n");
		}

		return messages[num];
	}


	void addNewMessage(std::string newMessage)	{
		//get time
		time_t mTime = time(0);
		tm* now = localtime( &mTime );
		char buf[80];
		strftime(buf, sizeof(buf), "%X", now);

		std::string timeString(buf);
			

		for(int i=0; i<MESSAGE_CONSOLE_CAPACITY-1; i++)	{
			messages[i] = messages[i+1];
		}

		messages[MESSAGE_CONSOLE_CAPACITY-1] = timeString + ": " + newMessage;
	}

private:
	std::string messages[MESSAGE_CONSOLE_CAPACITY];
};
