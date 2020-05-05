#ifndef MCHECK_STORAGE_API_H
#define MCHECK_STORAGE_API_H

#include <cstddef>


extern "C" void memAlloc(void *baseAddr, size_t size);

extern "C" void memDeAlloc (void *baseAddr);

extern "C" void dump();

#endif

