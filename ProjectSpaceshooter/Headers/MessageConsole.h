#pragma once



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
		for(int i=0; i<MESSAGE_CONSOLE_CAPACITY-1; i++)	{
			messages[i] = messages[i+1];
		}

		messages[MESSAGE_CONSOLE_CAPACITY-1] = newMessage;
	}

private:
	std::string messages[MESSAGE_CONSOLE_CAPACITY];
};
