#include "Args.h"
#include <string>
#include <iostream>

// Chose to use reinterpret cast because it is a pain transferring data through const char * otherwise
// This may potentially affect ABI compatibility forcing readers and writers to have been 
// compiled on the same compiler but that is ok

namespace Common
{
	const char * Args::serialize(unsigned int &sizeInBytes) 
	{
		std::string argstring = std::to_string(args);
		sizeInBytes = argstring.length() * sizeof(char);
		sizeInBytes = sizeof(*this);
		return reinterpret_cast<const char *>(this);
	}

	void Args::deserialize(const char *msg)
	{
		const Args *args = reinterpret_cast<const Args *>(msg);
		*this = *args;
		delete msg;
	}

	Args::Args(): args{0} {}

	Args::Args(unsigned int args): args{args} {}
}

