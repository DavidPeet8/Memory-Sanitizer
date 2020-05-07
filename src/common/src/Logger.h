#ifndef LOGGER_H
#define LOGGER_H

#include "Args.h"
#include "commonMethods.h"
#include <memory>
#include <string>
#include <iostream>

namespace Common 
{
	class Logger final
	{
		private:
			bool verbose;
			std::ostream &out;
			static std::unique_ptr<Logger> logger;

		protected: 
			Logger(const Common::Args &args, std::ostream &);
			static bool exists();

		public:
			Logger() = delete;
			Logger(Logger &) = delete;
			Logger(Logger &&) = delete;
			Logger operator=(Logger &) = delete;
			Logger operator=(Logger &&) = delete;
			~Logger()
			{
				out << std::flush;
			}

			template<typename OutType>
			void log(const OutType &data, const bool flush = false);
			// log specifically to a different stream
			template<typename OutType>
			void log(std::ostream &, const OutType &data, const bool flush = false);

			static void create(const Common::Args &args);
			static void create(std::ostream &);
			static void create(std::ostream &, const Common::Args &args);
			static void create();
			static Logger &get();
	};

	// ----------------------------- TEMPLATE IMPLEMENTATIONS ----------------------------------

	template<typename OutType>
	void Logger::log(std::ostream& out, const OutType &data, const bool flush) 
	{
		if (verbose)
		{
			out << getTimeStamp() << data << "\n";
			if (flush) { out << std::flush; }
		}
	}

	template<typename OutType>
	void Logger::log(const OutType &data, const bool flush) 
	{
		Logger::log(out, data, flush);
	}

	template <typename OutType>
	Logger &operator<<(Logger &logger, const OutType data)
	{
		logger.log(data);
		return logger;
	}

}

#endif
