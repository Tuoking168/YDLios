#include "stdafx.h"
#include "MsgLogger.h"

#pragma warning( push )
#pragma warning( disable : 4996)

MsgLogger::MsgLogger(void)
{
}


std::string MsgLogger::dump(char& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%d", val );
#else
	snprintf( buf, 64, "%d", val );
#endif

	ret = buf;
	return ret;
}

std::string MsgLogger::dump(unsigned char& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%d", val );
#else
	snprintf( buf, 64, "%d", val );
#endif
	ret = buf;
	return ret;
}

std::string MsgLogger::dump(short& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%d", val );
#else
	snprintf( buf, 64, "%d", val );
#endif
	ret = buf;
	return ret;
}

std::string MsgLogger::dump(unsigned short& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%d", val );
#else
	snprintf( buf, 64, "%d", val );
#endif
	ret = buf;
	return ret;
}

std::string MsgLogger::dump(int& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%d", val );
#else
	snprintf( buf, 64, "%d", val );
#endif

	ret = buf;
	return ret;
}

std::string MsgLogger::dump(unsigned int& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%d", val );
#else
	snprintf( buf, 64, "%d", val );
#endif
	ret = buf;
	return ret;
}

std::string MsgLogger::dump(int64& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%lld", val );
#else
	snprintf( buf, 64, "%lld", val );
#endif
	ret = buf;
	return ret;
}

std::string MsgLogger::dump(uint64& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%lld", val );
#else
	snprintf( buf, 64, "%lld", val );
#endif
	ret = buf;
	return ret;
}

std::string MsgLogger::dump(float& val)
{
	char buf[64];
	std::string ret;
#ifdef WIN32
	sprintf_s( buf, 64, "%f", val );
#else
	snprintf( buf, 64, "%f", val );
#endif

	ret = buf;
	return ret;
}

std::string MsgLogger::dump(std::string& val)
{
	return val;
}

#pragma warning( pop )
