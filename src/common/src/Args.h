#ifndef ARGS_H
#define ARGS_H

#include <istream>

namespace Common
{
	#define ARG_VERBOSE 0x1

	struct Args 
	{
		unsigned int args;
		public:
			const char * serialize(unsigned int &sizeInBytes);
			void deserialize(const char *msg);
	};

	std::istream &operator>>(std::istream &in, Args &args);
}

#endif

