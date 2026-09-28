#include "Path.h"
#include "platform/CCFileUtils.h"
#include <string>
#include "cocos2d.h"

using namespace cocos2d;


std::string PathR::_path_header;



void PathR::convert(std::string& path)
{
	path = _path_header + path;
}

void PathR::convert(std::string& path, const char* relative)
{
	path = _path_header + relative;
}

const char* PathR::convert(const char* relative)
{
	_path_data = _path_header + relative;
	return _path_data.c_str();
}

void PathR::initialize()
{
	//const char* relative = "data-c/game.conf";
    const char* relative = "data-a/gameconf.lua";
	_path_header = cocos2d::CCFileUtils::sharedFileUtils()->fullPathForFilename(relative);
	size_t pos = _path_header.find(relative);
    /*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #if __IPHONE_OS_VERSION_MAX_ALLOW > __IPHONE_6_1
    #else
        pos = _path_header.find("data-a//gameconf.lua");
    #endif
#endif
     */
    if (pos==std::string::npos)
	{
		pos = _path_header.find("data-a//gameconf.lua");
	}
    
	if (pos==std::string::npos)
	{
		_path_header = "invalid header--+//";
	}
	else
	{
		_path_header = _path_header.substr(0, pos);
	}
}

std::string PathW::_path_header;



void PathW::convert(std::string& path)
{
	path = _path_header + path;
}

void PathW::convert(std::string& path, const char* relative)
{
	path = _path_header + relative;
}

const char* PathW::convert(const char* relative)
{
	_path_data = _path_header + relative;
	return _path_data.c_str();
}

void PathW::initialize()
{
	_path_header = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath();
}