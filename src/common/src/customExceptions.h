#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <exception>

namespace Common
{
	class UnrecognizedArgException : public std::exception 
	{
		public:
			const char * what() const noexcept override;
	};

	class ProcCreateException : public std::exception 
	{
		public:
			const char * what() const noexcept override;
	};

	class QueueMessageException : public std::exception 
	{
		int err;
		public:
			QueueMessageException(int err): err{err} {}
			const char * what() const noexcept override;
	};

	class CloseQueueException : public std::exception 
	{
		int err, queue;
		public:
			CloseQueueException(int err, int queue): err{err}, queue{queue} {}
			const char * what() const noexcept override;
	};

	class LoggerRecreationException : public std::exception
	{
		public:
			const char * what() const noexcept override;
	};
}

#endif
