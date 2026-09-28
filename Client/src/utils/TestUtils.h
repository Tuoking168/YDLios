#ifndef __TestUtils_h__
#define __TestUtils_h__

#include "MacroUtils.h"
#include <string>

class TestUtils
{
public:
	static void timeTestBegin();
	static void timeTestEnd();
	static void timeTestEnd(const std::string &mark);

	static void printMemoryUsedInfo();
	static void printMemoryUsedInfo(const std::string &mark);

private:
	CP_MAKE_STATIC_CLASS(TestUtils);
};
#endif //__TestUtils_h__