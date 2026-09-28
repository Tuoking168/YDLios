#include "MineData.h"
#include "UserItemData.h"
#include "UserData.h"
#include "GameData.h"
#include <cstring>
#include "SystemData.h"

static std::map<int,int> emptyMap;


std::map<int,int> MineData::minedata_map=emptyMap;

void MineData::addMine( int sid ,int count)
{
	if (!isMine(sid))
	{
		CCLog("%d isn't mine",sid);
		return ;
	}
	std::map<int, int>::iterator it =  MineData::minedata_map.find(sid);
	if (it== MineData::minedata_map.end())
	{
		MineData::minedata_map[sid] = count;
	}
	else
	{
		MineData::minedata_map[sid] += count;
	}
	CCLog("%d count is %d",sid,MineData::minedata_map[sid]);
}

void MineData::clear()
{
	MineData::minedata_map.clear();
}

int MineData::getNewMineCount( int sid )
{
	std::map<int, int>::iterator it =  MineData::minedata_map.find(sid);
	if (it== MineData::minedata_map.end())
	{
		return 0;
	}
	return it->second;
}

int MineData::getAllMineCount( int sid )
{
	return GameData::s_user->getUserItemData()->getItemCntBySid(sid);
}

bool MineData::isMine( int itemsid )
{
	for (int i =1;i<=3;i++)
	{
		CCString* pStrSize = CCString::createWithFormat(SystemData::getLayoutString("Mine_panel_text_size_").c_str(),i);
		for (int j =1;j<=SystemData::getLayoutValue(pStrSize->getCString());j++)
		{
			CCString* pStrSub = CCString::createWithFormat(SystemData::getLayoutString("Mine_panel_text_sub_").c_str(),i,j);
			int sid = SystemData::getLayoutValue(pStrSub->getCString());
			if (itemsid == sid)
			{
				return true;
			}
		}
	}
	return false;
}

