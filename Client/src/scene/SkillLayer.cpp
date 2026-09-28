#include "SkillLayer.h"
#include <cmath>
#include <algorithm>
#include "HeroModule.h"
#include "ModuleData.h"
#include "MainUIModule.h"
#include "UserDataModule.h"
#include "CCFlashAnimation.h"
#include "NotificationHelper.h"

#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/netdata/AliveGhost.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/skilldata/SkillEffect.h"
#include "userdata/skilldata/SkillState.h"

#include "event/EventProtocol.h"
#include "event/EventDispatcher.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "network/HandleMessage.h"

#include "MsgItem.h"
#include "MsgPet.h"

#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "logic/ItemOperator.h"

#include "res/AudioLoader.h"

#include "ext/CCActionDestroy.h"

#include "utils/StringUtils.h"

#include "panel/worship/SpiderPanel.h"//调用回收

#define SKILL_ICON_COVER_TAG 10
#define TOUCH_MOVE_DISTANCE 200

const float PI = 3.1415926f;
const float Radius = 200;
const float RotateSpeed = PI*1000;// RotateSpeed angle per second

enum SKILL_LAYER_TAG
{
	TAG_COOLDOWN_BASE = -999,
};

SkillLayer::SkillLayer()
	:mNormalLayer(NULL)
	,mSpecialLayer(NULL)
	,m_pSkillMenu(NULL)
	, m_preAngle(0.0)
	, m_pRotateNode(NULL)
	, m_pUp(NULL)
	, m_pDown(NULL)
	, m_bLockTouch(false)
	,mSkillMenuTouched(false)
	,m_isRotatingPannel(false)
	,m_iselectTime(0)
	,m_iselectTag(0)
	,m_pEasyAttackBtn(NULL)
	,m_bAttackTouch(false)
	,m_bTargetSwiped(false)
	,m_lastSwitchY(0.0f)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::UI_NOTIFY, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}
SkillLayer::~SkillLayer()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::UI_NOTIFY, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
}
void SkillLayer::onEnter()
{
	//注册自己为listener
	EventDispatcher::sharedEventDispather()->addListener(this);
	CCLayer::onEnter();
	updateSkillList();
}

void SkillLayer::onExit()
{
	//取消监听
	EventDispatcher::sharedEventDispather()->removeListener(this);
	CCLayer::onExit();
}

bool SkillLayer::init()
{
	if(!CCLayer::init())	
	{
		return false;
	}
	setTouchEnabled(true);
	
	initUI();
	refreshNormalAndSpecial();
	scheduleUpdate();
	
	return true;
}

void SkillLayer::initUI()
{
	initNormal();
	initSpecial();
	
}

