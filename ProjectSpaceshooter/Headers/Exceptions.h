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

class ParserException : public My_Exception
{
public:
	ParserException(std::string errorMessage)
		: My_Exception(errorMessage)
	{};
	ParserException(std::wstring errorMessage)
		: My_Exception(errorMessage)
	{};
};

class IteratorException : public My_Exception
{
public:
	IteratorException(std::string errorMessage)
		: My_Exception(errorMessage)
	{};
	IteratorException(std::wstring errorMessage)
		: My_Exception(errorMessage)
	{};
};

enum class PrefabExceptionType
{
	NO_PREFAB
};
class PrefabException : public My_Exception
{
public:
	PrefabException(std::string errorMessage, PrefabExceptionType type)
		: My_Exception(errorMessage), myType(type)
	{};
	PrefabException(std::wstring errorMessage, PrefabExceptionType type)
		: My_Exception(errorMessage), myType(type)
	{};
	PrefabExceptionType getType() const { return myType; }
private:
	PrefabExceptionType myType;
	
};

//Game object Exceptions
class EnemyNullException : My_Exception {};
class CoreNullException : My_Exception {};

class ErrMsg
{
public:
	void operator << ( exception & expt)
	{
		MessageBoxA( NULL, expt.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return ;
	}
};