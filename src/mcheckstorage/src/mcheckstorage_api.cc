#include "mcheckstorage_api.h"
#include "Logger.h"
#include "LeakChecker.h"
#include "messageManager.h"
#include "Args.h"
#include <cstddef>
#include <memory>
#include <iostream>
#include <sstream>

namespace 
{
	LeakChecker checker;
	Common::Args args;
	__attribute__((constructor)) void onLoad() 
	{
		// Get information from the POSIX message queue
		Common::MessageManager queue("/mcheck_config", O_RDONLY);
		args.deserialize(queue.readMessage());
		Common::Logger::create(args);
	}	
}

extern "C" void addMemRef (void *baseAddr, size_t size) 
{
	checker.addRef(baseAddr, size);
}

extern "C" void remMemRef (void *baseAddr) 
{
	checker.remRef(baseAddr);
}

extern "C" void dump() 
{
	checker.dumpRefs();
}


