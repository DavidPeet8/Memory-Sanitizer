#ifndef LEAKCHECKER_H
#define LEAKCHECKER_H

#include <vector>
#include <map>

struct MemRequest 
{
	unsigned long baseAddr;
	size_t size;
};

class LeakChecker 
{
	std::map<unsigned long, size_t> memRefs;
	std::vector<MemRequest> allocationTimeline;

	public:
		void addRef(void * const baseAddr, const size_t size);
		void remRef(void * const baseAddr);
		void dumpRefs();
};



#endif

