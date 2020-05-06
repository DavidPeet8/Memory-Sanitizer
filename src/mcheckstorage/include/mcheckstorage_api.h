#ifndef MCHECK_STORAGE_API_H
#define MCHECK_STORAGE_API_H

#include <cstddef>


extern "C" void addMemRef (void *baseAddr, size_t size);

extern "C" void remMemRef (void *baseAddr);

extern "C" void dump();

#endif