void SkillLayer::initNormal()//技能ui外
{
    mNormalLayer = CCLayer::create();
    addChild(mNormalLayer);
    mNormalLayer->setScale(1.4f);
    mNormalLayer->setPosition(ccp(-SystemData::size_x * 0.2f, SystemData::size_y * 0.19f));

    m_pRotateNode = CCNode::create();
    m_pRotateNode->setPosition(ccp(SystemData::size_x, 0));
    mNormalLayer->addChild(m_pRotateNode);

    m_pSkillMenu = CCMenu::create();
    m_pSkillMenu->setTouchPriority(kCCMenuHandlerPriority + 1);
    m_pSkillMenu->setPosition(CCPointZero);
    m_pRotateNode->addChild(m_pSkillMenu);

    // 根据您提供的位置信息重新设计
    for (int i=0; i<8; ++i)
    {
        CCSprite* sprite = SystemData::getSpriteByPlist("main_ui.skill_bkg");
        
        float x, y;
        
        // 根据您提供的位置设置
        switch (i) {
            case 0:  // 技能1
                x = -40.0f; y = 190.0f;
                break;
            case 1:  // 技能2
                x = -110.0f; y = 190.0f;
                break;
            case 2:  // 技能3
                x = -180.0f; y = 190.0f;
                break;
            case 3:  // 技能4
                x = -115.0f; y = 260.0f;
                break;
            case 4:  // 技能5
                x = -240.0f; y = 120.0f;
                break;
            case 5:  // 技能6
                x = -240.0f; y = 50.0f;
                break;
            case 6:  // 技能7
                x = -160.0f; y = 120.0f;
                break;
            case 7:  // 技能8
                x = -160.0f; y = 50.0f;
                break;
        }
        
        sprite->setPosition(ccp(x, y));
        m_pRotateNode->addChild(sprite);
        
      
    }

     // 添加箭头
    m_pUp = LayoutData::getSprite(CPModuleName::MAIN_UI, "skillArrowUp");
    m_pUp->setVisible(true);  // 确保显示
    mNormalLayer->addChild(m_pUp);

    m_pDown = LayoutData::getSprite(CPModuleName::MAIN_UI, "skillArrowDown");
    m_pDown->setRotation(-90);
    m_pDown->setVisible(true);  // 确保显示
    mNormalLayer->addChild(m_pDown);

    // 添加便捷攻击按钮
    CCSprite* pEasyBkg = SystemData::getSpriteByPlist("main_ui.skill_bkg");
    pEasyBkg->setScale(1.5f);
    mNormalLayer->addChild(pEasyBkg);

    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    pMenu->setTouchPriority(kCCMenuHandlerPriority + 2);
    mNormalLayer->addChild(pMenu);

    CCMenuItemImage* pEasyAttack = SystemData::getMenuItemImageByPlist("main_ui.skill.attack");
    pEasyAttack->setTarget(this, menu_selector(SkillLayer::easyAttackCB));
    pEasyAttack->setScale(1.3f);
    pMenu->addChild(pEasyAttack);
    m_pEasyAttackBtn = pEasyAttack;
    pEasyBkg->setPosition(pEasyAttack->getPosition());

    // 宠物出战
    CCMenuItemImage* petfight = SystemData::getMenuItemImageByPlist("main_ui.skill.petfight");
    petfight->setTarget(this, menu_selector(SkillLayer::selectBattlePet));
    pMenu->addChild(petfight);
    petfight->setPosition(ccp(902,85));
    petfight->setScale(0.7f);

    // 上下马
    CCMenuItemImage* horsefight = SystemData::getMenuItemImageByPlist("main_ui.skill.horse");
    horsefight->setTarget(this, menu_selector(SkillLayer::selectMountHorse));
    pMenu->addChild(horsefight);
    horsefight->setPosition(ccp(902,35));
    horsefight->setScale(0.85f);

    // 装备回收
    CCMenuItemImage* newButton = SystemData::getMenuItemImageByPlist("main_ui.skill.spider");
    newButton->setTarget(this, menu_selector(SkillLayer::newButtonCallback));
    pMenu->addChild(newButton);
    newButton->setPosition(ccp(946, 420));
    newButton->setScale(0.63f);
}
void SkillLayer::newButtonCallback(CCObject* pSender)
{
    // 方式1：直接创建
    SpiderPanel* spiderPanel = SpiderPanel::create();
    
    if (spiderPanel) {
        CCDirector* director = CCDirector::sharedDirector();
        CCScene* scene = director->getRunningScene();
        
        if (scene) {
            // 确保面板没有被重复添加
            if (scene->getChildByTag(SPIDER_PANEL_TAG)) {
                return; // 面板已存在，不再重复创建
            }
            
            spiderPanel->setTag(SPIDER_PANEL_TAG);
            scene->addChild(spiderPanel, 1000);
        }
    }
}




void SkillLayer::initSpecial()
{
	mSpecialLayer = CCLayer::create();
	addChild(mSpecialLayer);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	mSpecialLayer->addChild(menu);

	const int cnt = LayoutData::getInt(CPModuleName::MAIN_UI, "saiMaChangSkillCnt");
	int firstSkill = 0;
	StaticData::getSaiMaChangFirstSkill(firstSkill);
	for (int i = 0; i < cnt; i++)
	{
		const std::string &iconName = "saiMaChangSkill" + StringUtils::toString(i);
		CCMenuItemImage *btn = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, iconName);
		btn->setTarget(this, menu_selector(SkillLayer::onSpecialSkill));
		menu->addChild(btn, 0, firstSkill + i);
	}
}

void SkillLayer::refreshNormalAndSpecial()
{
	int saiMaChangFlag = 0;
	StaticData::getMapSaiMaChangFlag(GameData::getCurrentMap()->mID, saiMaChangFlag);
	mNormalLayer->setVisible(saiMaChangFlag == 0);
	mSpecialLayer->setVisible(saiMaChangFlag != 0);
}

void SkillLayer::handleEvent( int channel )
{
	//处理skillchange的event
	if(channel == EventProtocol::EVENT_NET_SKILL_CHANGE)
	{
		updateSkillList();
	}
	if (channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		updateItem();
	}
}

