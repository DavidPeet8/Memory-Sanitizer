#include "customExceptions.h"
#include "messageManager.h"
#include "Logger.h"
#include "Args.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

namespace CLI 
{
	unsigned int parseArgs (int argc, char *argv[]) 
	{
		int i;
		unsigned int args;
		for(i = 1; i < argc; i++) // argv[0] is calling name
		{
			if (argv[i][0] == '-') // As these are C strings, argv[i][1] must be data or 0
			{
				switch (argv[i][1])  
				{
					case 'v':
						args |= ARG_VERBOSE;
						break;
					default: 
						throw Common::UnrecognizedArgException();
				}
			}
			else
			{
				break;
			}
		}

		argv += (i-1); // remove the exe name and all arguments to mcheck
		return args;
	}
}

// Two binaries, the CLI and the actaual memcheck
// Memcheck is a shared lib, CLI is an exe
// Calling format: mcheck <mcheck args> executable_path <args to exe>
int main (int argc, char **argv, char **envp) 
{
	Common::Args args {CLI::parseArgs(argc, argv)};
	// Create a write only message queue used to pass arguments to shared lib
	// Shared lib will not be running at the time of message sending, so must use a Message Queue other IPC like pipes or FIFOs
	struct mq_attr attr;
	attr.mq_msgsize = 4096;
	attr.mq_maxmsg = 1;

	Common::MessageManager queue("/mcheck_config", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR, &attr);
	unsigned int size;
	const char * msg = args.serialize(size);
	queue.sendMessage(msg, size, 0);

	// Use multiple processes allow for a orphan version
	int pid = fork();
	switch (pid) 
	{
		case -1:
			throw Common::ProcCreateException();
		case 0: // We are in the child process
		{
			std::cout << "In the child proc" << std::endl;
			putenv(const_cast<char *>("LD_PRELOAD=./libmcheck.so"));
			execv(argv[0], argv + 1);
			break;
		}
		default: // We are in the parent process
			// wait for child to return
			std::cout << "In the parent PROC" << std::endl;
			int status;
			wait(&status);
			break;
	}
}

