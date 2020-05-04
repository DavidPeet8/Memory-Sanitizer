#ifndef MESSAGE_MANAGER_H
#define MESSAGE_MANAGER_H

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

namespace Common 
{

	// Use RAII to handle POSIX Message queue destruction
	class MessageManager final
	{
		const char * name;
		mqd_t queue;

		public:
			MessageManager(const char *name, int oflag);
			MessageManager(const char *name, int oflag, mode_t mode, mq_attr *attr);
			~MessageManager();

			void sendMessage(const char *msg, size_t length, unsigned int priority);
			void hardClose();
	};

}

#endif

