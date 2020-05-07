#include "commonMethods.h"
#include <string>
#include <time.h>

namespace Common 
{
	std::string getTimeStamp() 
	{
		time_t curTime = time(nullptr);
		std::string res = "[ ";
		res += ctime(&curTime);
		res.pop_back();
		res += " ] ";
		return res;
	}
}

