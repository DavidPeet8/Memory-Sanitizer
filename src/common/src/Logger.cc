#include "Logger.h"
#include "Args.h"
#include "commonMethods.h"
#include "customExceptions.h"
#include <iostream>
#include <memory>

namespace Common 
{
	std::unique_ptr<Logger> Logger::logger = nullptr;

	// Create the singleton logger object
	void Logger::create(std::ostream &outstream, const int args) 
	{
		if (exists()) throw LoggerRecreationException();
		Logger::logger.reset(new Logger(args, outstream));
	}

	void Logger::create(std::ostream &outstream) 
	{
		if (exists()) throw LoggerRecreationException();
		Logger::logger.reset(new Logger(0, outstream));
	}

	void Logger::create(const int args) 
	{
		if (exists()) throw LoggerRecreationException();
		Logger::logger.reset(new Logger(args, std::cout));
	}

	void Logger::create() 
	{
		if (exists()) throw LoggerRecreationException();
		Logger::logger.reset(new Logger(0, std::cout));
	}

	Logger& Logger::get(LogLevel level)
	{	
		if (Logger::logger) 
		{
			return *logger;
		}
		else 
		{
			create(); // create the logger with default init
			return *logger;
		}
	}

	template<typename OutType>
	void Logger::log(std::ostream& out, const OutType &data, const bool flush) 
	{
		out << getTimeStamp() << data << "\n";
		if (flush) { out << std::flush; }
	}

	template<typename OutType>
	void Logger::log(const OutType &data, const bool flush) 
	{
		Logger::log(out, data, flush);
	}

	Logger::Logger(const int args, std::ostream &out): 
	verbose{static_cast<bool>(args & ARG_VERBOSE)}, 
	out{out} 
	{}

	template <typename OutType>
	Logger &operator<< (Logger &logger, const OutType &data)
	{
		logger.log(data);
		return logger;
	}

	bool Logger::exists()
	{
		return Logger::logger != nullptr;
	}
};

