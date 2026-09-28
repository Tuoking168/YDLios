#include "MiniMapLayer.h"
#include "cocos2d.h"
#include "MapModule.h"
#include "MapHelper.h"

#include "controls/CPNodeHelper.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "userdata/UserData.h"
#include "userdata/GameData.h"
#include "userdata/LayoutData.h"
#include "userdata/mapdata/PixesMap.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/GhostManager.h"

#include "utils/StringUtils.h"


/////////MiniMapLayer//////////////////////////////////////////////////
MiniMapLayer::MiniMapLayer()
	: m_pHeroFlag(NULL)
	, m_pMiniMapLayer(NULL)
	, mCoordinateLabel(NULL)
	, m_pNodeContainer(NULL)
	, mPortalContainer(NULL)
	, mEntityContainer(NULL)
	, mOpenBtn(NULL)
	, mCloseBtn(NULL)
	, mNameLabel(NULL)
	, m_fMiniTileWidth(0)
	, m_fMiniTileHeight(1.0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

MiniMapLayer::~MiniMapLayer()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

// on "init" you need to initialize your instance
bool MiniMapLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);

	initUI();
	refreshMap();

	return true;
}

void MiniMapLayer::onEnter()
{
	CCLayer::onEnter();
	
	update(0);
	schedule(schedule_selector(MiniMapLayer::update), 1.0f);
}

void MiniMapLayer::initUI()
{
	// container
	const CCSize &winSize = CCDirector::sharedDirector()->getWinSize();
	m_pNodeContainer = CCNode::create();
	m_pNodeContainer->setContentSize(winSize);
	m_pNodeContainer->setAnchorPoint(ccp(1, 1));
	m_pNodeContainer->setPosition(ccp(winSize.width, winSize.height));
	addChild(m_pNodeContainer);

	// map
	const CCSize &miniMapSize = LayoutData::getSize(CPModuleName::MAP, "miniMap");
	CCClippingNode *clippingNode = CPNodeHelper::getClippingNode(miniMapSize);
	clippingNode->setPosition(LayoutData::getPoint(CPModuleName::MAP, "miniMap"));
	m_pNodeContainer->addChild(clippingNode);

	m_pMiniMapLayer = CCLayer::create();
	clippingNode->addChild(m_pMiniMapLayer);

	m_pMap = CCSprite::create();
	m_pMap->setAnchorPoint(CCPointZero);
	m_pMap->setPosition(CCPointZero);
	m_pMiniMapLayer->addChild(m_pMap);

	// sign
	mPortalContainer = CCNode::create();
	m_pMap->addChild(mPortalContainer);

	mEntityContainer = CCNode::create();
	m_pMap->addChild(mEntityContainer);

	m_pHeroFlag = MapHelper::getSignNode(MapSignType::me);
	m_pHeroFlag->setScale(0.5f);
	m_pMap->addChild(m_pHeroFlag);

	// border
	CCSprite *border = LayoutData::getSprite(CPModuleName::MAP, "miniMapBorder");
	m_pNodeContainer->addChild(border);

	mCoordinateLabel = LayoutData::getLabelTTF(CPModuleName::MAP, "miniMapCoordinate");
	m_pNodeContainer->addChild(mCoordinateLabel);

	mNameLabel = LayoutData::getLabelTTF(CPModuleName::MAP, "miniMapName");
	m_pNodeContainer->addChild(mNameLabel);

	// open and close menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItemImage *closeBtn = LayoutData::getMenuItemImg(CPModuleName::MAP, "closeMiniMap");
	closeBtn->setTarget(this, menu_selector(MiniMapLayer::onClose));
	menu->addChild(closeBtn);
	mCloseBtn = closeBtn;

	CCMenuItemImage *openBtn = LayoutData::getMenuItemImg(CPModuleName::MAP, "openMiniMap");
	openBtn->setTarget(this, menu_selector(MiniMapLayer::onOpen));
	openBtn->setVisible(false);
	menu->addChild(openBtn);
	mOpenBtn = openBtn;
}

void MiniMapLayer::buildPortalSign()
{
	mPortalContainer->removeAllChildren();
	ccColor3B portalColor = LayoutData::getColor3(CPModuleName::COMMON, "white");
	MapConnsMap::iterator mIt = GameData::s_map->mMiniMapConn.find(GameData::s_user->mMap.mID);
	if (mIt != GameData::s_map->mMiniMapConn.end())
	{
		MapConnVect portalVect = mIt->second;
		for (int i = 0; i < (int)portalVect.size(); i++)
		{
			const NetMapConn *portalData = portalVect[i];
			CCNode *portalNode = MapHelper::getSignNode(MapSignType::portal);
			portalNode->setScale(0.5f);
			portalNode->setPosition(getLocalPt(ccp(portalData->mFromX, portalData->mFromY)));
			mPortalContainer->addChild(portalNode);

			// name label
			CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::MAP, "portalName");
			nameLabel->setString(portalData->mDesMapName.c_str());
			nameLabel->setColor(portalColor);
			nameLabel->setPositionX(portalNode->getContentSize().width/2);
			nameLabel->setPositionY(portalNode->getContentSize().height);
			portalNode->addChild(nameLabel);
		}
	}
}

