#ifndef LOGGER_H
#define LOGGER_H

#include "Args.h"
#include <ostream>
#include <memory>

namespace Common 
{
	class Logger final
	{
		private:
			bool verbose;
			std::ostream &out;
			static std::unique_ptr<Logger> logger;

		protected: 
			Logger(const int args, std::ostream &);
			static bool exists();

		public:
			enum LogLevel {DEBUG, INFO, WARNING, ERROR};

			Logger() = delete;
			Logger(Logger &) = delete;
			Logger(Logger &&) = delete;
			Logger operator=(Logger &) = delete;
			Logger operator=(Logger &&) = delete;
			~Logger(){}

			template<typename OutType>
			void log(const OutType &data, const bool flush = false);
			// log specifically to a different stream
			template<typename OutType>
			void log(std::ostream &, const OutType &data, const bool flush = false);

			static void create(const int args);
			static void create(std::ostream &);
			static void create(std::ostream &, const int args);
			static void create();
			static Logger& get(LogLevel level = INFO);
	};

	template <typename OutType>
	Logger &operator<< (Logger &, const OutType &);
}

#endif
