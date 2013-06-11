#pragma once
#include <iostream>

class My_Exception;
std::ostream & operator << (std::ostream & stream, const My_Exception & ex);

/**
 * @author konkit
 */
class AbstractException	{

};

/**
 * @author konkit
 */
class WindowClosedException : public AbstractException	
{};

/**
 * @author konkit
 */
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
	friend std::ostream & operator << (std::ostream & stream, const My_Exception & ex);
private:
};

/**
 * @author Zyga
 */
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

/**
 * @author Zyga
 */
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

/**
 * @author Zyga
 */
enum class PrefabExceptionType
{
	NO_PREFAB
};

/**
 * @author Zyga
 */
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

/**
 * Game object Exceptions
 * @author konkit
 */
class EnemyNullException : My_Exception {};

/**
 * Game object Exceptions
 * @author konkit
 */
class CoreNullException : My_Exception {};

/**
 * Stream operator used to print exception.
 * @return Input stream reference
 * @param stream Output stream
 * @param _exception Exception to print
 * @author Zyga
 */
std::ostream & operator << (std::ostream & stream, const My_Exception & _exception)
{
	stream << std::endl << "Exception: " << _exception.what() << std::endl;
	return stream;
}

/**
 * Class showing exception in windows MessageBox
 * @author Zyga
 */
class ErrMsg
{
public:
    void operator << ( exception & expt)
	{
		MessageBoxA( NULL, expt.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return ;
		std::cout;
	}
};