void MiniMapLayer::refreshMap()
{
	mNameLabel->setString(GameData::getCurrentMap()->mName.c_str());

	//
	const std::string &mapPath = LayoutData::getString(CPModuleName::MAP, "mimiMapPathHead") + GameData::getCurrentMap()->mMapFile + ".jpg";
	CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(mapPath.c_str());
	if (!pTexture)
	{
		pTexture = CCTextureCache::sharedTextureCache()->addImage(LayoutData::getString(CPModuleName::MAP, "mimiMapPathDefault").c_str());
	}
	m_pMap->setTexture(pTexture);

	const CCSize &size = pTexture->getContentSize();
	m_pMap->setTextureRect(CCRectMake(0, 0, size.width, size.height));
	m_fMiniTileWidth = size.width/GameData::getPixesMap()->mLogicWidth;
	m_fMiniTileHeight = size.height/GameData::getPixesMap()->mLogicHeight;

	//
	buildPortalSign();
}

void MiniMapLayer::update( float dt )
{
	refreshMapPosition();
	refreshMySign();
	refreshEntitySign();
}

void MiniMapLayer::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool MiniMapLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	if (!pTouch)
	{
		return false;
	}

	if(m_pNodeContainer->getScale() == 1)
	{
		const CCPoint &ptLeftCorner = LayoutData::getPoint(CPModuleName::MAP, "miniMap");
		const CCPoint &pos = pTouch->getLocation();
		if (pos.x >= ptLeftCorner.x &&
			pos.y >= ptLeftCorner.y)
		{
#define QI_SHI_SAI_MA_CHANG 270
#define ZHONG_DIAN_SAI_MA_CHANG 271
			const int mid = GameData::s_user->mMap.mID;
			if (mid != QI_SHI_SAI_MA_CHANG && mid != ZHONG_DIAN_SAI_MA_CHANG)
			{
				CPEventHelper::openPanel("MiniMapPanel");
			}
			return true;
		}
	}
	return false;
}

void MiniMapLayer::refreshMapPosition()
{
	// info
	char strMapinfo[100];
	sprintf(strMapinfo,"%d,%d", GameData::s_user->m_pMainRole->mTx, GameData::s_user->m_pMainRole->mTy);
	mCoordinateLabel->setString(strMapinfo);

	// pos
	const CCSize &miniSize = LayoutData::getSize(CPModuleName::MAP, "miniMap");
	CCPoint pos = m_pHeroFlag->getPosition();
	pos = ccpAdd(ccpNeg(pos), ccp(miniSize.width/2, miniSize.height/2));
	pos.x = min(pos.x, 0.0f);
	pos.y = min(pos.y, 0.0f);
	pos.x = max(pos.x, miniSize.width - m_pMap->getContentSize().width);
	pos.y = max(pos.y, miniSize.height - m_pMap->getContentSize().height);
	m_pMap->setPosition(pos);
}

void MiniMapLayer::refreshMySign()
{
	if(m_pHeroFlag)
	{
		GameRole* pHero = GameData::s_user->m_pMainRole;
		if(!pHero || !GameData::s_user->m_pPixesMap)
		{
			return;
		}
		m_pHeroFlag->setPosition(getLocalPt(ccp(pHero->mTx,pHero->mTy)));
	}
}

void MiniMapLayer::refreshEntitySign()
{
	mEntityContainer->removeAllChildrenWithCleanup(true);

	GhostManager *gMnger = GameData::s_user->m_pGhostManager;
	GhostManager::GhostList ghostVect = gMnger->m_pGhosts;
	for (int i = 0; i < (int)ghostVect.size(); i++)
	{
		CCNode *signNode = NULL;
		const Ghost *ghost = ghostVect[i];
		switch (ghost->mType)
		{
		case GHOST_TYPE_NPC:
			{
				signNode = MapHelper::getSignNode(MapSignType::npc);
				break;
			}
		case GHOST_TYPE_MONSTER:
			{
				signNode = MapHelper::getSignNode(MapSignType::monster);
				break;
			}
		case GHOST_TYPE_SLAVE:
			{
				signNode = MapHelper::getSignNode(MapSignType::pet);
				break;
			}
		}

		if (signNode)
		{
			signNode->setScale(0.5f);
			signNode->setPosition(getLocalPt(ccp(ghost->mTx, ghost->mTy)));
			mEntityContainer->addChild(signNode);
		}
	}
}

void MiniMapLayer::onOpen( CCObject *target )
{
	mOpenBtn->setVisible(false);
	mCloseBtn->setVisible(true);
	m_pNodeContainer->stopAllActions();
	m_pNodeContainer->runAction(CPNodeHelper::getScaleToBig());
	CPEventHelper::dispatcher(CPEventName::UI_OPEN, "MiniMapLayer", "");
}

void MiniMapLayer::onClose( CCObject *target )
{
	mCloseBtn->setVisible(false);
	mOpenBtn->setVisible(true);
	m_pNodeContainer->stopAllActions();
	m_pNodeContainer->runAction(CPNodeHelper::getScaleToSmall());
	CPEventHelper::dispatcher(CPEventName::UI_CLOSE, "MiniMapLayer", "");
}

cocos2d::CCPoint MiniMapLayer::getLocalPt( const cocos2d::CCPoint &pt )
{
	CCPoint ret = CCPointZero;
	ret.x = m_fMiniTileWidth * pt.x + m_fMiniTileWidth/2;
	ret.y = m_fMiniTileHeight * (GameData::s_user->m_pPixesMap->mLogicHeight - pt.y) + m_fMiniTileHeight/2;
	return ret;
}

void MiniMapLayer::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageMapSelfEnterNotify")
		{
			refreshMap();
		}
	}
}
