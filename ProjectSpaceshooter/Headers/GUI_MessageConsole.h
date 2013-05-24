#pragma once

#include <ctime>

#define MESSAGE_CONSOLE_CAPACITY 5


/** Class storing data about messages displayed on GUI
  *
  * @author Konkit
  */
class MessageConsole	{
public:
	MessageConsole()	{
		addNewMessage("Boot completed");
	}

	/** Returns string with all messages separated with '\n' */
	std::string getMessages()	{
		std::string result;

		for( std::string i : messages )	{
			result += i + "\n";
		}

		return result;
	}

	/**returns one message with given number */
	std::string getMessage(int num)	{
		if( num < 0 || num > MESSAGE_CONSOLE_CAPACITY )	{
			throw My_Exception("Array out of bounds \n");
		}

		return messages[num];
	}

	/** adds new message with current time to the message console */
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

	/** adds new message with current time to the message console */
	void operator<<(std::string newMessage)	{
		addNewMessage(newMessage);
	}


private:
	std::string messages[MESSAGE_CONSOLE_CAPACITY];
};
