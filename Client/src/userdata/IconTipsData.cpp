#include "IconTipsData.h"
#include "event/CPEventHelper.h"
#include "userdata/ActivityData.h"
#include "script/LuaWrapper.h"
#include <cstring>

static std::vector<int> emptyIntVector;
static std::map<int,ForgetRewardData> emptyMap;
static std::vector<IconData> emptyIconData;


std::vector<int> IconTipsData::icontips_list=emptyIntVector;
std::map<int,ForgetRewardData> IconTipsData::forgettips_map=emptyMap;
std::vector<IconData> IconTipsData::icontips_icondata=emptyIconData;
bool IconTipsData::m_isInit=false;
IconTipsData::IconArrayData IconTipsData::m_theIconArrayData;
int IconTipsData::m_iOverEventid=0;
int IconTipsData::m_iDoingEventid=0;
int IconTipsData::m_iWillEventid=0;
bool IconTipsData::m_bClickActivity=false;
int IconTipsData::s_iShowWelfare=0;
int IconTipsData::m_iIconCnt=0;


void IconTipsData::initorclear()
{
	for (int i=0;i<T_Max;i++)
	{
		for (int j=0;j<1000;j++)
		{
			IconTipsData::setIconArray(i,j,false);
		}
	}
	IconTipsData::m_isInit=true;
}

bool IconTipsData::getIconArray( int tag,int data )
{
	std::pair<int, int> key = std::make_pair(tag, data);
	IconTipsData::IconArrayData::const_iterator pos = IconTipsData::m_theIconArrayData.find(key);
	if (pos != IconTipsData::m_theIconArrayData.end())
	{
		return pos->second;
	}
	return false;
}

void IconTipsData::setIconArray( int tag,int data,bool flag )
{
	std::pair<int, int> key = std::make_pair(tag, data);
	IconTipsData::m_theIconArrayData[key]=flag;
}

int IconTipsData::getIconCnt()
{
	return IconTipsData::m_iIconCnt;
}

void IconTipsData::setIconCnt( int cnt )
{
	IconTipsData::m_iIconCnt = cnt;
}

void IconTipsData::checkForgetGiftTime()
{
	std::vector<int> deletelist;
	std::map<int,ForgetRewardData>::iterator it = IconTipsData::forgettips_map.begin();
	for (it;it!=IconTipsData::forgettips_map.end();it++)
	{
		if(ActivityData::getWorldTime() >= it->second.endtime)
		{
			deletelist.push_back(it->first);
		}
	}

	std::vector<int>::iterator vecit = deletelist.begin();
	for (vecit;vecit!=deletelist.end();vecit++)
	{
		int dataidx = *vecit;
		std::map<int,ForgetRewardData>::iterator deleteit = IconTipsData::forgettips_map.find(dataidx);
		if (deleteit!=IconTipsData::forgettips_map.end())
		{
			IconTipsData::forgettips_map.erase(deleteit);
		}
		CPEventHelper::msgNotify("HandleMessageFuncDataNotify", "",0,0,dataidx,0);
	}
}

std::string IconTipsData::getForgetGiftStr( int idx )
{
	std::map<int,ForgetRewardData>::iterator it = IconTipsData::forgettips_map.find(idx);
	if (it!=IconTipsData::forgettips_map.end())
	{
		return it->second.str;
	}
	return "";
}

void IconTipsData::addForgetGiftData( int idx,int data,std::string str )
{
	ForgetRewardData newData;
	newData.endtime = data;
	newData.str = str;
	IconTipsData::forgettips_map[idx] = newData;
}

void IconTipsData::removeForgetGiftData( int idx )
{
	std::map<int,ForgetRewardData>::iterator it = IconTipsData::forgettips_map.find(idx);
	if (it!=IconTipsData::forgettips_map.end())
	{
		IconTipsData::forgettips_map.erase(it);
	}
}

int IconTipsData::m_iHollowIID = 0;

int IconTipsData::getHollowIID()
{
	return m_iHollowIID;
}

void IconTipsData::setHollowIID( int iid )
{
	m_iHollowIID = iid;
}

bool IconTipsData::needShowSubWelfare( int index )
{
	if (index < 0)
	{
		index = 0;
	}

	const int mark = 1 << index;
	const int result = s_iShowWelfare & mark;
	return (result != 0);
}

bool IconTipsData::needShowWelfare()
{
	return (s_iShowWelfare > 0);
}

void IconTipsData::setShowSubWelfare( int index, bool needShow )
{
	if (index < 0)
	{
		index = 0;
	}

	const int mark = 1 << index;
	if (needShow)
	{
		s_iShowWelfare |= mark;
	}
	else
	{
		s_iShowWelfare &= ~mark;
	}
}

std::map<int,MailData> IconTipsData::mail_map;

void IconTipsData::addMailData( int idx,std::string str )
{
	std::string gift = "";
	std::string title = "";
	std::string content = "";

	Lua::instance()->push(str);
	if(Lua::instance()->call("translateMail",1,3))
	{
		Lua::instance()->pop(gift);
		Lua::instance()->pop(content);
		Lua::instance()->pop(title);
	}

	MailData newData;
	newData.idx = idx;
	newData.title = title;
	newData.content = content;
	newData.gift = gift;
	IconTipsData::mail_map[idx] = newData;
}

void IconTipsData::removeMailData( int idx )
{
	std::map<int,MailData>::iterator it = IconTipsData::mail_map.find(idx);
	if (it!=IconTipsData::mail_map.end())
	{
		IconTipsData::mail_map.erase(it);
	}
}

std::string IconTipsData::getMailTitleStr( int idx )
{

	std::map<int,MailData>::iterator it = IconTipsData::mail_map.find(idx);
	if (it!=IconTipsData::mail_map.end())
	{
		return it->second.title;
	}
	return "";
}

std::string IconTipsData::getMailContentStr( int idx )
{
	std::map<int,MailData>::iterator it = IconTipsData::mail_map.find(idx);
	if (it!=IconTipsData::mail_map.end())
	{
		string Nothing = "null"; 
		int i = 0;
		for(i = 0; i < 4; i++){
			if (it->second.content[i] != Nothing[i])
			{
				break;
			}
		}
		if (i == 4)
		{
			return "";
		}
		return it->second.content;
	}
	return "";
}

std::string IconTipsData::getMailGiftStr( int idx )
{
	std::map<int,MailData>::iterator it = IconTipsData::mail_map.find(idx);
	if (it!=IconTipsData::mail_map.end())
	{
		return it->second.gift;
	}
	return "";
}



