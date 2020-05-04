#include <string>
#include <time.h>

namespace Common 
{
	std::string getTimeStamp() 
	{
		time_t curTime = time(nullptr);
		return std::string("[ ") + ctime(&curTime) + " ]";
	}
}

