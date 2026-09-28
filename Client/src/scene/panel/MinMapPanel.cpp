#include "MinMapPanel.h"
#include "MapModule.h"
#include "MsgScene.h"
#include "SceneDefinition.h"
#include "scene/MapHelper.h"
#include "scene/SceneHelper.h"
#include "ErrorDefinition.h"

#include "ext/CCMenuEx.h"

#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"

#include "element/AnimElement.h"
#include "element/ElementDefinition.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/SystemData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/mapdata/PixesMap.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/luadata/MinimapLua.h"
#include "scene/SceneManager.h"
#include "scene/Login.h"
#include "event/CPEventHelper.h"
#include "module/LoginModule.h"

//////////MiniMapPanel///////////////////////////////////////////////////
MiniMapPanel::MiniMapPanel()
:mCurrentMapLayer(NULL)
,mWorldMapLayer(NULL)
,mMapSwitch(NULL)
,mCurrentNPCList(NULL)
,mCurrentMapContainer(NULL)
,mMySign(NULL)
,mCurrentMapID(0)
,m_fMapWidth(0)
,m_fMapHeight(0)
,m_fMiniTileWidth(0)
,m_fMiniTileHeight(0)
{

}

bool MiniMapPanel::init()
{
	if (!FullScreenPanel::init())
	{
		return false;
	}

	mMapShow = LayoutData::getSize(CPModuleName::MAP, "mapShow");
	mLeftTop = LayoutData::getPoint(CPModuleName::MAP, "mapShowLeftTop");
	mCurrentMapID = GameData::s_user->mMap.mID;
	MiniMapLua::getMapList();

	initUI();
	showCurrentMap();
	refreshCurrentMap();

	return true;
}

void MiniMapPanel::onEnter()
{
	FullScreenPanel::onEnter();
	schedule(schedule_selector(MiniMapPanel::refreshMySign), 0.5f);
}

void MiniMapPanel::onExit()
{
	unschedule(schedule_selector(MiniMapPanel::refreshMySign));
	FullScreenPanel::onExit();
}

void MiniMapPanel::initUI()//地图界面ui
{
	// 设置整个面板的位置
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	
	// 设置面板的锚点为左下角，方便定位
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));
	
	// 所有子元素的位置都相对于面板位置
	CCScale9Sprite* pBorder=SystemData::getScale9SpriteByPlist("taskcontent_bigborder",795,SystemData::getLayoutValue("taskcontent_bigborder.h"));
	pBorder->setAnchorPoint(CCPointZero);
	pBorder->setPosition(ccp(SystemData::getLayoutPoint("taskcontent_bigborder").x-2, 
							SystemData::getLayoutPoint("taskcontent_bigborder").y));
	addChild(pBorder);

	CCSprite *title = LayoutData::getSprite(CPModuleName::MAP, "title");
	addChild(title);

	CCScale9Sprite *leftBoard = LayoutData::getScale9Sprite(CPModuleName::MAP, "leftBoard");
	addChild(leftBoard);

	CCScale9Sprite *rightBoard = LayoutData::getScale9Sprite(CPModuleName::MAP, "rightBoard");
	addChild(rightBoard);

	const CCSize &switchSize = LayoutData::getSize(CPModuleName::MAP, "mapSwitch");
	mMapSwitch = CPItemComponents::create(switchSize, new CPLayoutList(CCSizeZero, false));
	mMapSwitch->setPosition(LayoutData::getPoint(CPModuleName::MAP, "mapSwitch"));
	addChild(mMapSwitch);

	CCMenuItemImage *currentBtn = LayoutData::getMenuItemImg(CPModuleName::MAP, "currentMap");
	currentBtn->setTarget(this, menu_selector(MiniMapPanel::onCurrentMap));
	mMapSwitch->addItem(currentBtn);

	CCMenuItemImage *worldBtn = LayoutData::getMenuItemImg(CPModuleName::MAP, "worldMap");
	worldBtn->setTarget(this, menu_selector(MiniMapPanel::onWorldMap));
	mMapSwitch->addItem(worldBtn);
	
	
}

