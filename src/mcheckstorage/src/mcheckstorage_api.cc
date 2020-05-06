#include "mcheckstorage_api.h"
#include "LeakChecker.h"
#include "messageManager.h"
#include "Args.h"
#include <cstddef>
#include <memory>

namespace 
{
	LeakChecker checker;
	std::unique_ptr<Common::Args> args;
	__attribute__((constructor)) void onLoad() 
	{
		// Get information from the POSIX message queue
		Common::MessageManager queue("/mcheck_config", O_RDONLY);
		Common::Args *a = reinterpret_cast<Common::Args*>(queue.readMessage());
		args.reset(a);
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


