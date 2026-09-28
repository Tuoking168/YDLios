#include "UserData.h"
#include "ModuleData.h"
#include "LoginModule.h"
#include "MapModule.h"
#include "UserDataModule.h"
#include "MsgAuth.h"
#include "MsgLogin.h"
#include "QuestDefinition.h"

#include "utils/StringUtils.h"

#include "UserItemData.h"
#include "UserPetData.h"

#include "network/NetProtocol.h"

#include "scene/GameUI.h"
#include "scene/SceneFactory.h"
#include "scene/LoginHelper.h"
#include "scene/panel/ChatPanel.h"

#include "userdata/netdata/GhostManager.h"
#include "userdata/mapdata/PixesMap.h"
#include "userdata/netdata/Ghost.h"
#include "userdata/netdata/ItemGhost.h"
#include "GameData.h"
#include "SystemData.h"
#include "netdata/GameRole.h"
#include "userdata/netdata/AliveGhost.h"
#include "userdata/mapdata/MapData.h"
#include "userdata/teamdata/TeamData.h"

#include "ext/CCFileDataStream.h"
#include "ext/CCFlashAnimation.h"

#include "userdata/mapdata/PixesMap.h"
#include "userdata/CacheData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/OtherRole.h"
#include "userdata/statetimer/FightingState.h"
#include "LayoutData.h"
#include "userdata/luadata/LuaData.h"
#include "IconTipsData.h"

#include "res/Path.h"
#include "res/AudioLoader.h"
#include "res/CPAnimationManager.h"

#include "controls/CPNodeHelper.h"

#include "event/EventDispatcher.h"
#include "event/EventProtocol.h"

#include "network/HandleMessage.h"

#include "HeroData.h"
#include "ModuleData.h"
#include "ActivityData.h"
#include "GuildData.h"
#include "SceneData.h"
#include "TaskData.h"
#include "WorldData.h"

#include "logic/CPUpdateFunctor/CPUpdateFunctorManager.h"

#include "logic/platform/IPlatform.h"
#include "../../ios/channel/common/ChannelHelper.h"


long UserData::m_currenttime = 0;
UserData::UserData()
: m_pMainRole(NULL)
, m_pOtherRole(NULL)
, m_pingtime(0)
, m_bAttackModeChanged(false)
, m_bLevelChanged(false)
, m_bExperienceChanged(false)
, m_pPixesMap(NULL)
, m_bCharListRecieved(false)
,m_changeEquipMsg(false)
,m_bIsMainPanel(false)
,m_bIsFloatPanel(false)
,ChangePos(0)
,ChangeTypeID(0)
,m_skillSelectIce(false)
, m_itemKeyUsePos(-1)
, m_itemKeyUseID(0)
, mPayType(0)
, m_whetherChishaUse(0)
, m_whetherBanyueUse(0)
, m_bloadCompleted(0)
{
	m_pGhostManager = new GhostManager();
	m_pMainRole = GameRole::create(millisecondNow());
	m_pOtherRole = OtherRole::create();
	userItemData = NULL;
	userPetData = NULL;
}

UserData::~UserData()
{
	for(std::map<int,NetItem*>::iterator it=mOthersItems.begin(); it!=mOthersItems.end(); it++)
	{
		if(it->second)
		{
			delete it->second;
		}
	}
	mOthersItems.clear();
	if (m_pPixesMap)
	{
		delete m_pPixesMap;
		m_pPixesMap = NULL;
	}
	if (m_pGhostManager)
	{
		delete m_pGhostManager;
		m_pGhostManager = NULL;
	}

	if(userItemData)
	{
		userItemData->clear();
		delete userItemData;
		userItemData = NULL;
	}

	if(userPetData)
	{
		userPetData->clear();
		delete userPetData;
		userPetData = NULL;
	}
	
	if (m_pMainRole)
	{
		m_pMainRole->release();
		m_pMainRole = NULL;
	}
	if (m_pOtherRole)
	{
		m_pOtherRole->release();
		m_pOtherRole = NULL;
	}
}	

void UserData::enterGameRequest()
{
	const int pid = HeroData::getPID();
	const bool hasEnter = SceneData::hasEnterScene();
	releaseModuleData();
	HeroData::setPID(pid);
	SceneData::setHasEnterScene(hasEnter);

	MsgEnterGameRequest* req = new MsgEnterGameRequest;
	req->pid = pid;
	HandleMessage::sendMessage(req);
	//
	//return;
	MsgEnterCrossGameRequest* csreq = new MsgEnterCrossGameRequest;
	csreq->serverid = CPPlatformMnger.getIntData(CPPlatformData::SERVER_ID);
	csreq->pid = pid;
	HandleMessage::sendMessage(csreq);
    
#if defined APPSTORE_VERSION
    CHANNELHELPER->checkOrder();
#endif
}

