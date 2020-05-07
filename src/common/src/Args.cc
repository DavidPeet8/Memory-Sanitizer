#include "Args.h"
#include <string>
#include <iostream>

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

	std::istream &operator>>(std::istream &in, Args &args) 
	{
		unsigned int newArgs = 0;
		in >> newArgs;
		args.args = newArgs;
		return in;
	}
}