void MiniMapPanel::showCurrentMap()
{
	mMapSwitch->setCurrentIndex(0);
	if (mWorldMapLayer)
	{
		mWorldMapLayer->setVisible(false);
	}

	if (mCurrentMapLayer)
	{
		mCurrentMapLayer->setVisible(true);
		return;
	}

	mCurrentMapLayer = CCLayer::create();
	addChild(mCurrentMapLayer);

	// map container
	mCurrentMapContainer = CCLayer::create();
	mCurrentMapLayer->addChild(mCurrentMapContainer);

	// list title
	CCMenuItemImage *titleButton = LayoutData::getMenuItemLabelImage(CPModuleName::MAP, "npcList");
	titleButton->setEnabled(false);
	mCurrentMapLayer->addChild(titleButton);

	// npc list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::MAP, "list");
	mCurrentNPCList = CPItemComponents::create(listSize, new CPLayoutList(CCSizeMake(176,45),true));
	mCurrentNPCList->setClickSensitive(true);
	mCurrentNPCList->setPosition(LayoutData::getPoint(CPModuleName::MAP, "list"));
	mCurrentMapLayer->addChild(mCurrentNPCList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::MAP, "listScrollBar");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mCurrentNPCList->setScrollbar(scrollBar);
}

void MiniMapPanel::showWorldMap()//世界地图背景界面
{
	if (mCurrentMapLayer)
	{
		mCurrentMapLayer->setVisible(false);
	}

	if (mWorldMapLayer)
	{
		mWorldMapLayer->setVisible(true);
		return;
	}

	mWorldMapLayer = CCLayer::create();
	addChild(mWorldMapLayer);

	// bkg
	CCSprite *bkg = LayoutData::getSpriteByFile(CPModuleName::MAP, "worldMap");
	const float factorX = mMapShow.width/bkg->getContentSize().width;
	const float factorY = mMapShow.height/bkg->getContentSize().height;
	const float factor = min(factorX, factorY);
	bkg->setAnchorPoint(ccp(0, 1));
	bkg->setPosition(mLeftTop);
	bkg->setScale(factor);
	mWorldMapLayer->addChild(bkg);

	// icons 
	MiniMapLua::getMapIconList();
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	mWorldMapLayer->addChild(menu);
	for (unsigned int i = 0; i < MiniMapLua::mapIconList.size(); i++)
	{
		const MiniMapIcon& icondata = MiniMapLua::mapIconList[i];
		CCSprite *norm = LayoutData::getSpriteByFrameName(icondata.m_strImage + ".png");
		CCSprite *sel = LayoutData::getSpriteByFrameName(icondata.m_strImage + "_sel.png");
		CCMenuItemSprite *icon = CCMenuItemSprite::create(norm, sel);
		icon->setTarget(this, menu_selector(MiniMapPanel::onWorldMapIcon));
		icon->setPosition(ccp(icondata.m_nPosX, icondata.m_nPosY));
		menu->addChild(icon, 0, icondata.m_nID);

		if (icondata.m_nID == GameData::getCurrentMap()->mID)
		{
			GameRole *myRole = GameData::getMyRole();
			AnimElement *myAnim = AnimElement::create(0, CPElement::Type::player, HeroData::getGender());
			myAnim->setCloth(myRole->getDress(AVATAR_TYPE_CLOTH));
			myAnim->setWeapon(myRole->getDress(AVATAR_TYPE_WEAPON));
			myAnim->setWings(myRole->getDress(AVATAR_TYPE_WINGS));
			myAnim->setPosition(icon->getPosition());
			myAnim->setScale(LayoutData::getFloat(CPModuleName::MAP, "myAnimScale"));
			mWorldMapLayer->addChild(myAnim);
		}
	}

	// list title
	CCMenuItemImage *titleButton = LayoutData::getMenuItemLabelImage(CPModuleName::MAP, "mapList");
	titleButton->setEnabled(false);
	mWorldMapLayer->addChild(titleButton);

	// map list
	const CCSize &listSize = LayoutData::getSize(CPModuleName::MAP, "list");
	CPItemComponents *mapList = CPItemComponents::create(listSize, new CPLayoutList(CCSizeMake(176,45),true));
	mapList->setClickSensitive(true);
	mapList->setPosition(LayoutData::getPoint(CPModuleName::MAP, "list"));
	mWorldMapLayer->addChild(mapList);

	const CCSize &barSize = LayoutData::getSize(CPModuleName::MAP, "listScrollBar");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mapList->setScrollbar(scrollBar);

	for (int i = 0; i < (int)MiniMapLua::mapList.size(); i++)
	{
		const int mapID = MiniMapLua::mapList[i].m_nID;
		int hideFlag = 0;
		StaticData::getMapHideInWorldMapFlag(mapID, hideFlag);
		if (hideFlag != 0)
		{
			continue;
		}

		CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::MAP, "listItem");
		item->setTarget(this, menu_selector(MiniMapPanel::onWorldMapIcon));
		mapList->addItem(item);
		item->setTag(mapID);

		CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::MAP, "listItemName");
		label->setHorizontalAlignment(kCCTextAlignmentLeft);
		label->setAnchorPoint(ccp(0,0.5));
		label->setPosition(ccp(5,item->getContentSize().height/2));
		label->setString(MiniMapLua::mapList[i].m_strName.c_str());
		item->addChild(label);

		if (mapID != GameData::getCurrentMap()->mID)
		{
			// teleport btn
			CCMenu *menu = CCMenu::create();
			menu->setPosition(CCPointZero);
			item->addChild(menu);

			CCMenuItemImage *teleportBtn = LayoutData::getMenuItemImg(CPModuleName::MAP, "npcTeleport");
			teleportBtn->setTarget(this, menu_selector(MiniMapPanel::onWorldTeleport));
			teleportBtn->setPosition(item->getContentSize().width - 30, item->getContentSize().height/2);
			teleportBtn->setScale(0.8f);
			menu->addChild(teleportBtn, 0, mapID);
		}
	}
}

