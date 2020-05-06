#ifndef ARGS_H
#define ARGS_H

namespace Common
{
	#define ARG_VERBOSE 0x1

	struct Args 
	{
		unsigned int args;
		public:
			const char * serialize();
	};
}

#endif

