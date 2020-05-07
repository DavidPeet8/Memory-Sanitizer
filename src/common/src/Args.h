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
			Args();
			Args(unsigned int args);
	};

}

#endif

