#include "SocialData.h"

static bool find(const SocialData::RelationList &data, const int pid)
{
	for (int i = 0; i < (int)data.size(); i++)
	{
		if (data[i].pid == pid)
		{
			return true;
		}
	}
	return false;
}

/////////SocialData//////////////////////////////////////////////
SocialData::RelationList SocialData::mFriends;
SocialData::RelationList SocialData::mMasters;
SocialData::RelationList SocialData::mApprentices;
SocialData::RelationList SocialData::mCouples;
SocialData::RelationList SocialData::mEnemies;

SocialData::RelationList SocialData::mMasterList;
SocialData::RelationList SocialData::mApprenticeList;

int SocialData::delPid(-1);
std::string SocialData::delName("");
int SocialData::delType(-1);

int SocialData::masterPid(-1);
std::string SocialData::masterName("");
int SocialData::apprenticePid(-1);
std::string SocialData::apprenticeName("");

int SocialData::bridegroomPid(-1);
std::string SocialData::bridegroomName("");
int SocialData::bridePid(-1);
std::string SocialData::brideName("");

std::string SocialData::notifyMsgKey("");
std::string SocialData::notifyMsgValue("");

bool SocialData::isFriend( const int pid )
{
	return find(mFriends, pid);
}

bool SocialData::isMaster( const int pid )
{
	return find(mMasters, pid);
}

bool SocialData::isApprentice( const int pid )
{
	return find(mApprentices, pid);
}

bool SocialData::isCouple( const int pid )
{
	return find(mCouples, pid);
}

bool SocialData::isEnemy( const int pid )
{
	return find(mEnemies, pid);
}

//----------------------------Friend Map-------------------------------------//
std::map<int ,std::string> SocialData::addFriendMap;
void SocialData::addFriendData( int pid,const std::string& name )
{
	addFriendMap[pid] = name;
}

void SocialData::rmvFriendData( int pid,const std::string& name )
{
	std::map<int ,std::string>::iterator it = addFriendMap.find(pid);
	if (it!=addFriendMap.end())
	{
		addFriendMap.erase(it);
	}
}

std::string SocialData::getFriendName( int pid )
{
	std::map<int ,std::string>::iterator it = addFriendMap.find(pid);
	if (it!=addFriendMap.end())
	{
		return it->second;
	}
	return "NoBody";
}

//--------------------------- Marter Map-------------------------------------//
std::map<int ,std::string> SocialData::addMasterMap;
void SocialData::addMasterData( int pid,const std::string& name )
{
	addMasterMap[pid] = name;

}

void SocialData::rmvMarsterData( int pid,const std::string& name )
{
	std::map<int ,std::string>::iterator it = addMasterMap.find(pid);
	if (it!=addMasterMap.end())
	{
		addMasterMap.erase(it);
	}

}

std::string SocialData::getMasterName( int pid )
{

	std::map<int ,std::string>::iterator it = addMasterMap.find(pid);
	if (it!=addMasterMap.end())
	{
		return it->second;
	}
	return "NoBody";
}

//----------------------------Apprentice Map-------------------------------------//
std::map<int ,std::string> SocialData::addApprenticeMap;
void SocialData::addApprenticeData( int pid,const std::string& name )
{
	addApprenticeMap[pid] = name;

}

void SocialData::rmvApprenticeData( int pid,const std::string& name )
{
	std::map<int ,std::string>::iterator it = addApprenticeMap.find(pid);
	if (it!=addApprenticeMap.end())
	{
		addApprenticeMap.erase(it);
	}

}

std::string SocialData::getApprenticeName( int pid )
{

	std::map<int ,std::string>::iterator it = addApprenticeMap.find(pid);
	if (it!=addApprenticeMap.end())
	{
		return it->second;
	}
	return "NoBody";
}

int SocialData::getFriendDataCnt()
{
	return addFriendMap.size();
}

int SocialData::getMasterDataCnt()
{
	return addMasterMap.size();

}

int SocialData::getApprenticeDataCnt()
{
	return addApprenticeMap.size();

}

std::map<int ,std::string>& SocialData::getFriendList()
{
	return addFriendMap;
}

std::map<int ,std::string>& SocialData::getMasterList()
{
	return addMasterMap;
}

std::map<int ,std::string>& SocialData::getApprenticeList()
{
	return addApprenticeMap;
}





