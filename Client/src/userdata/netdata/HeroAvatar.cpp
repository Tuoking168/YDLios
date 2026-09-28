#include "HeroAvatar.h"
#include "UserDataModule.h"

#include "ext/CCFlashAnimation.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/socialdata/SocialData.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"

#include "utils/StringUtils.h"
#include "EntityDefinition.h"


#define REBORN_LABEL_TAG 31
#define VIP_LABEL_TAG 32
#define GUILD_NAME_TAG 33
#define COUPLE_NAME_TAG 34


HeroAvatar::HeroAvatar()
: AliveGhost()
,mHeadNameContainer(NULL)
{
}

HeroAvatar::~HeroAvatar()
{
}

void HeroAvatar::runAvatarAnimation()
{
	AliveGhost::runAvatarAnimation();
	//__super::runAvatarAnimation();
}
bool HeroAvatar::init()
{
	if (m_pBodySprite)
	{
		m_pBodySprite->release();
		m_pBodySprite=NULL;
	}

	m_pBodySprite = CCSprite::create();
	m_pBodySprite->retain();
	if (mType == GHOST_TYPE_PLAYER || mType == GHOST_TYPE_THIS)
	{
		char url[60];
		for ( int index = 0; index < AVATAR_TYPE_NUMBER; index ++ )
		{
			m_pSprite[index] = CCSprite::create();
			if (m_pBodySprite)
			{
				m_pBodySprite->addChild(m_pSprite[index]);
			}

			const int &dressID = getDress(index);
			if (dressID > 0)
			{
				sprintf(url,"%s_%d", SystemData::getAnimationName(dressID, mType, index, mGhostGender).c_str(),m_state);
				std::string strurl = url;
				std::string strpng = "data-a/animation/" + strurl + ".png";
				safeToLoad(index, m_state, strurl);
				m_nCurrentDress[index][m_state] = dressID;
			}

		}
	}

	m_sprShadow = SystemData::getSpriteByPlist("ui.ghost.shadow");
	m_sprShadow->_setZOrder(AVATAR_SHADOW_ZORDER);
	if (m_pBodySprite)
	{
		m_pBodySprite->addChild(m_sprShadow);
	}

	initName();

	const short& dir=getDirection();
	setMapPosition(dir, mTx, mTy);

	if (isDead())
	{
		setState(AVATAR_ACTION_DIE);
	}

	runAnimation();

	return true;
}

// ?????????????
// ??????dt - ??????????????delta time??
void HeroAvatar::update( float dt )
{
	// ???????????VIP??????????????????????VIP?????bug
	// ??????AliveGhost::update(dt);
	// ????????????????????update???????????????????????
	
	// 1. ????????????
	// ????true??????????????????????????
	// ????????????VIP????????????????????
	refreshNameLabel(true);
	
	// 2. ??????????????
	// ???????AliveGhost???????????????????????????????
	AliveGhost::update(dt);
	
	// 3. ???????????/????
	// ?????????????????????
	bool visible = (UserData::getIntData(HeroData::getPID(), CPUserData::HIDE_WING) == 0);
	
	// ?????????????????????????????
	if (m_pSprite[AVATAR_TYPE_WINGS])
	{
		// visible?true???????false???????
		m_pSprite[AVATAR_TYPE_WINGS]->setVisible(visible);
	}
	
	// ????????????????????????????????????
	// ??????????????????????????????????????????
}

void HeroAvatar::initName()
{
	AliveGhost::initName();
	if (m_disName)
	{
		CCLabelTTF *rebornLabel = dynamic_cast<CCLabelTTF *>(m_disName->getChildByTag(REBORN_LABEL_TAG));
		if (!rebornLabel)
		{
			rebornLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "aliveGhostName");
			m_disName->addChild(rebornLabel, 0, REBORN_LABEL_TAG);
		}

		CCNode *vipLabelNode = m_disName->getChildByTag(VIP_LABEL_TAG);
		if (!vipLabelNode)
		{
			vipLabelNode = CCNode::create();
			m_disName->addChild(vipLabelNode, 0, VIP_LABEL_TAG);
		}

		CCLabelTTF *guildNameLabel = dynamic_cast<CCLabelTTF *>(m_disName->getChildByTag(GUILD_NAME_TAG));
		if (!guildNameLabel)
		{
			guildNameLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "guildName");
			m_disName->addChild(guildNameLabel, 0, GUILD_NAME_TAG);
			refreshGuildLabel();
		}

		CCLabelTTF *coupleNameLabel = dynamic_cast<CCLabelTTF *>(m_disName->getChildByTag(COUPLE_NAME_TAG));
		if (!coupleNameLabel)
		{
			coupleNameLabel = LayoutData::getLabelTTF(CPModuleName::COMMON, "guildName");
			m_disName->addChild(coupleNameLabel, 0, COUPLE_NAME_TAG);
			refreshCoupleLabel();
		}

		initHeadName();
	}
}

