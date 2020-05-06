#include "Args.h"

// Reinterpret the bits of this class as a C string to allow for transmission through the posix message queue
// Note that this choice does enable ABI issues but that is ok
// This does require that libraries are all compiled by the same compiler (for glibc / CRT reasons)
// This is ok though, normal humans wanting to use this will compile all of the above using the same compiler
const char * Args::serialize() 
{
	return reinterpret_cast<const char*>(*this);
}

