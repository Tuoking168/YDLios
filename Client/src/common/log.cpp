#include "stdafx.h"
#include "log.h"
#include <stdarg.h>

#define MAX_LOG_LEN 2048

static void defaultLogger( const std::string &type, const std::string &content )
{
	std::cout << type << content << std::endl;
}

///////////CPLog///////////////////////////////////////////////////////
CPLogger CPLog::sLogger = defaultLogger;
void CPLog::setLogger( CPLogger logger )
{
	if (logger)
	{
		sLogger = logger;
	}
	else
	{
		sLogger = defaultLogger;
	}
}

void CPLog::log( const std::string &type, const char * pszFormat, ... )
{
	char szBuf[MAX_LOG_LEN];

	va_list ap;
	va_start(ap, pszFormat);
	vsnprintf(szBuf, MAX_LOG_LEN, pszFormat, ap);
	va_end(ap);

	sLogger(type, szBuf);
}

void CPLog::logDebug( const std::string &content )
{
	log("Debug> ", content.c_str());
}

void CPLog::logWarn( const std::string &content )
{
	log("Warn> ", content.c_str());
}

void CPLog::logInfo( const std::string &content )
{
	log("Info> ", content.c_str());
}

void CPLog::logError( const std::string &content )
{
	log("Error> ", content.c_str());
}