void  UserData::switch2GameScene()
{	 
	releaseDataForTransfer();

	//
	m_pPixesMap = new PixesMap();
	m_pMainRole->setState(AVATAR_ACTION_IDLE);
	m_pGhostManager->addGhost(m_pMainRole);

	//
	if (SceneData::hasEnterScene())
	{
		Game::changeMap();
	}
	else
	{
		CCDirector::sharedDirector()->replaceScene(SceneFactory::sceneGame());
	}
}

void UserData::releaseDataForTransfer()
{
	for(int i=0; i<AVATAR_TYPE_NUMBER; i++)
	{
		for(int j=0; j<AVATAR_ACTION_COUNT; j++)
		{
			m_pMainRole->m_nCurrentDress[i][j] = 0;
		}
	}

	if (m_pPixesMap)
	{
		delete m_pPixesMap;
		m_pPixesMap = NULL;
	}

	CCCacheData::sharedCacheData()->releaseCacheDataFT();
	CPAnimMnger.clear(false);
}

void UserData::releaseGameData()
{
	releaseDataForTransfer();
	releaseModuleData();
	releaseUIData();
}

void UserData::releaseModuleData()
{
	if (m_pGhostManager)
	{
		m_pGhostManager->release();
	}

	if (m_pMainRole)
	{
		m_pMainRole->release();
		m_pMainRole = GameRole::create(millisecondNow());
	}

	if(userItemData)
	{
		userItemData->clear();
		delete userItemData;
		userItemData = NULL;
	}

	if(userPetData)
	{
		userPetData->clear();
		delete userPetData;
		userPetData = NULL;
	}

	IconTipsData::icontips_icondata.clear();
	IconTipsData::initorclear();
	TeamData::mTeamMembers.clear();
	HeroData::clear();
	LoginHelper::clear();
	ActivityData::clear();
	GuildData::clear();
	SceneData::clear();
	TaskData::clearTasks();
	WorldData::clearWorldData();
	ChatPanelHelper::clearChat();

	CPUpdateFunctorManager::instance()->onClear();
}

void UserData::releaseUIData()
{
	CCTextureCache::sharedTextureCache()->removeAllTextures();
	CCSpriteFrameCache::sharedSpriteFrameCache()->purgeSharedSpriteFrameCache();
	CCCacheData::sharedCacheData()->releaseCacheDataAll();
}

long UserData::millisecondNow()
{ 
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now, NULL); 
	m_currenttime = now.tv_sec * 1000 + now.tv_usec / 1000;
	return m_currenttime;
}

long UserData::getTime()
{
	return m_currenttime;
}

void UserData::addMapConnGhost(NetMapConn* pConn)
{
	//创建对应地图传送点的ghost，并运行动画
	CCSprite *bodySprite = CCSprite::create();
	Ghost *ghost = new Ghost;
	ghost->init(bodySprite);
	ghost->setMapPosition(0, pConn->mFromX, pConn->mFromY);
	m_pGhostManager->addGhost(ghost);

	const CCSize &animSize = LayoutData::getSize(CPModuleName::COMMON, "portalName");
	const std::string &key = LayoutData::getString(CPModuleName::MAP, "portalAnim");
	CCFlashAnimation *anim = SystemData::getAnimationOneDir(key);
	CCSprite *portal = CCSprite::create();
	bodySprite->addChild(portal);
	if (anim)
	{
		portal->setPosition(ccp(animSize.width/2, animSize.height/2));
		portal->runAction(CCRepeatForever::create(anim->getAnimate(0)));

		bodySprite->setContentSize(animSize);
	}

	// name label
	CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::MAP, "portalBigName");
	nameLabel->setString(pConn->mDesMapName.c_str());
	nameLabel->setPosition(ccp(animSize.width/2, animSize.height + animSize.height/2));
	bodySprite->addChild(nameLabel);
}

void UserData::addMapConns()
{
	//读取当前地图数据中的所有传送点，创建对应ghost
	if(GameData::s_map->mMiniMapConn.find(mMap.mID) == GameData::s_map->mMiniMapConn.end())
	{
		return;
	}

	MapConnVect &mapconns = GameData::s_map->mMiniMapConn[mMap.mID];
	for(unsigned int i = 0; i < mapconns.size(); i++)	
	{
		NetMapConn* pConn = mapconns[i];
		if(pConn)
		{
			addMapConnGhost(pConn);			
		}
		else
		{
			CCLog("ERROR, null map conns.");
		}
	}
}

