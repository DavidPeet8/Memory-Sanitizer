#include "customExceptions.h"

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
		return "[ ERROR ]: Failed to push message to queue | ErrCode: " + err;
	}

	const char * CloseQueueException::what() const noexcept
	{
		return "[ ERROR ]: Failed to close message to queue | ErrCode: " + err;
	}

	const char * LoggerRecreationException::what() const noexcept
	{
		return "[ ERROR ]: Logger is singleton and cannot be recreated";
	}
}
