#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <string>
#include <map>

#define LOG_FILENAME "log.dat"

// Example	Moo::Log().put(Moo::Log::DEBUG) << "example" << std::endl;

namespace Moo
{
	class Log
	{
	public:
		enum logLevel
		{
			CRITICAL_ERROR,
			WARNING,
			INFO,
			DEBUG
		};
		Log()
		{
			_logLevel[logLevel::CRITICAL_ERROR] = "CRITICAL_ERROR";
			_logLevel[logLevel::WARNING] = "WARNING";
			_logLevel[logLevel::INFO] = "INFO";
			_logLevel[logLevel::DEBUG] = "DEBUG";
			_file.open(LOG_FILENAME, std::fstream::in | std::fstream::out | std::fstream::app);
		}
		~Log()
		{
			_file.close();
		}

		std::fstream& put(logLevel level = logLevel::INFO)
		{
			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			std::time_t now_c = std::chrono::system_clock::to_time_t(now);
			_file << "- " << std::put_time(std::localtime(&now_c), "%F %T");
			_file << " " << _logLevel[level] << ": ";
			return _file;
		}

	private:
		std::map<logLevel, std::string> _logLevel;
		std::fstream  _file;
	};
}