void SkillLayer::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if(eventName == CPEventName::UI_NOTIFY)
	{
		if (source == "UINotifyPlayerUseSkill")
		{
			const int skillID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			showCoolDown(skillID);
			const int typeEnum = skillID/10;
			if (typeEnum == SKILL_TYPE_HuoQiang)
			{
				CCNode *btn = m_pSkillMenu->getChildByTag(skillID);
				if (btn)
				{
					refreshSkillOnOff(skillID, btn, false);
				}
			}
			else if (typeEnum == SKILL_TYPE_LieYanChongSheng)
			{
				int skillLieHuo = 0;
				if (GameData::getMyRole()->isSkillLearned(SKILL_TYPE_LieHuoJianFa * 10 + 1, skillLieHuo))
				{
					//showCoolDown(skillLieHuo, true);
				}
			}
		}
	}
	else if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			updateSelecttime(1);
		}
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageMapSelfEnterNotify")
		{
			refreshNormalAndSpecial();
		}
	}
}

float SkillLayer::getCoolDown(int skillid)
{
	float cooldown = HeroData::getSkillCD(skillid);
	if (cooldown > FLT_EPSILON)
	{
		return cooldown;
	}
	
	std::string strKey = "cooldown";
	if(LuaData::getProp(LuaData::SKILL, skillid, strKey, cooldown))				
	{
		if (cooldown > FLT_EPSILON)
		{
			return cooldown / 1000;
		}
	}

	int time = 0;
	StaticData::getGlobalData("playerattackinterval", time);
	cooldown = time/1000.0f;
	return cooldown;
}

void SkillLayer::showCoolDown(int skillID)
{
	showCoolDown(skillID, false);
}

void SkillLayer::showCoolDown( int skillID, bool isClear )
{
	if (m_pSkillMenu)
	{
		CCArray *children = m_pSkillMenu->getChildren();
		if ( children && children->count() > 0 )
		{
			CCObject* child = NULL;
			CCARRAY_FOREACH(children, child)
			{
				CCNode* pNode = dynamic_cast<CCNode *>(child);
				if (pNode)
				{
					CCProgressTimer *progressCD = (CCProgressTimer *)pNode->getChildByTag(TAG_COOLDOWN_BASE + skillID);
					if (progressCD)
					{
						progressCD->stopAllActions();
						const float cooldown = (isClear ? 0 : getCoolDown(skillID));
						CCProgressFromTo *progressToAction = CCProgressFromTo::create(cooldown, 100.0f, 0.0f);
						progressCD->runAction(progressToAction);
					}
				}
			}
		}
	}
}

void SkillLayer::useSkillCallback( CCObject* pSender )
{
	if (m_isRotatingPannel)	return;

	CCNode* pNode = dynamic_cast<CCNode *>(pSender);
	if (!pNode)
	{
		return;
	}

	GameRole* pHero = GameData::s_user->m_pMainRole;
	const int tag = pNode->getTag();
	const int typeEnum = tag/10;
	if (typeEnum == SKILL_TYPE_BanYueWanDao ||
		typeEnum == SKILL_TYPE_CiShaJianShu ||
		typeEnum == SKILL_TYPE_LieHuoJianFa ||
		typeEnum == SKILL_TYPE_HuoQiang)
	{
		if (typeEnum == SKILL_TYPE_HuoQiang)
		{
			SkillState::_s_state_pre_fire_wall = true;
		}

		if (m_pSkillMenu)
		{
			bool flag = true;
			CCArray *children = m_pSkillMenu->getChildren();
			if ( children && children->count() > 0 )
			{
				CCObject* child = NULL;
				CCARRAY_FOREACH(children, child)
				{
					CCNode* pNode = dynamic_cast<CCNode *>(child);
					if (pNode->getTag() == tag)
					{
						refreshSkillOnOff(tag, pNode, flag);
						flag = false;
					}
				}
			}
		}
	}
	else
	{
		pHero->clickSkills(tag);
	}
}

