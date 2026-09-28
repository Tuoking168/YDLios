#include "StringUtils.h"
#include "CCCommon.h"

#include "userdata/LayoutData.h"
#include "userdata/SystemData.h"
#include "script/LuaWrapper.h"


using namespace cocos2d;


#define S_PER_M 60
#define M_PER_H 60
#define S_PER_H 3600
#define H_PER_D 24


std::string StringUtils::toString( int data )
{
	char ch[128];
	sprintf(ch, "%d", data);
	return ch;
}

std::string StringUtils::timeToString( int time, int timeType )
{
	// honor, minute, second
	int data[4] = { (time/S_PER_H)/H_PER_D,(time/S_PER_H)%H_PER_D, (time%S_PER_H)/S_PER_M, time%S_PER_M};
	std::string str[4];
	for (int i = 0; i < 4; i++)
	{
		str[i] = toString(data[i]);
		if (data[i] < 10 && timeType != TimeType::dhms && timeType != TimeType::dh)
		{
			str[i] = "0" + str[i];
		}
	}
	
	//
	switch (timeType)
	{
	case TimeType::ms:
		{
			return str[2] + ":" + str[3];
		}
	case TimeType::hm:
		{
			return str[1] + ":" + str[2];
		}
	case TimeType::hms:
		{
			return str[1] + ":" + str[2] + ":" + str[3];
		}
	case TimeType::dhms:
		{
			const std::string &m_Day = SystemData::getLayoutString("timelimitgift.label.timelimit.day");
			const std::string &m_Hour = SystemData::getLayoutString("onlinegift.label.time.hour");
			const std::string &m_Min = SystemData::getLayoutString("onlinegift.label.time.min");
			const std::string &m_Sec = SystemData::getLayoutString("onlinegift.label.time.sec");
			return str[0] + m_Day + str[1] + m_Hour + str[2] + m_Min + str[3] + m_Sec;
		}
	case TimeType::dh:
		{
			const std::string &m_Day = SystemData::getLayoutString("timelimitgift.label.timelimit.day");
			const std::string &m_Hour = SystemData::getLayoutString("onlinegift.label.time.hour");
			return str[0] + m_Day + str[1] + m_Hour;
		}
	}

	CCLog(">>>Error: StringUtils::timeToString, unknown timeType = %d", timeType);
	return "";
}

std::string StringUtils::levelToString( int reborn, int level )
{
	if (reborn < 0)
	{
		reborn = 0;
	}

	if (level < 0)
	{
		level = 1;
	}
	std::string rebornStr;
	std::string levelStr;
	if (reborn > 0)
	{
		rebornStr = toString(reborn) + LayoutData::getString(CPModuleName::COMMON, "reborn");
	}
	levelStr = toString(level) + LayoutData::getString(CPModuleName::COMMON, "level");
	return rebornStr + levelStr;
}

bool StringUtils::filterString( const std::string &inString, std::string &outString )
{
	bool permited = true;
	Lua::instance()->push(inString);
	if (Lua::instance()->call("g_get_string_permit", 1, 2) &&
		Lua::instance()->pop(permited) &&
		Lua::instance()->pop(outString))
	{
		return permited;
	}
	CCLog(">>>Error: StringUtils::filterString, inString = %s", inString.c_str());
	return true;
}

bool StringUtils::hasSpecialWords( const std::string &str )
{
	const char *result = U8ToA(str.c_str());
	return (result == NULL);
}

std::string StringUtils::getFormatTime(time_t t_time)
{
	time_t _Time = t_time;
	//unsigned long long timestamp = localtime(&_Time);
	struct tm *ptm = localtime(&_Time);
	char tmp[100] = {0};
	memset(tmp, 0x0, 100);
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", ptm);
	return tmp;
}