void MiniMapPanel::refreshCurrentMap()
{	
	// bkg
	mCurrentMapContainer->removeAllChildrenWithCleanup(true);
	mMySign = NULL;

	char mapPath[64];
	for (int i = 0; i < (int)MiniMapLua::mapList.size(); i++)
	{
		if (MiniMapLua::mapList[i].m_nID == mCurrentMapID)
		{
			sprintf(mapPath, "data-a/minimap/mini_%s.jpg", MiniMapLua::mapList[i].m_strImage.c_str());
			break;
		}
	}
	CCSprite *bkg = CCSprite::create(mapPath);
	if (bkg==NULL)
	{
		return;
	}
	const float factorX = mMapShow.width/bkg->getContentSize().width;
	const float factorY = mMapShow.height/bkg->getContentSize().height;
	const float factor = min(factorX, factorY);
	bkg->setAnchorPoint(ccp(0, 1));
	bkg->setPosition(mLeftTop);
	bkg->setScale(factor);
	mCurrentMapContainer->addChild(bkg);

	m_fMapWidth = bkg->getContentSize().width * factor;
	m_fMapHeight = bkg->getContentSize().height * factor;

	m_fMiniTileHeight = m_fMapHeight/GameData::s_user->m_pPixesMap->mLogicHeight;
	m_fMiniTileWidth = m_fMapWidth/GameData::s_user->m_pPixesMap->mLogicWidth;

	MiniMapLua::getNPCList(mCurrentMapID);
	if(mCurrentMapID == GameData::s_user->mMap.mID)
	{
		buildPortalSign();
		buildEntitySign();
		buildMySign();
	}

	// npc list
	mCurrentNPCList->removeAllItems();
	for (int i = 0; i < (int)MiniMapLua::npcList.size(); i++)
	{
		const int npcID = MiniMapLua::npcList[i].m_nID;
		int hideFlag = 0;
		StaticData::getNPCHideInWorldMapFlag(npcID, hideFlag);
		if (hideFlag != 0)
		{
			continue;
		}

		CCMenuItemImage *item = LayoutData::getMenuItemImg(CPModuleName::MAP, "listItem");
		item->setTarget(this, menu_selector(MiniMapPanel::onNPC));
		mCurrentNPCList->addItem(item);
		item->setTag(npcID);

		CCLabelTTF *label = LayoutData::getLabelTTF(CPModuleName::MAP, "listItemName");
		label->setHorizontalAlignment(kCCTextAlignmentLeft);
		label->setAnchorPoint(ccp(0,0.5));
		label->setPosition(ccp(5, item->getContentSize().height/2));
		label->setString(MiniMapLua::npcList[i].m_strName.c_str());
		item->addChild(label);

		// teleport btn
		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		item->addChild(menu);

		CCMenuItemImage *teleportBtn = LayoutData::getMenuItemImg(CPModuleName::MAP, "npcTeleport");
		teleportBtn->setTarget(this, menu_selector(MiniMapPanel::onNPCTeleport));
		teleportBtn->setPosition(item->getContentSize().width - 30, item->getContentSize().height/2);
		teleportBtn->setScale(0.8f);
		menu->addChild(teleportBtn, 0, npcID);
	}

	//
	if(mCurrentMapID != GameData::s_user->mMap.mID)
	{
		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		mCurrentMapContainer->addChild(menu);

		CCMenuItemImage *telepotBtn = LayoutData::getMenuItemImg(CPModuleName::MAP, "mapTeleport");
		telepotBtn->setTarget(this, menu_selector(MiniMapPanel::onWorldTeleport));
		menu->addChild(telepotBtn, 0, mCurrentMapID);
	}
}