void SkillLayer::updateSkillList()
{
    removeSkillMenuChildren();

    for (int i=0; i<8; i++)
    {
        int sid = UserData::getIntData(HeroData::getPID(), CPUserData::FAST_NUM_, i+1);
        int type = UserData::getIntData(HeroData::getPID(), CPUserData::FAST_TYPE_, i+1);
        
        float x, y;
        
        // 使用与initNormal相同的位置
        switch (i) {
            case 0:  // 技能1
                x = -40.0f; y = 190.0f;
                break;
            case 1:  // 技能2
                x = -110.0f; y = 190.0f;
                break;
            case 2:  // 技能3
                x = -180.0f; y = 190.0f;
                break;
            case 3:  // 技能4
                x = -115.0f; y = 260.0f;
                break;
            case 4:  // 技能5
                x = -240.0f; y = 120.0f;
                break;
            case 5:  // 技能6
                x = -240.0f; y = 50.0f;
                break;
            case 6:  // 技能7
                x = -160.0f; y = 120.0f;
                break;
            case 7:  // 技能8
                x = -160.0f; y = 50.0f;
                break;
        }
        
      
        
        if (type==1)
        {
            std::string strIconUrl;
            std::string strKey = "icon";
            if(LuaData::getProp(LuaData::SKILL, sid, strKey, strIconUrl))                
            {
                if(!strIconUrl.empty() && strIconUrl != "0")
                {
                    strIconUrl = "skill_" + strIconUrl;
                    CCSprite *norm = LayoutData::getSpriteByFrameName(strIconUrl + ".png");
                    CCSprite *sel = NULL;
                    if (sid/10 != SKILL_TYPE_HuoQiang)
                    {
                        sel = LayoutData::getSpriteByFrameName(strIconUrl + "_sel.png");
                    }
                    else
                    {
                        sel = LayoutData::getSpriteByFrameName(strIconUrl + ".png");
                    }
                    CCMenuItemSprite *pItem = CCMenuItemSprite::create(norm, sel);
                    pItem->setPosition(ccp(x, y));
                    pItem->setTarget(this, menu_selector(SkillLayer::useSkillCallback));
                    m_pSkillMenu->addChild(pItem, type, sid);

                    refreshSkillOnOff(sid, pItem, false);

                    CCSprite* activeSprite = SystemData::getSpriteByPlist("main_ui.skill_bkg");
                    activeSprite->setColor(ccc3(0, 0, 0));
                    CCProgressTimer *progressCD = CCProgressTimer::create(activeSprite);
                    progressCD->setType(kCCProgressTimerTypeRadial);
                    progressCD->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/2));
                    progressCD->setAnchorPoint(pItem->getAnchorPoint());
                    progressCD->setTag(TAG_COOLDOWN_BASE + sid);
                    pItem->addChild(progressCD);
                    progressCD->setReverseProgress(true);
                }
            }
        }
        else if (type==2)
        {
            CCMenuItemImage* pItem=CommonFunction::getItemIconInSkillLayer(CommonFunction::createNewItem(sid));
            pItem->setPosition(ccp(x, y));
            pItem->setTarget(this,menu_selector(SkillLayer::useItemCallback));
            m_pSkillMenu->addChild(pItem, type, sid);
        }
        else
        {
            CCMenuItemImage* sprite = SystemData::getMenuItemImageByPlist("main_ui.skill_bkg");            
            sprite->setTarget(this,menu_selector(SkillLayer::emptyBtnCB));
            sprite->setTag(i+1);
            sprite->setPosition(ccp(x, y));
            m_pSkillMenu->addChild(sprite);
        }
    }
}

//bool SkillLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
//{
//	if (mNormalLayer->isVisible())
//	{
//		m_beginPoint = pTouch->getLocation();		
//		float dis = ccpDistance(m_beginPoint,ccp(SystemData::size_x,0));
//		if (dis < Radius + 50)
//		{
//			m_preAngle = PI-std::atan(m_beginPoint.y/(SystemData::size_x-m_beginPoint.x));
//			mSkillMenuTouched = m_pSkillMenu->ccTouchBegan(pTouch, pEvent);
//			return true;
//		}
//	}
//	
//	return false;
//}
//
//void SkillLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
//{
//	CCPoint curPoint = pTouch->getLocation();
//	float curAngle = PI-std::atan(curPoint.y/(SystemData::size_x-curPoint.x));	
//	float angle = m_preAngle-curAngle;
//	float targetAngle = m_pRotateNode->getRotation()*PI/180+angle;
//	if(targetAngle>=-PI/16 && targetAngle<=PI/2+PI/16)
//	{
//		m_pRotateNode->setRotation(targetAngle*180/PI);
//	}
//	m_preAngle = curAngle;
//	if (mSkillMenuTouched)
//	{
//		m_pSkillMenu->ccTouchMoved(pTouch, pEvent);
//	}
//}
//
//void SkillLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
//{
//	m_curPoint = pTouch->getLocation();
//	if(!m_bLockTouch)
//	{
//		updateArrowState(m_pRotateNode->getRotation());
//	}
//
//	m_curPoint.x = m_curPoint.x-m_beginPoint.x;
//	m_curPoint.y = m_curPoint.y-m_beginPoint.y;
//
//	const float dist = m_curPoint.x * m_curPoint.x + m_curPoint.y * m_curPoint.y;
//	m_isRotatingPannel = (dist >= TOUCH_MOVE_DISTANCE);
//	if (mSkillMenuTouched)
//	{
//		if (m_isRotatingPannel)
//		{
//			m_pSkillMenu->ccTouchCancelled(pTouch, pEvent);
//		}
//		else
//		{
//			m_pSkillMenu->ccTouchEnded(pTouch, pEvent);
//		}
//	}
//	mSkillMenuTouched = false;
//}
bool SkillLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (mNormalLayer->isVisible())
    {
        m_beginPoint = pTouch->getLocation();
        m_bTargetSwiped = false;
        m_bAttackTouch = false;
        if (m_pEasyAttackBtn)
        {
            CCPoint local = m_pEasyAttackBtn->convertToNodeSpace(m_beginPoint);
            const CCSize &btnSize = m_pEasyAttackBtn->getContentSize();
            m_bAttackTouch = (local.x >= 0 && local.y >= 0
                && local.x <= btnSize.width && local.y <= btnSize.height);
        }
        if (m_bAttackTouch)
        {
            // 攻击键触摸完全由 SkillLayer 接管，不转发给 m_pSkillMenu
            m_lastSwitchY = m_beginPoint.y;
            return true;
        }
        float dis = ccpDistance(m_beginPoint,ccp(SystemData::size_x,0));

        if (dis < Radius + 50)  // 如果点击了技能区域
        {
            // 只处理点击，不标记为可滑动
            mSkillMenuTouched = m_pSkillMenu->ccTouchBegan(pTouch, pEvent);
            return true;
        }
    }
    
    return false;
}

void SkillLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (mSkillMenuTouched)
    {
        m_pSkillMenu->ccTouchMoved(pTouch, pEvent);
    }
    if (m_bAttackTouch)
    {
        selectTargetBySlide(pTouch->getLocation());
    }
}

void SkillLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (mSkillMenuTouched)
    {
        m_pSkillMenu->ccTouchEnded(pTouch, pEvent);
    }
    else if (m_bAttackTouch && !m_bTargetSwiped)
    {
        // 攻击键原地点击，触发普通攻击
        easyAttackCB(NULL);
    }
    mSkillMenuTouched = false;
    m_isRotatingPannel = false;  // 确保不触发旋转
    m_bAttackTouch = false;
    m_bTargetSwiped = false;
}
void SkillLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

void SkillLayer::turnUpCallback( CCObject* pSender )
{
	float targetAngle = (m_pRotateNode->getRotation()+22.5)*PI/180;
	if(targetAngle>=-PI/16 && targetAngle<=PI/2+PI/16)
	{
		m_bLockTouch = true;
		updateArrowState(targetAngle*180/PI);
	}
}

void SkillLayer::turnDownCallback( CCObject* pSender )
{
	float targetAngle = (m_pRotateNode->getRotation()-22.5)*PI/180;
	if(targetAngle>=-PI/16 && targetAngle<=PI/2+PI/16)
	{
		m_bLockTouch = true;
		updateArrowState(targetAngle*180/PI);
	}
}

void SkillLayer::onSpecialSkill( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		const int skillID = node->getTag();
		if (HeroData::getSkillCD(skillID) > 0)
		{
			CPEventHelper::uiNotify("SkillLayer", "", Error::Combat_InCoolDown);
			AudioLoader::play(Sound::Effect::jinenglengque);
			return;
		}
		MsgPlayerUseSkillonEntityRequest* req = new MsgPlayerUseSkillonEntityRequest;
		req->skillid = skillID;
		req->eid = 0;
		HandleMessage::sendMessage(req);
	}
}

void SkillLayer::updateArrowState( float angle )
{
	const int t = std::floor(angle/22.5 + 0.5);	
	m_pRotateNode->runAction(CCSequence::create(
		CCRotateTo::create(0.1f, t * 22.5f),
		CCCallFunc::create(this, callfunc_selector(SkillLayer::unlockTouch)),
		NULL));

	m_pDown->setVisible(true);
	m_pUp->setVisible(true);
	if(t == 0)
	{
		m_pDown->setVisible(false);
	}
	else if(t == 4)
	{
		m_pUp->setVisible(false);
	}
}

void SkillLayer::unlockTouch()
{
	m_bLockTouch = false;
}

