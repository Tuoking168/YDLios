#include "OptionsHelper.h"
#include "cocos2d.h"
#include "MsgAuth.h"
#include "MsgLogin.h"
#include "UserDataModule.h"
#include "ModuleData.h"

#include "ext/CCFlashAnimation.h"
#include "event/CPEvent.h"
#include "script/LuaWrapper.h"

#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userData/SystemData.h"
#include "userData/netdata/AliveGhost.h"
#include "userdata/luadata/LuaData.h"

#include "network/HandleMessage.h"
#include "network/MsgListener.h"
#include "ErrorDefinition.h"
#include "GuildDefinition.h"
#include "scene/panel/guide/GuideHelper.h"

#include "GuildModule.h"

using namespace cocos2d;

//////////OptionsHelper///////////////////////////////////////////////

int OptionsHelper::m_defaultidx;

int OptionsHelper::getMainSize(std::string tableName)
{
	int value;
	if (LuaData::getProp_size(tableName,0,"",value))
	{
		return value;
	}
	return 0;
}
std::string  OptionsHelper::getMainResource(std::string tableName,int idx)
{
	std::string value;
	if (LuaData::getProp(tableName,idx,"res",value))
	{
		return value;
	}
	return 0;
}
std::string  OptionsHelper::getMainTitle(std::string tableName,int idx)
{
	std::string value;
	if (LuaData::getProp(tableName,idx,"name",value))
	{
		return value;
	}
	return 0;
}
int  OptionsHelper::getMainOwner(std::string tableName,int idx)
{
	int value;
	if (LuaData::getProp(tableName,idx,"owner",value))
	{
		return value;
	}
	return 0;
}
bool  OptionsHelper::hasSubOption(std::string tableName,int idx)
{
	int oSize = getSubSize(tableName,idx);
	return (oSize>0)?true:false;
}
int OptionsHelper::getSubSize(std::string tableName,int idx)
{
	int value;
	if (LuaData::getProp_size(tableName,idx,"elems",value))
	{
		return value;
	}
	return 0;
}
std::string  OptionsHelper::getSubResource(std::string tableName,int idx,int sidx)
{
	std::string value;
	if (LuaData::getProp(tableName,idx,"elems",sidx,"res",value))
	{
		return value;
	}
	return 0;
}
std::string  OptionsHelper::getSubTitle(std::string tableName,int idx,int sidx)
{
	std::string value;
	if (LuaData::getProp(tableName,idx,"elems",sidx,"name",value))
	{
		return value;
	}
	return 0;
}
int  OptionsHelper::getSubOwner(std::string tableName,int idx,int sidx)
{
	int value;
	if (LuaData::getProp(tableName,idx,"elems",sidx,"owner",value))
	{
		return value;
	}
	return 0;
}
int  OptionsHelper::getMainCtrlID(std::string tableName,int idx)
{
	int ret = 0;
	if (LuaData::getProp(tableName,idx,"ctrlid",ret))
	{
		return ret;
	}
	return 0;
}

int OptionsHelper::getSubCtrlID(std::string tableName,int idx,int sidx)
{
	int ret = 0;
	if (LuaData::getProp(tableName,idx,"elems",sidx,"ctrlid",ret))
	{
		return ret;
	}
	return 0;
}
void OptionsHelper::initAllOptionsList(OptionsList& oList,std::string tableName)
{
	if (tableName.length()<=0)
	{
		return;
	}
	int mSize = OptionsHelper::getMainSize(tableName);
	for (int i=1;i<=mSize;i++)
	{
		if (!GuideHelper::canOpenFunction(OptionsHelper::getMainCtrlID(tableName, i)))
		{
			continue;
		}

		OptionsInfo option;
		option.resource = OptionsHelper::getMainResource(tableName,i);
		option.title = OptionsHelper::getMainTitle(tableName,i);
		option.owner = OptionsHelper::getMainOwner(tableName,i);
		option.idx = OptionsHelper::getMainTag(tableName,i);
		oList.push_back(option);
		if (getDefaultTag() == 0)
		{
			setDefaultTag(i);
		}
		if (OptionsHelper::hasSubOption(tableName,i))
		{
			int sSize = OptionsHelper::getSubSize(tableName,i);
			for (int j=1;j<=sSize;j++)
			{
				if (!GuideHelper::canOpenFunction(OptionsHelper::getSubCtrlID(tableName, i, j)))
				{
					continue;
				}
				OptionsInfo option;
				option.resource = OptionsHelper::getSubResource(tableName,i,j);
				option.title = OptionsHelper::getSubTitle(tableName,i,j);
				option.owner = OptionsHelper::getSubOwner(tableName,i,j);
				oList.push_back(option);
			}
		}
	}
	printOptions(oList);
}

void OptionsHelper::openOption(OptionsList& oList,std::string tableName,int idx)
{
	if (!hasSubOption(tableName,idx+1))
		return;
	int sSize = OptionsHelper::getSubSize(tableName,idx+1);
	for (int i=1;i<=sSize;i++)
	 {
		 OptionsInfo option;
		 option.resource = OptionsHelper::getSubResource(tableName,idx+1,i);
		 option.title = OptionsHelper::getSubTitle(tableName,idx+1,i);
		 option.owner = OptionsHelper::getSubOwner(tableName,idx+1,i);
		 OptionsList::iterator itr = oList.begin()+idx+1;
		 oList.insert(itr,option);
 	}
	printOptions(oList);
}
void OptionsHelper::closeOption(OptionsList& oList,std::string tableName,int idx)
{
	if (!hasSubOption(tableName,idx+1))
		return;
	int sSize = OptionsHelper::getSubSize(tableName,idx+1);
	for (int i=1;i<=sSize;i++)
	{
		OptionsList::iterator itr = oList.begin()+idx+1;
		if (itr!=oList.end())
		{
			oList.erase(itr);
		}
	}
	printOptions(oList);
}
void OptionsHelper::printOptions(OptionsList& oList)
{
	for (OptionsList::iterator iter=oList.begin();iter!=oList.end();iter++)  
	{  
		OptionsInfo option = *iter;
		CCLog("__________droid_________sub__t=%s,o=%d",option.title.c_str(),option.owner); 
	} 
}

int OptionsHelper::getMainTag( std::string tableName,int idx )
{
	int value;
	if (LuaData::getProp(tableName,idx,"tag",value))
	{
		return value;
	}
	return 0;
}

int OptionsHelper::getDefaultTag()
{
	return m_defaultidx;
}

void OptionsHelper::setDefaultTag(int idx)
{
	m_defaultidx = idx;
}