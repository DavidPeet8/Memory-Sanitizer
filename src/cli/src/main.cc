#include "customExceptions.h"
#include "messageManager.h"
#include "Logger.h"
#include "Args.h"
#include "Constants.h"
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
	unsigned int parseArgs (int argc, char *argv[], int &consumed) 
	{
		int i;
		unsigned int args = 0;
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

		consumed = (i-1); // remove the exe name and all arguments to mcheck
		return args;
	}

	void interpretStatus(int status, int pid) 
	{
		std::cout << "\n";
		if (WIFEXITED(status))
		{
			std::cout << "Child process " << pid << " terminated normally." << std::endl;
		} else if (WIFSIGNALED(status))
		{
			std::cout << "Child process " << pid << " terminated due to unhandled signal: " << WTERMSIG(status) << std::endl;
		}
	}
}


// Calling format: mcheck <mcheck args> executable_path <args to exe>
int main (int argc, char **argv) 
{
	std::cerr << "Starting Up Mcheck..." << std::endl;
	int argsComsumed = 0;
	Common::Args args {CLI::parseArgs(argc, argv, argsComsumed)};
	unsigned int size;
	const char * msg = args.serialize(size);

	// Create a write only message queue used to pass arguments to shared lib
	// Shared lib will not be running at the time of message sending, so use a kernel persistent IPC method
	struct mq_attr attr;
	attr.mq_msgsize = Constants::msgSize;
	attr.mq_maxmsg = Constants::maxNumMsg;

	Common::MessageManager queue("/mcheck_config", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR, &attr);	
	queue.sendMessage(msg, size, 0);

	int pid = fork();
	switch (pid) 
	{
		case -1:
			throw Common::ProcCreateException();
		case 0: // We are in the child process
		{
			std::string libPath = std::string(getenv("HOME")) + "/mylibs/libmcheck.so";
			std::cerr << "Library Path: " << libPath << std::endl;
			setenv("LD_PRELOAD", libPath.c_str(), 1);
			setenv("DYLD_INSERT_LIBRARIES", libPath.c_str(), 1);
			execv(argv[argsComsumed + 1], argv + argsComsumed + 2);
			break;
		}
		default: // We are in the parent process
			int status;
			wait(&status);
			CLI::interpretStatus(status, pid);
			break;
	}
}

