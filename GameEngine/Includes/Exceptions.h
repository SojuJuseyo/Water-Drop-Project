#pragma once

#include <stdexcept>
#include <string>

namespace Moo
{
	class Exception : public std::exception
	{
	public:
		Exception(const std::string& exception) 
		{
			_msg = exception;
		}
		~Exception() {}
		virtual const char* what() const throw()
		{
			return _msg.c_str();
		}
	private:
		std::string _msg;
	};
	class InitException : public Exception
	{
	public:
		InitException(const std::string& exception) : Exception(exception) {}
		~InitException() {}
	};
}