void SkillLayer::refreshSkillOnOff( int skillID, CCNode *skillBtn, bool isChange )
{
	if (!skillBtn)
	{
		return;
	}

	const int typeEnum = skillID/10;
	switch (typeEnum)
	{
	case SKILL_TYPE_BanYueWanDao:
		{
			refreshSkillOnOff(skillID, skillBtn, isChange, CPUserData::SKILL_BAN_YUE_OFF
				, SystemData::getLayoutString("main_ui.skill.openbanyue")
				, SystemData::getLayoutString("main_ui.skill.closebanyue"));
			break;
		}
	case SKILL_TYPE_CiShaJianShu:
		{
			refreshSkillOnOff(skillID, skillBtn, isChange, CPUserData::SKILL_CI_SHA_OFF
				, SystemData::getLayoutString("main_ui.skill.opencisha")
				, SystemData::getLayoutString("main_ui.skill.closecisha"));
			break;
		}
	case SKILL_TYPE_LieHuoJianFa:
		{
			refreshSkillOnOff(skillID, skillBtn, isChange, CPUserData::SKILL_LIE_HUO_OFF
				, SystemData::getLayoutString("main_ui.skill.openlieyan")
				, SystemData::getLayoutString("main_ui.skill.closelieyan"));
			break;
		}
	case SKILL_TYPE_HuoQiang:
		{
			if (isChange)
			{
				std::string strIconUrl;
				std::string strKey = "icon";
				if(LuaData::getProp(LuaData::SKILL, skillID, strKey, strIconUrl))				
				{
					if(!strIconUrl.empty() &&
						strIconUrl != "0")
					{
						strIconUrl = "skill_" + strIconUrl;
						CCNode *iconNode = skillBtn->getChildByTag(SKILL_ICON_COVER_TAG);
						if (iconNode)
						{
							iconNode->removeFromParent();
						}
						iconNode = LayoutData::getSpriteByFrameName(strIconUrl + "_sel.png");
						iconNode->setPosition(ccp(iconNode->getContentSize().width/2, iconNode->getContentSize().height/2));
						skillBtn->addChild(iconNode, 0, SKILL_ICON_COVER_TAG);
					}
				}
			}
			else
			{
				CCNode *iconNode = skillBtn->getChildByTag(SKILL_ICON_COVER_TAG);
				if (iconNode)
				{
					iconNode->removeFromParent();
				}
			}
			break;
		}
	}
}

void SkillLayer::refreshSkillOnOff( int skillID, CCNode *skillBtn, bool isChange, const std::string &userDataKey, const std::string &onNote, const std::string &offNote )
{
	if (!skillBtn)
	{
		return;
	}

	int flag = UserData::getIntData(HeroData::getPID(), userDataKey);
	if (isChange)
	{
		flag = (flag > 0 ? 0 : 1);
		UserData::setIntData(HeroData::getPID(), userDataKey, flag);
		UserData::saveData();
	}

	if(flag > 0)
	{
		std::string strIconUrl;
		std::string strKey = "icon";
		if(LuaData::getProp(LuaData::SKILL, skillID, strKey, strIconUrl))				
		{
			if(!strIconUrl.empty() &&
				strIconUrl != "0")
			{
				strIconUrl = "skill_" + strIconUrl;
				CCNode* pFlag = LayoutData::getSpriteByFrameName(strIconUrl + "_dis.png");
				pFlag->setPosition(ccp(pFlag->getContentSize().width/2,pFlag->getContentSize().height/2));
				skillBtn->addChild(pFlag, 0, SKILL_ICON_COVER_TAG);
				if (isChange)
				{
					NotificationHelper::showNote(offNote);
				}
			}
		}
	}
	else
	{
		CCNode *iconNode = skillBtn->getChildByTag(SKILL_ICON_COVER_TAG);
		if (iconNode)
		{
			iconNode->removeFromParent();
		}

		if (isChange)
		{
			NotificationHelper::showNote(onNote);
		}
	}
}

void SkillLayer::useItemCallback( CCObject* pSender )
{
	if (m_isRotatingPannel)	return;

	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		int iid=GameData::s_user->getUserItemData()->getItemBySid(tag);
		if (iid==0)
		{
			CPEventHelper::uiNotify("","",Error::NotEnoughItem);
		}
		else
		{
			ItemOperator::useItem(iid);
		}
	}
}

void SkillLayer::removeSkillMenuChildren()
{
	// this code used to resolve bug 2999 from jira
	// don't replace me with: m_pSkillMenu->removeAllChildren();
	typedef std::vector<CCNode *> NodeVect;
	NodeVect nodeVect;
	CCArray *children = m_pSkillMenu->getChildren();
	if ( children && children->count() > 0 )
	{
		CCObject* child = NULL;
		CCARRAY_FOREACH(children, child)
		{
			CCNode* pNode = dynamic_cast<CCNode *>(child);
			if (pNode)
			{
				nodeVect.push_back(pNode);
			}
		}
	}

	for (int i = 0; i < (int)nodeVect.size(); i++)
	{
		m_pSkillMenu->removeChild(nodeVect[i], true);
	}
}

