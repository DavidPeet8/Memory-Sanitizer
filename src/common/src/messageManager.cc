#include "messageManager.h"
#include "customExceptions.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

namespace Common 
{
	MessageManager::MessageManager(const char *name, int oflag):
	name{name},
	queue{mq_open(name, oflag)}
	{}

	MessageManager::MessageManager(const char *name, int oflag, mode_t mode, mq_attr *attr):
	name{name},
	queue{mq_open(name, oflag, mode, attr)}
	{}

	MessageManager::~MessageManager() 
	{
		// Don't deal with error here, queue may have already been closed manually
		mq_unlink(name);
	}

	void MessageManager::sendMessage(const char *msg, size_t length, unsigned int priority) 
	{
		int ret = mq_send(queue, msg, length, priority);
		if (ret != 0) throw QueueMessageException(errno);
	}

	void MessageManager::hardClose() 
	{
		int ret = mq_close(queue);
		if (ret != 0) throw CloseQueueException(errno, queue);
	}

}

