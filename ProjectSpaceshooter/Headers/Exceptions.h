#pragma once


class AbstractException	{

};

class WindowClosedException : public AbstractException	
{};

class My_Exception : public std::exception
{
public:
	My_Exception(){};
	My_Exception(std::string errorMessage)
		: exception(errorMessage.c_str())
	{};
	My_Exception(std::wstring errorMessage)
		: exception(string(errorMessage.begin(),errorMessage.end()).c_str())
	{};
	~My_Exception(){};


private:

};
