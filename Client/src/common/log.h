#ifndef __log_h__
#define __log_h__


#include <iostream>
#include <string>
#include <sstream>

typedef void (*CPLogger)( const std::string &type, const std::string &content );
class CPLog
{
public:
	static void setLogger(CPLogger logger);

	static void log(const std::string &type, const char * pszFormat, ...);
	static void logDebug(const std::string &content);
	static void logWarn(const std::string &content);
	static void logInfo(const std::string &content);
	static void logError(const std::string &content);

private:
	static CPLogger sLogger;
};

#define LOG(lvl, message)	do{ \
	std::ostringstream oss;	\
	oss << message; \
	CPLog::log(lvl, oss.str().c_str()); \
 }while(0);

#ifdef _DEBUG
#define LOG_DEBUG(message)	LOG("Debug> ", message)	
#else
#define LOG_DEBUG(message) LOG("Debug> ", message)
#endif

#define LOG_WARN(message)	LOG("Warn> ", message)	

#define LOG_INFO(message)	LOG("Info> ", message)	

#define LOG_ERROR(message)	LOG("Error> ", message)

#define LOG_TRACE CPLog::log("Trace> ", "%s(%d)", __FUNCTION__, __LINE__);

#endif //__log_h__