UserItemData* UserData::getUserItemData()
{
	if(!userItemData)
	{
		userItemData = new UserItemData();
	}
	return userItemData;
}

void UserData::UpdStoneArray()
{
	if (!m_pMainRole) return;
	for (int i=0;i<16;i++)
	{
		for (int j=0;j<5;j++)
		{
			m_pMainRole->m_pStoneArray[i][j]=NULL;
		}
	}

	UserItems& items = getUserItemData()->userItems;
	int n=0;
	int m=n;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem && pItem->position<ItemPosition_stone_begin && pItem->position>ItemPosition_stone_end)
		{
			int i=(ItemPosition_stone_begin-1-pItem->position)/5;
			int j=(ItemPosition_stone_begin-1-pItem->position)%5;
			m_pMainRole->m_pStoneArray[i][j]=pItem;
		}
	}

}

UserPetData* UserData::getUserPetData()
{
	if(!userPetData)
	{
		userPetData = new UserPetData();
	}
	return userPetData;
}

void UserData::loadData()
{
	ModuleData::loadModule(CPModuleName::USER_DATA);
}

void UserData::saveData()
{
	ModuleData::saveModule(CPModuleName::USER_DATA);
}

void UserData::setIntData( const std::string &key, int data )
{
	ModuleData::setInt(CPModuleName::USER_DATA, key, data);
}

void UserData::setIntData( int pid, const std::string &key, int data )
{
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::setInt(pid, key, data);
}

void UserData::setIntData( int pid, const std::string &key, int id, int data )
{
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::setInt(pid, key + StringUtils::toString(id), data);
}

void UserData::setStringData( const std::string &key, const std::string &data )
{
	ModuleData::setString(CPModuleName::USER_DATA, key, data);
}

void UserData::setStringData( int pid, const std::string &key, const std::string &data )
{
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::setString(pid, key, data);
}

void UserData::setStringData( int pid, const std::string &key, int id, const std::string &data )
{
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::setString(pid, key + StringUtils::toString(id), data);
}

void UserData::setStringData( const std::string &key, const std::string &data,int tag )
{
//	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DOWNLOAD_FILELIST_VERSION);
//	SubModuleData::setString(key, data,0);
}

int UserData::getIntData( const std::string &key )
{
	int ret = 0;
	ModuleData::getInt(CPModuleName::USER_DATA, key, ret);
	return ret;
}

int UserData::getIntDataForSeverPick( const std::string &key )
{
	int ret = -1;
	ModuleData::getInt(CPModuleName::USER_DATA, key, ret);
	return ret;
}

int UserData::getIntData( int pid, const std::string &key )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::getInt(pid, key, ret);
	return ret;
}

int UserData::getIntData( int pid, const std::string &key, int id )
{
	int ret = 0;
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::getInt(pid, key + StringUtils::toString(id), ret);
	return ret;
}

std::string UserData::getStringData( const std::string &key )
{
	std::string ret;
	ModuleData::getString(CPModuleName::USER_DATA, key, ret);
	return ret;
}

std::string UserData::getStringData( int pid, const std::string &key )
{
	std::string ret;
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::getString(pid, key, ret);
	return ret;
}

std::string UserData::getStringData( int pid, const std::string &key, int id )
{
	std::string ret;
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::getString(pid, key + StringUtils::toString(id), ret);
	return ret;
}

std::string UserData::getStringData( const std::string &key,int tag )
{
	std::string ret;
//	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DOWNLOAD_FILELIST_VERSION);
//	LuaData::getProp("download_filelist_version",key,ret);
	return ret;
}

void UserData::clear( int pid )
{
	SubModuleData::init(CPModuleName::USER_DATA, CPUserData::DATA_DEPEND_PID);
	SubModuleData::clearData(pid);
}

void UserData::initSetting()
{
	AudioLoader::setSilent(UserData::getIntData(CPUserData::BGM_OFF));
	AudioLoader::setEffectSilent(UserData::getIntData(CPUserData::EFFECT_OFF));
}

int UserData::getemptyFast()
{
	for (int i=0;i<8;i++)
	{
		int type=UserData::getIntData(HeroData::getPID(),CPUserData::FAST_NUM_,i+1);
		int sid=UserData::getIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,i+1);
		if (type==0)
		{
			return i+1;
		}
	}
	return 0;
}

void UserData::clearOtherRole()
{
	if (m_pOtherRole)
	{
		m_pOtherRole->release();
		m_pOtherRole = NULL;
		m_pOtherRole = OtherRole::create();
	}
}


