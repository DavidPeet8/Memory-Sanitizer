
#include "LeakChecker.h"
#include <stdio.h>

void LeakChecker::addRef(void * const baseAddr, const size_t size)
{
	if (memRefs.find(baseAddr) != memRefs.end()) throw "Something very bad happened... :'(";
	memRefs[baseAddr] = size;
 	allocationTimeline.emplace_back(MemRequest{baseAddr, size, true});
}

void LeakChecker::remRef(void * const baseAddr) 
{
	auto refIt = memRefs.find(baseAddr);
	if (refIt != memRefs.end()) 
	{
		memRefs.erase(refIt);
		allocationTimeline.emplace_back(MemRequest{baseAddr, std::nullopt, true});
	}
	allocationTimeline.emplace_back(MemRequest{baseAddr, std::nullopt, false});
}

void LeakChecker::dumpRefs () const 
{
	printf("------------ PEETGRIND V1.0 ------------\n");
	printf("Leaked Refs:\n");
	for (const auto ref : memRefs) 
	{
		// TODO: Change the stream to be a variable retrieved from POSIX message queue
		printf("Base Address: %p | Size: %lu \n", ref.first, ref.second);
	}
	printf("\nMemory Allocation History:\n");
	for (const auto &memref : allocationTimeline) 
	{
		printf("Base Address: %p | Size: %lu | Success: %s", memref.baseAddr, memref.size.value_or(0), memref.success ? "true" : "false");
	}
}