void SkillLayer::updateItem()
{
	if (m_pSkillMenu)
	{
		CCArray *children = m_pSkillMenu->getChildren();
		if ( children && children->count() > 0 )
		{
			CCObject* child = NULL;
			CCARRAY_FOREACH(children, child)
			{
				CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage *>(child);
				if (pNode && pNode->getZOrder()==2)
				{
					((CCLabelAtlas*)(pNode->getChildByTag(100)))->setString(SystemData::intToString(GameData::s_user->getUserItemData()->getItemCntBySid(pNode->getTag())).c_str());
				}
			}
		}
	}
}

void SkillLayer::updateAllAngle(float time)
{
	if (!m_pRotateNode)
	{
		return;
	}
	float angle=m_pRotateNode->getRotation();
	const int t = std::floor(angle/22.5 + 0.5);	
	if (m_pSkillMenu)
	{
		CCArray *children = m_pSkillMenu->getChildren();
		if ( children && children->count() > 0 )
		{
			CCObject* child = NULL;
			CCARRAY_FOREACH(children, child)
			{
				CCNode* pNode = dynamic_cast<CCNode *>(child);
				if (pNode)
				{
					pNode->setRotation(-angle);
				}
			}
		}
	}
}

void SkillLayer::easyAttackCB( CCObject* pSender )
{
	GameRole* pHero = GameData::getMyRole();
	if (pHero && !pHero->isEasyAIOn())
	{
		pHero->clickSkills(0);
	}
}

CCPoint SkillLayer::s_sortRefPos = CCPointZero;

bool SkillLayer::compareGhostByDist(AliveGhost* a, AliveGhost* b)
{
	return ccpDistanceSQ(a->getSpritePosition(), s_sortRefPos) < ccpDistanceSQ(b->getSpritePosition(), s_sortRefPos);
}

void SkillLayer::selectTargetBySlide(const CCPoint &curPoint)
{
	GameRole* myRole = GameData::getMyRole();
	if (!myRole)
	{
		return;
	}
	const float SWITCH_STEP = 50.0f;
	const float dy = curPoint.y - m_lastSwitchY;
	if (dy > SWITCH_STEP)
	{
		AliveGhost* next = getNextAttackPlayer();
		if (next)
		{
			m_bTargetSwiped = true;
			myRole->changeToPlayerAnim(next);
			m_lastSwitchY = curPoint.y;
		}
	}
	else if (dy < -SWITCH_STEP)
	{
		AliveGhost* next = getNextAttackMonster();
		if (next)
		{
			m_bTargetSwiped = true;
			myRole->changeTheAim(next);
			m_lastSwitchY = curPoint.y;
		}
	}
}

AliveGhost* SkillLayer::getNextAttackPlayer()
{
	GhostManager* pMgr = GameData::getGhostManager();
	if (!pMgr) return NULL;
	std::vector<Ghost*> &ghosts = pMgr->getGhosts();
	vector<AliveGhost*> players;
	CCPoint myPos = GameData::s_user->m_pMainRole->getSpritePosition();
	for (size_t i = 0; i < ghosts.size(); i++)
	{
		Ghost* g = ghosts[i];
		if (!g || g->mType != GHOST_TYPE_PLAYER) continue;
		AliveGhost* p = dynamic_cast<AliveGhost*>(g);
		if (!p || p->isDead() || pMgr->isTargetFriendly(p)) continue;
		players.push_back(p);
	}
	if (players.empty()) return NULL;
	SkillLayer::s_sortRefPos = myPos;
	sort(players.begin(), players.end(), compareGhostByDist);
	int curEid = GameData::s_user->m_pMainRole->m_iTargeteid;
	for (size_t i = 0; i < players.size(); i++)
	{
		if (players[i]->mID == curEid)
		{
			return players[(i + 1) % players.size()];
		}
	}
	return players[0];
}