void HeroAvatar::initHeadName()
{
	if (!mHeadNameContainer)
	{
		mHeadNameContainer = CCNode::create();
		m_disName->addChild(mHeadNameContainer);
	}
	refreshHeadName();
}

void HeroAvatar::refreshNameLabel( bool visible )
{
	AliveGhost::refreshNameLabel(visible);
	if (m_disName)
	{
		int ox = 0;
		refreshRebornLabel(ox);
		refreshVIPLabel(ox);
		refreshGuildLabel();
		refreshCoupleLabel();

		// head name
		if (mHeadNameContainer)
		{
			mHeadNameContainer->setVisible(UserData::getIntData(HeroData::getPID(), CPUserData::HIDE_HEADNAME) == 0);
		}
	}
}

void HeroAvatar::setExData( int type, int data )
{
	AliveGhost::setExData(type, data);
	if (type == Entity::attr_open_headtitle)
	{
		refreshHeadName();
	}
}

void HeroAvatar::setExStr( int type, const std::string &str )
{
	AliveGhost::setExStr(type, str);
	if (type == Entity::attr_name_id)
	{
		mName = str;
	}
	else if (type == Entity::attr_couple_name_id)
	{
		refreshCoupleLabel();
	}
}

void HeroAvatar::refreshRebornLabel( int &ox )
{
	const CCSize &nameSize = m_disName->getContentSize();
	CCLabelTTF *rebornLabel = dynamic_cast<CCLabelTTF *>(m_disName->getChildByTag(REBORN_LABEL_TAG));
	if (rebornLabel)
	{
		if (mType == GHOST_TYPE_THIS)
		{
			mReborn = HeroData::getProp(Entity::attr_reborn);
		}

		std::string str;
		ccColor3B color = ccWHITE;
		if (mReborn > 0)
		{
			StaticData::getRebornStrAndColor(mReborn, str, color);
		}
		rebornLabel->setString(str.c_str());
		rebornLabel->setColor(color);
		rebornLabel->setAnchorPoint(ccp(0, 0.5f));
		rebornLabel->setPosition(ccp(-rebornLabel->getContentSize().width + ox, nameSize.height/2));
		ox -= rebornLabel->getContentSize().width;
	}
}

void HeroAvatar::refreshVIPLabel( int &ox )
{
	const CCSize &nameSize = m_disName->getContentSize();
	CCNode *vipLabelNode = m_disName->getChildByTag(VIP_LABEL_TAG);
	if (vipLabelNode)
	{
		vipLabelNode->removeAllChildren();
		const int vipLevel = getExData(Entity::attr_vip_level);
		if (vipLevel > 0)
		{
			const std::string &path = LayoutData::getString(CPModuleName::COMMON, "vipNumber");
			const CCSize &vipSize = LayoutData::getSize(CPModuleName::COMMON, "vipNumber");
			CCLabelAtlas *vipLabel = CCLabelAtlas::create(StringUtils::toString(vipLevel).c_str(), path.c_str(), vipSize.width, vipSize.height, '0');
			vipLabel->setAnchorPoint(ccp(0, 0.5f));
			vipLabel->setPosition(ccp(-vipLabel->getContentSize().width + ox, nameSize.height/2));
			vipLabelNode->addChild(vipLabel);
			ox -= vipLabel->getContentSize().width;

			CCSprite *vipIcon = LayoutData::getSprite(CPModuleName::COMMON, "vipLabel");
			vipIcon->setAnchorPoint(ccp(0, 0.5f));
			vipIcon->setPosition(ccp(-vipIcon->getContentSize().width + ox, nameSize.height/2));
			vipLabelNode->addChild(vipIcon);
		}
	}
}

void HeroAvatar::refreshGuildLabel()
{
	const CCSize &nameSize = m_disName->getContentSize();
	CCLabelTTF *guildNameLabel = dynamic_cast<CCLabelTTF *>(m_disName->getChildByTag(GUILD_NAME_TAG));
	if (guildNameLabel)
	{
		std::string guildName = getExStr(Entity::attr_guild_id);
		if (!guildName.empty())
		{
			guildName = "<" + guildName + ">";
		}
		guildNameLabel->setString(guildName.c_str());
		guildNameLabel->setPosition(ccp(nameSize.width/2, 0));
	}
}

