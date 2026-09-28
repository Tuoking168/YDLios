#include "TestUtils.h"
#include "CCCommon.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	#include <windows.h>
	#include <Psapi.h>
	#pragma comment(lib,"Psapi.lib")
#endif

using namespace cocos2d;


static double timeFrequency = 0;
static double timeStart = 0;
void TestUtils::timeTestBegin()
{
	Win32Code(
		LARGE_INTEGER frequency={0};
		QueryPerformanceFrequency(&frequency);
		LARGE_INTEGER startTime={0};
		QueryPerformanceCounter(&startTime);

		if(frequency.QuadPart > 0)
		{
			timeFrequency = frequency.QuadPart;
			timeStart = startTime.QuadPart;
		}
		else
		{
			CCLog("Error: SystemData::timeTestBegin, timeFrequency = 0!");
		}
	);
}

void TestUtils::timeTestEnd()
{
	timeTestEnd("");
}

void TestUtils::timeTestEnd( const std::string &mark )
{
	Win32Code(
		if(timeFrequency > 0)
		{
			LARGE_INTEGER time = {0};
			QueryPerformanceCounter(&time);
			double timeEnd = time.QuadPart;
			double timeUsed = 1000 * (timeEnd - timeStart) / timeFrequency;

			CCLog("\n>>>Mark: %s", mark.c_str());
			CCLog(">>>TimeTest: use time = %f ms", timeUsed);
		}
	);
}

void TestUtils::printMemoryUsedInfo()
{
	printMemoryUsedInfo("");
}

void TestUtils::printMemoryUsedInfo( const std::string &mark )
{
	Win32Code(
		HANDLE handle = GetCurrentProcess();  
		PROCESS_MEMORY_COUNTERS pmc;  
		GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));  

		CCLog("\n>>>Mark: %s", mark.c_str());
		CCLog(">>>MemoryTest: current memory used = %dK", pmc.WorkingSetSize/1000);
		CCLog(">>>MemoryTest: peak memory used = %dK", pmc.PeakWorkingSetSize/1000);
		CCLog(">>>MenoryTest: virtual memory used = %dK", pmc.PagefileUsage/1000);
		CCLog(">>>MenoryTest: peak virtual memory used = %dK", pmc.PeakPagefileUsage/1000);
	);
}
