#include "mcheckstorage_api.h"
#include "LeakChecker.h"
#include "messageManager.h"
#include "Args.h"
#include <cstddef>
#include <memory>
#include <iostream>

namespace 
{
	LeakChecker checker;
	Common::Args args;
	__attribute__((constructor)) void onLoad() 
	{
		// Get information from the POSIX message queue
		// TODO: Fix the difficulties with the POSIX Message queue
		// Common::MessageManager queue("/mcheck_config", O_RDONLY);
		args = Common::Args{/*std::stoul(queue.readMessage())*/0};// Read message is getting stuck
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


