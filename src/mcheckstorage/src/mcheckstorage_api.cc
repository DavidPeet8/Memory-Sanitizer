#include "mcheckstorage_api.h"
#include "LeakChecker.h"
#include "MessageManager.h"
#include <cstddef>

namespace 
{
	LeakChecker checker;
	__attribute__((constructor)) void onLoad() 
	{
		// Get information from the POSIX message queue
		MessageManager queue("mcheck_config", O_RONLY);
		reinterpret_cast<>(queue.readMessage());
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


