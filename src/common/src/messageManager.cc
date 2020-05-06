#include "messageManager.h"
#include "customExceptions.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#include <string>
#include <iostream>

namespace Common 
{
	MessageManager::MessageManager(const char *name, int oflag):
	name{name},
	queue{mq_open(name, oflag)}
	{
		if (queue == -1) { throw QueueOpenException(errno); }
	}

	MessageManager::MessageManager(const char *name, int oflag, mode_t mode, mq_attr *attr):
	name{name},
	queue{mq_open(name, oflag, mode, attr)}
	{
		if (queue == -1) { throw QueueOpenException(errno); }
	}

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

	char *MessageManager::readMessage()
	{
		const int buffSize = 1000;
		char *msg = new char[buffSize];
		mq_receive(queue, msg, buffSize, nullptr);
		return msg;
	}

	void MessageManager::hardClose() 
	{
		int ret = mq_close(queue);
		if (ret != 0) throw CloseQueueException(errno, queue);
	}

}

