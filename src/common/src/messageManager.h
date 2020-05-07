#ifndef MESSAGE_MANAGER_H
#define MESSAGE_MANAGER_H

#include <mqueue.h>
#include <string>

namespace Common 
{

	// Use RAII to handle POSIX Message queue destruction
	class MessageManager final
	{
		const char * name;
		mqd_t queue;
		long int msgSize = 0;
		long int max_msgSize = 0;

		public:
			MessageManager(const char *name, int oflag);
			MessageManager(const char *name, int oflag, mode_t mode, mq_attr *attr);
			~MessageManager();

			void sendMessage(const char *msg, size_t length, unsigned int priority);
			const char *readMessage();
			void hardClose();
	};

}

#endif