AliveGhost* SkillLayer::getNextAttackMonster()
{
	GhostManager* pMgr = GameData::getGhostManager();
	if (!pMgr) return NULL;
	std::vector<Ghost*> &ghosts = pMgr->getGhosts();
	vector<AliveGhost*> monsters;
	CCPoint myPos = GameData::s_user->m_pMainRole->getSpritePosition();
	for (size_t i = 0; i < ghosts.size(); i++)
	{
		Ghost* g = ghosts[i];
		if (!g || g->mType != GHOST_TYPE_MONSTER) continue;
		AliveGhost* m = dynamic_cast<AliveGhost*>(g);
		if (!m || m->isDead()) continue;
		int selFlag = 0;
		StaticData::getMonsterSelFlag(m->mStaticID, selFlag);
		if (selFlag != 0) continue;
		monsters.push_back(m);
	}
	if (monsters.empty()) return NULL;
	SkillLayer::s_sortRefPos = myPos;
	sort(monsters.begin(), monsters.end(), compareGhostByDist);
	int curEid = GameData::s_user->m_pMainRole->m_iTargeteid;
	for (size_t i = 0; i < monsters.size(); i++)
	{
		if (monsters[i]->mID == curEid)
		{
			return monsters[(i + 1) % monsters.size()];
		}
	}
	return monsters[0];
}

void SkillLayer::emptyBtnCB( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		if(m_iselectTime!=0 && pNode->getChildByTag(label_enum))
		{
			CPEventHelper::openPanel("MainPanel",8,3,0,0);
		}
		else
		{
			m_iselectTime=3;
			CCLabelTTF* p=SystemData::getLabelTTF("Setting_Skill_Text");
			p->setFontSize(18);
			p->setColor(ccGREEN);
			//p->setDimensions(CCSizeMake(36,0)); // 取消注释会导致安卓crash
			p->setPosition(ccp(pNode->getContentSize().width/2,pNode->getContentSize().height/2));
			pNode->addChild(p);
			p->setTag(label_enum);
			p->runAction(CCSequence::create(CCDelayTime::create(2.5f),CCFadeOut::create(0.5f),CCActionInstantRemoveFromParent::create(),NULL));
			
		}
		CCLog("press empty btn! %d",tag);
	}
}

void SkillLayer::updateSelecttime( int time )
{
	if (m_iselectTime==0)
	{
		return;
	}
	m_iselectTime=m_iselectTime-time;
}

void SkillLayer::update( float delta )
{
	updateAllAngle(0);
}


void SkillLayer::selectBattlePet(CCObject* pSender)
{
    CCLog("=== 宠物出战按钮点击 ===");
    
    static int currentPetId = 1;
    static int consecutiveSamePet = 0; // 连续选择同一个宠物的次数
    
    CCLog("尝试出战宠物ID: %d", currentPetId);
    
    // 发送出战请求
    MsgActivePetStateRequest* msg = new MsgActivePetStateRequest;
    msg->id = currentPetId;
    HandleMessage::sendMessage(msg);
    
    // 智能切换：如果连续5次选择同一个宠物都失败，自动切换
    consecutiveSamePet++;
    
    if (consecutiveSamePet >= 5) {
        // 切换到下一个宠物
        int nextPetId = currentPetId + 1;
        if (nextPetId > 5) nextPetId = 1;//5个宠物
        
        currentPetId = nextPetId;
        consecutiveSamePet = 0; // 重置计数
        
        CCLog("连续尝试3次失败，自动切换到宠物ID: %d", currentPetId);
    } else {
        CCLog("保持宠物ID: %d (连续次数: %d)", currentPetId, consecutiveSamePet);
    }
}

void SkillLayer::selectMountHorse(CCObject* pSender)
{
    int rideState = HeroData::getProp(Entity::attr_horse_ride_state);
    GameRole* myRole = GameData::getMyRole();

    if (rideState == 0)
    {
        // 上马
        if (myRole)
        {
            myRole->setDress(AVATAR_TYPE_HORSE, 1);
            myRole->setDress(AVATAR_TYPE_HORSEHEAD, 1);
            myRole->setExData(Entity::attr_horse_ride_state, 1);
        }
        HeroData::setProp(Entity::attr_horse_ride_state, 1);

        MsgRideReq* msg = new MsgRideReq;
        msg->OnOrOff = 1;
        HandleMessage::sendMessage(msg);
    }
    else
    {
        // 下马
        if (myRole)
        {
            myRole->setDress(AVATAR_TYPE_HORSE, 0);
            myRole->setDress(AVATAR_TYPE_HORSEHEAD, 0);
            myRole->setExData(Entity::attr_horse_ride_state, 0);
        }
        HeroData::setProp(Entity::attr_horse_ride_state, 0);

        MsgRideReq* msg = new MsgRideReq;
        msg->OnOrOff = 0;
        HandleMessage::sendMessage(msg);
    }
}

