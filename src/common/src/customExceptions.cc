#include "customExceptions.h"
#include <iostream>

namespace Common
{
	const char * UnrecognizedArgException::what() const noexcept
	{
		return "[ ERROR ]: Unrecognized mcheck argument provided.";
	}

	const char * ProcCreateException::what() const noexcept
	{
		return "[ ERROR ]: Failed to create child process.";
	}

	const char * QueueMessageException::what() const noexcept
	{
		std::cerr << "ErrorCode: " << err << std::endl;
		return "[ ERROR ]: Failed to push message to queue";
	}

	const char * QueueOpenException::what() const noexcept
	{
		std::cerr << "ErrorCode: " << err << std::endl;
		return "[ ERROR ]: Failed to open message queue";
	}

	const char * CloseQueueException::what() const noexcept
	{
		std::cerr << "ErrorCode: " << err << std::endl;
		return "[ ERROR ]: Failed to close message to queue";
	}

	const char * LoggerRecreationException::what() const noexcept
	{
		return "[ ERROR ]: Logger is singleton and cannot be recreated";
	}
}
