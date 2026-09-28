#ifndef __IPlatform_h__
#define __IPlatform_h__

#include <string>
#include <map>
#include "module/PlatformModule.h"
#include "PlatformOpID.h"
#include "utils/MacroUtils.h"

class IPlatform
{
public:
	virtual ~IPlatform();

public:
	virtual void login() = 0;
	virtual void pay(int yuan) = 0;
	virtual void operate(int opID) = 0;
	virtual std::string convert(const std::string &data) = 0;
	virtual void selectGameSever( int selectedserver ) = 0;
};

//////////PlatformManager/////////////////////////////////////////////
class PlatformManager
{
public:
	static PlatformManager &instance();

public:
	void setPlatform(IPlatform *platform);
	IPlatform *getPlatform();

	void setIntData(const std::string &key, int data);
	int getIntData(const std::string &key);

	void setStringData(const std::string &key, const std::string &data);
	std::string getStringData(const std::string &key);

private:
	CP_MAKE_STATIC_CLASS(PlatformManager);

private:
	IPlatform *mPlatform;

	typedef std::map<std::string, std::string> StringMap;
	typedef std::map<std::string, int> IntMap;

	StringMap mStrData;
	IntMap mIntData;
};
#define CPPlatformMnger PlatformManager::instance()
#define CPPlatform CPPlatformMnger.getPlatform()

#endif //__IPlatform_h__