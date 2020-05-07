#include "Logger.h"
#include "Args.h"
#include "customExceptions.h"
#include <iostream>
#include <memory>

namespace Common 
{
	std::unique_ptr<Logger> Logger::logger = nullptr;

	// Create the singleton logger object
	void Logger::create(std::ostream &outstream, const Common::Args &args) 
	{
		if (exists()) throw LoggerRecreationException();
		Logger::logger.reset(new Logger(args, outstream));
	}

	void Logger::create(std::ostream &outstream) 
	{
		if (exists()) throw LoggerRecreationException();
		Logger::logger.reset(new Logger(Common::Args{0}, outstream));
	}

	void Logger::create(const Common::Args &args) 
	{
		if (exists()) throw LoggerRecreationException();
		Logger::logger.reset(new Logger(args, std::cout));
	}

	void Logger::create() 
	{
		if (exists()) throw LoggerRecreationException();
		Logger::logger.reset(new Logger(Common::Args{0}, std::cout));
	}

	Logger &Logger::get()
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

	Logger::Logger(const Common::Args &args, std::ostream &out): 
	verbose{static_cast<bool>(args.args & ARG_VERBOSE)}, 
	out{out},
	args{args.args} 
	{}

	bool Logger::exists()
	{
		return Logger::logger != nullptr;
	}
};

