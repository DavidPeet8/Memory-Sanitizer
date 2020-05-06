#include "mcheckstorage_api.h"
#include "LeakChecker.h"
#include "messageManager.h"
#include "Args.h"
#include <cstddef>

namespace 
{
	LeakChecker checker;
	Common::Args a{};
	__attribute__((constructor)) void onLoad() 
	{
		// Get information from the POSIX message queue
		Common::MessageManager queue("mcheck_config", O_RDONLY);
		a = reinterpret_cast<Common::Args&>(queue.readMessage());
	}
}

extern "C" void memAlloc(void *baseAddr, size_t size) 
{
	checker.addRef(baseAddr, size);
}

extern "C" void memDeAlloc (void *baseAddr) 
{
	checker.remRef(baseAddr);
}

extern "C" void dump() 
{
	checker.dumpRefs();
}