void HeroAvatar::refreshCoupleLabel()
{
	if (!m_disName) return;

	const CCSize &nameSize = m_disName->getContentSize();
	
CCLabelTTF *coupleLabel = dynamic_cast<CCLabelTTF *>(m_disName->getChildByTag(COUPLE_NAME_TAG));
	
if (!coupleLabel) return;

	
std::string coupleTitle;

	
if (mType == GHOST_TYPE_THIS)
	{
	// ??????????????????????????UI?????
	}
	
	else if (mType == GHOST_TYPE_PLAYER)
	
{
		
// ?????????????????????"N:??????,G:???(1??2?0???)"????????????????????????
		
std::string rawData = getExStr(Entity::attr_couple_name_id);
		
if (!rawData.empty())
		
{
			
std::string partnerName;
			
int targetGender = 0;
			
size_t nPos = rawData.find("N:");
			
size_t commaPos = rawData.find(",");
			
size_t gPos = rawData.find("G:");
			
if (nPos != std::string::npos && commaPos != std::string::npos && gPos != std::string::npos)
			
{
				
partnerName = rawData.substr(nPos + 2, commaPos - (nPos + 2));
				
std::string genderStr = rawData.substr(gPos + 2);
				
targetGender = atoi(genderStr.c_str());
			
}
			
if (!partnerName.empty())
			
{
				
if (targetGender == 1)
				
{
					
coupleTitle = LayoutData::getString(CPModuleName::COMMON, "couple_wife") + partnerName;
				
}
				
else if (targetGender == 2)
				
{
					
coupleTitle = LayoutData::getString(CPModuleName::COMMON, "couple_husband") + partnerName;
				
}
				
else
				
{
					
coupleTitle = LayoutData::getString(CPModuleName::COMMON, "couple_partner") + partnerName;
				
}
			
}
		
}
	
}

	
coupleLabel->setAnchorPoint(ccp(0, 0));
	coupleLabel->setColor(ccc3(255, 192, 203));
	coupleLabel->setString(coupleTitle.c_str());
	
float labelH = coupleLabel->getContentSize().height;

coupleLabel->setZOrder(1);
	coupleLabel->setPosition(ccp(-58, nameSize.height));//????????
}
void HeroAvatar::refreshHeadName()
{
	if (!m_disName || !mHeadNameContainer)
	{
		return;
	}

	mHeadNameContainer->removeAllChildren();

	const int x = m_disName->getContentSize().width/2;
	int y = m_disName->getContentSize().height;
	CCLabelTTF *headCoupleLabel = dynamic_cast<CCLabelTTF *>(m_disName->getChildByTag(COUPLE_NAME_TAG));
	if (headCoupleLabel && strlen(headCoupleLabel->getString()) > 0) { y += headCoupleLabel->getContentSize().height; }

	// normal head name
	const IDVector &headNames = HeroData::getHeadNames(getExData(Entity::attr_open_headtitle));
	int picFlag = 0;
	std::string headStr;
	for (int i = headNames.size() - 1; i >= 0; i--)
	{
		CCNode *headNode = NULL;
		EffectSprite *dynamicEffectHead = NULL;
		
		headStr.clear();
		StaticData::getHeadNamesData(headNames[i], "ispicture", picFlag);
		StaticData::getHeadNamesShowTitle(headNames[i], mGhostJob, mGhostGender, headStr);
		
		if (picFlag == 1)  
		{  
			headNode = LayoutData::getSpriteByFrameName(headStr);
		}  
		else if (picFlag >= 2)  
		{  
			dynamicEffectHead = EffectSprite::create(picFlag, -1);  
		}  
		else  
		{  
			CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::COMMON, "headNames");
			label->setString(headStr.c_str());
			headNode = label; 
		}
		
		if (headNode != NULL)
		{
			headNode->setAnchorPoint(ccp(0.5f, 0));
			headNode->setPosition(ccp(x, y));
			mHeadNameContainer->addChild(headNode);
			y += headNode->getContentSize().height;
		}
		
		if (dynamicEffectHead != NULL)
		{
			dynamicEffectHead->setAnchorPoint(ccp(0.5f, 0));
			dynamicEffectHead->setPosition(ccp(x, y));
			mHeadNameContainer->addChild(dynamicEffectHead);
			y += dynamicEffectHead->getContentSize().height;
		}
	
	}
}
