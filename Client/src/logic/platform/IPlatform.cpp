#include "IPlatform.h"
#include "ModuleData.h"

IPlatform::~IPlatform()
{
	//
}

///////PlatformManager//////////////////////////////////////////////////////
PlatformManager::PlatformManager()
	:mPlatform(NULL)
{
	
}

PlatformManager::~PlatformManager()
{
	if (mPlatform)
	{
		delete mPlatform;
		mPlatform = NULL;
	}
}

PlatformManager & PlatformManager::instance()
{
	static PlatformManager ret;
	return ret;
}

void PlatformManager::setPlatform( IPlatform *platform )
{
	if (mPlatform)
	{
		delete mPlatform;
	}
	mPlatform = platform;
}

IPlatform * PlatformManager::getPlatform()
{
	return mPlatform;
}

void PlatformManager::setIntData( const std::string &key, int data )
{
	mIntData[key] = data;
}

int PlatformManager::getIntData( const std::string &key )
{
	IntMap::iterator it = mIntData.find(key);
	if (it != mIntData.end())
	{
		return it->second;
	}
	return 0;
}

void PlatformManager::setStringData( const std::string &key, const std::string &data )
{
	mStrData[key] = data;
}

std::string PlatformManager::getStringData( const std::string &key )
{
	StringMap::iterator it = mStrData.find(key);
	if (it != mStrData.end())
	{
		return it->second;
	}
	return "";
}


