#include "Args.h"
#include <string>

namespace Common
{
	const char * Args::serialize(unsigned int &sizeInBytes) 
	{
		std::string res = std::to_string(args);
		sizeInBytes = res.length() * sizeof(char);
		return res.c_str();
	}
}

