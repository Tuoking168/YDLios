#ifndef __StringUtils_h__
#define __StringUtils_h__

#include "MacroUtils.h"
#include <string>

namespace TimeType
{
	enum
	{
		ms = 0,
		hm = 1,
		hms = 2,
		dhms = 3,
		dh = 4,
	};
}

class StringUtils
{
public:
	static std::string toString(int data);

	static std::string timeToString(int time, int timeType);

	static std::string levelToString(int reborn, int level);

	// return true if there is no sensitive words
	static bool filterString(const std::string &inString, std::string &outString);

	// return true if there is special words
	static bool hasSpecialWords(const std::string &str);

	// return time as like XXÄê-XXÔÂ-XXÈÕ XX£ºXX£ºXX
	static std::string getFormatTime(time_t t_time);

private:
	CP_MAKE_STATIC_CLASS(StringUtils);
};

#endif //__StringUtils_h__