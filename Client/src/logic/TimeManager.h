#ifndef __TimeManager_h__
#define __TimeManager_h__

#include <vector>
#include <string>
#include "utils/MacroUtils.h"

struct TimeKey
{
	TimeKey()
		:toAdd(false)
	{}
	std::string module;
	std::string subModule;
	std::string key;
	bool toAdd;
};

class TimeManager
{
public:
	static TimeManager &instance();

	void update();

	void clear();

private:
	CP_MAKE_STATIC_CLASS(TimeManager);

private:
	void init();

	void addKey(const std::string &module, const std::string &key);
	void addKey(const std::string &module, const std::string &keyHead, int key);
	void addKey(const std::string &module, const std::string &subModule, const std::string &key);
	void addKey(const std::string &module, const std::string &subModule, const std::string &key, bool toAdd);

	void updateNormModule(int index);
	void updateSubModule(int index);

	void toNextTime(int &time, bool toAdd);

private:
	typedef std::vector<TimeKey> TimeVect;
	TimeVect mTimeVect;
};

#endif //__TimeManager_h__