void MiniMapPanel::refreshMySign( float dt )
{
	if (mMySign)
	{
		GameRole *myRole = GameData::s_user->m_pMainRole;
		mMySign->setPosition(getLocalPt(ccp(myRole->mTx, myRole->mTy)));
	}
}

void MiniMapPanel::buildPortalSign()
{
	const ccColor3B &portalColor = LayoutData::getColor3(CPModuleName::COMMON, "white");
	MapConnsMap::iterator mIt = GameData::s_map->mMiniMapConn.find(mCurrentMapID);
	if (mIt != GameData::s_map->mMiniMapConn.end())
	{
		const MapConnVect &portalVect = mIt->second;
		for (int i = 0; i < (int)portalVect.size(); i++)
		{
			const NetMapConn *portalData = portalVect[i];
			CCNode *portalNode = MapHelper::getSignNode(MapSignType::portal);
			portalNode->setPosition(getLocalPt(ccp(portalData->mFromX, portalData->mFromY)));
			mCurrentMapContainer->addChild(portalNode);

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

void MiniMapPanel::buildEntitySign()
{
	// npc
	for (int i=0; i < (int)MiniMapLua::npcList.size(); i++)
	{
		const MiniMapNPC &npc = MiniMapLua::npcList[i];
		CCNode *npcNode = MapHelper::getSignNode(MapSignType::npc);
		npcNode->setScale(0.5f);
		npcNode->setPosition(getLocalPt(ccp(npc.m_nPosX, npc.m_nPosY)));
		mCurrentMapContainer->addChild(npcNode);
	}

	// boss
	int mapType = 0;
	StaticData::getMapType(mCurrentMapID, mapType);
	if (mapType == Scene::stSceneNormal)
	{
		int monsterCnt = 0;
		StaticData::getMapMonsterCount(mCurrentMapID, monsterCnt);
		int monsterID = 0, posX = 0, posY = 0;
		for (int i = 0; i < monsterCnt; i++)
		{
			monsterID = 0;
			StaticData::getMapMonsterData(mCurrentMapID, i + 1, monsterID, posX, posY);
			buildBossSign(monsterID, posX, posY);
		}

		monsterCnt = 0;
		StaticData::getMapEventMonsterCount(mCurrentMapID, monsterCnt);
		for (int i = 0; i < monsterCnt; i++)
		{
			monsterID = 0;
			StaticData::getMapEventMonsterData(mCurrentMapID, i + 1, monsterID, posX, posY);
			buildBossSign(monsterID, posX, posY);
		}
	}

	// target pos
	GameRole* myRole = GameData::getMyRole();
	if (myRole && myRole->m_bAutoMove)
	{
		CCNode *activeSign = MapHelper::getSignNode(MapSignType::target_pos);
		activeSign->setPosition(getLocalPt(myRole->getTargetPosition()));
		mCurrentMapContainer->addChild(activeSign);
	}	
}

void MiniMapPanel::buildBossSign( int monsterID, int posX, int posY )
{
	if (monsterID > 0)
	{
		int bossFlag = 0;
		StaticData::getMonsterBossFlag(monsterID, bossFlag);
		if (bossFlag != 0)
		{
			const float scale = 0.4f;
			CCNode *bossNode = MapHelper::getSignNode(MapSignType::boss);
			bossNode->setScale(scale);
			bossNode->setPosition(getLocalPt(ccp(posX, posY)));
			mCurrentMapContainer->addChild(bossNode);

			std::string bossName;
			StaticData::getMonsterName(monsterID, bossName);
			CCLabelTTF *nameLabel = LayoutData::getLabelTTF(CPModuleName::MAP, "bossName");
			nameLabel->setString(bossName.c_str());
			nameLabel->setPositionX(bossNode->getPositionX());
			nameLabel->setPositionY(bossNode->getPositionY() + bossNode->getContentSize().height * scale/2);
			mCurrentMapContainer->addChild(nameLabel);
		}
	}
}

void MiniMapPanel::buildMySign()
{
	GameRole *myRole = GameData::s_user->m_pMainRole;
	mMySign = MapHelper::getSignNode(MapSignType::me);
	mMySign->setScale(0.5f);
	mMySign->setPosition(getLocalPt(ccp(myRole->mTx, myRole->mTy)));
	mCurrentMapContainer->addChild(mMySign);
}

void MiniMapPanel::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	if (mCurrentMapLayer->isVisible() &&
		mCurrentMapID == GameData::s_user->mMap.mID)
	{
		CCPoint touchLocation = convertTouchToNodeSpace(touch);
		if(isInMap(touchLocation))
		{
			int tx = (touchLocation.x - mLeftTop.x)/m_fMiniTileWidth;
			int ty = (mLeftTop.y - touchLocation.y)/m_fMiniTileHeight;
			moveTo(ccp(tx, ty));
		}
	}
}

void MiniMapPanel::onCurrentMap( CCObject *target )
{
	showCurrentMap();
}

void MiniMapPanel::onWorldMap( CCObject *target )
{
	showWorldMap();
}

void MiniMapPanel::onNPC( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode*>(target);
	if(node)
	{
		SceneHelper::autoMoveToNPC(node->getTag());
		close();
	}
}

void MiniMapPanel::onWorldMapIcon( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if(node)
	{
		
		mCurrentMapID = node->getTag();
		
		showCurrentMap();
		refreshCurrentMap();
		
	}
}

void MiniMapPanel::onWorldTeleport( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if(node)
	{
		SceneHelper::teleportToMapRequest(node->getTag());
		close();
	}
}

void MiniMapPanel::onNPCTeleport( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		SceneHelper::teleportToNPCRequest(pNode->getTag());
		close();
	}
}

bool MiniMapPanel::isInMap( const CCPoint &pos )
{
	if (pos.x >= mLeftTop.x &&
		pos.y <= mLeftTop.y &&
		pos.x < mLeftTop.x + m_fMapWidth &&
		pos.y > mLeftTop.y - m_fMapHeight)
	{
		return true;
	}
	return false;	
}

void MiniMapPanel::moveTo( const CCPoint &pos )
{
	if(!GameData::s_user->m_pMainRole->isBlocked(pos.x, pos.y))
	{
		GameData::s_user->m_pMainRole->startAutoMoveTo(pos.x, pos.y);
		close();
	}
}

CCPoint MiniMapPanel::getLocalPt( const CCPoint &pt )
{
	CCPoint ret = CCPointZero;
	ret.x = mLeftTop.x + m_fMiniTileWidth * pt.x + m_fMiniTileWidth/2;
	ret.y = mLeftTop.y - m_fMiniTileHeight * pt.y + m_fMiniTileHeight/2;
	return ret;
}

void MiniMapPanel::onCPEvent( const std::string &eventName )
{
	//
}
