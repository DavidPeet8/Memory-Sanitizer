
#include "LeakChecker.h"
#include <stdio.h>

void LeakChecker::addRef(void * const baseAddr, const size_t size)
{
	if (memRefs.find(baseAddr) != memRefs.end()) throw "Something very bad happened... :'(";
	// Both of the following rely on underlying new operations leading to infinite recursion
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
	printf("\n------------ PEETGRIND V1.0 ------------\n");
	printf("Note: Size is in bytes\n");
	printf("Leaked Refs:\n");
	printf("%-14s | %-10s\n", "Base Address", "Size");
	for (const auto ref : memRefs) 
	{
		// TODO: Change the stream to be a variable retrieved from POSIX message queue
		printf("%-14p | %-10lu\n", ref.first, ref.second);
	}
	printf("\nMemory Allocation History:\n");
	printf("%-14s | %-10s | %-7s\n", "Base Address", "Size", "Success");
	for (const auto &memref : allocationTimeline) 
	{
		printf("%-14p | %-10lu | %-7s\n", memref.baseAddr, memref.size.value_or(0), memref.success ? "true" : "false");
	}
}




