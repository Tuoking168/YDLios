#ifndef __TASKTIPS_LUA__
#define __TASKTIPS_LUA__
#include "cocos2d.h"
#include "script/LuaCBinding.h"
#include "userdata/UserData.h"
using namespace cocos2d;



class TasktipsLua
{
public:
	
	static bool getTasktipsColor( int id, ccColor3B& c );
	static bool getTasktipsSize( int id, int &s );
	static std::vector<TaskTip> getTasktipsStr(std::string str );
	
private:
	TasktipsLua();
	virtual ~TasktipsLua();
};
#endif//__TASKTIPS_LUA__
