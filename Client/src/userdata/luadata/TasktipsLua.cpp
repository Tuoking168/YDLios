#include "stdafx.h"
#include "TasktipsLua.h"
#include "script/LuaWrapper.h"


// TasktipsLua* TasktipsLua::pInstance=NULL;
TasktipsLua::TasktipsLua()
{

}

TasktipsLua::~TasktipsLua()
{

}

// TasktipsLua& TasktipsLua::Instance()
// {
// 	if (!pInstance)
// 	{
// 		static TasktipsLua staticMemory_;
// 		pInstance=&staticMemory_;
// 	}
// 	return *pInstance;
// }

bool TasktipsLua::getTasktipsColor( int id, ccColor3B& c )
{
	short r,g,b;
	Lua::instance()->push(id);
	if(	Lua::instance()->call("tasktips","get_tasktips_color", 1, 3) &&
		Lua::instance()->pop(b),
		Lua::instance()->pop(g),
		Lua::instance()->pop(r))
	{
		c=ccc3(r,g,b);
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_tasktips_color string");
		return false;
	}
}

bool TasktipsLua::getTasktipsSize( int id, int &s )
{
	short n;
	Lua::instance()->push(id);
	if(	Lua::instance()->call("tasktips","get_tasktips_fontsize", 1, 1) &&
		Lua::instance()->pop(n))
	{
		s=n;
		return true;
	}
	else
	{
		CCLog("StaticData, failed to call function name : get_tasktips_fontsize string");
		return false;
	}
}

std::vector<TaskTip> TasktipsLua::getTasktipsStr( std::string str )
{
	
	
	vector<TaskTip> AllTaskContent;
	//vector<string> content;
	string::size_type pos1, pos2;
	pos2 = str.find('>');
	pos1 = str.find('<');    
	while (string::npos != pos2)
	{
		TaskTip Task;
		CCLOG("%s",str.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
		Task.id=atoi(str.substr(pos1 + 1, pos2 - pos1 - 1).c_str());
		getTasktipsSize(Task.id,Task.fontsize);
		getTasktipsColor(Task.id,Task.c);
		//id.push_back(str.substr(pos1 + 1, pos2 - pos1 - 1));
		
		pos1 = pos2 + 1;
		pos1 = str.find('<',pos1);

		//content.push_back(str.substr(pos2 + 1, pos1 - pos2 - 1));
		CCLOG("%s",str.substr(pos2 + 1, pos1 - pos2 - 1).c_str());
		Task.str=str.substr(pos2 + 1, pos1 - pos2 - 1).c_str();
		pos2 = str.find('>', pos1);

		AllTaskContent.push_back(Task);
	}
	
	

	return AllTaskContent;
}

