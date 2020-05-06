#ifndef LEAKCHECKER_H
#define LEAKCHECKER_H

#include <vector>
#include <map>
#include <optional>

struct MemRequest 
{
	void * const baseAddr;
	const std::optional<size_t> size;
	const bool success;
};

class LeakChecker 
{
	std::map<void *, size_t> memRefs;
	std::vector<MemRequest> allocationTimeline;

	public:
		void addRef(void * const baseAddr, const size_t size);
		void remRef(void * const baseAddr);
		void dumpRefs() const;
};



#endif

