#include "DesignationPanel.h"
#include "userdata/SystemData.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"
#include "userdata/HeroData.h"
#include "userData/LayoutData.h"
#include "userdata/StaticData.h"
#include "userdata/ActivityData.h"
#include "userdata/luadata/LuaData.h"
#include "ext/CCTabelViewEx.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include "EntityDefinition.h"
#include "controls/CPItemComponents.h"
#include "controls/CPScrollbar.h"
#include "network/HandleMessage.h"
#include "MsgPlayer.h"
#include "utils/StringUtils.h"

const static std::string DESIGN = "design";


Design::Design():
	listLayer(NULL),
	propertyLayer(NULL),
	descLayer(NULL),
	btnItemList(NULL),
	btn(NULL),
	btnLabel(NULL),
	topNode(NULL),
	downNode(NULL),
	currentBtn(NULL),
	currentIndex(0),
	m_pTime(NULL),
	time_label(NULL),
	m_iOddTime(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
}

Design::~Design()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
}

bool Design::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCScale9Sprite* pBorder=SystemData::getScale9SpriteByPlist("taskcontent_bigborder",705,433);
	pBorder->setAnchorPoint(CCPointZero);
	pBorder->setPosition(SystemData::getLayoutPoint("taskcontent_bigborder"));
	addChild(pBorder);

	initUI();


	listLayer = CCLayer::create();
	addChild(listLayer);
	return true;
}

void Design::initUI()
{
	CCScale9Sprite *pLeftborder=SystemData::getScale9SpriteByPlist("taskcontent_menuback",157,SystemData::getLayoutValue("taskcontent_leftmenu_size.h"));
	pLeftborder->setAnchorPoint(CCPointZero);
	pLeftborder->setPosition(ccp(11,9));
	addChild(pLeftborder);

	CCScale9Sprite *pRightTopborder=SystemData::getScale9SpriteByPlist("taskcontent_menuback",528,209);
	pRightTopborder->setAnchorPoint(CCPointZero);
	pRightTopborder->setPosition(ccp(175,220));
	addChild(pRightTopborder);


	propertyLayer = CCLayer::create();
	propertyLayer->setAnchorPoint(CCPointZero);
	propertyLayer->setPosition(ccp(175,220));
	propertyLayer->setContentSize(CCSizeMake(528,209));
	addChild(propertyLayer);

	CCSprite* ptitle1=SystemData::getSpriteByPlist("taskcontent_righttitleback");
	ptitle1->setPosition(ccp(450,411));
	addChild(ptitle1);
	CCLabelTTF* plabel1=SystemData::getLabelTTF("ui_chenghao_label");
	plabel1->setFontSize(20);
	plabel1->setColor(ccYELLOW);
	plabel1->setPosition(ccp(ptitle1->getContentSize().width/2,ptitle1->getContentSize().height/2));
	ptitle1->addChild(plabel1);

	CCScale9Sprite *pRightDownborder=SystemData::getScale9SpriteByPlist("taskcontent_menuback",528,206);
	pRightDownborder->setAnchorPoint(CCPointZero);
	pRightDownborder->setPosition(ccp(175,9));
	addChild(pRightDownborder);

	descLayer = CCLayer::create();
	descLayer->setAnchorPoint(CCPointZero);
	descLayer->setPosition(ccp(175,9));
	descLayer->setContentSize(CCSizeMake(528,206));
	addChild(descLayer);

	CCSprite* ptitle2=SystemData::getSpriteByPlist("taskcontent_righttitleback");
	ptitle2->setPosition(ccp(450,200));
	addChild(ptitle2);
	CCLabelTTF* plabel2=SystemData::getLabelTTF("ui_chenghao_huode");
	plabel2->setFontSize(20);
	plabel2->setColor(ccYELLOW);
	plabel2->setPosition(ccp(ptitle2->getContentSize().width/2,ptitle2->getContentSize().height/2));
	ptitle2->addChild(plabel2);


	topNode = GeneralMenu::create();
	topNode->setPosition(CCPointZero);
	topNode->setAnchorPoint(CCPointZero);
	addChild(topNode);

	btn = SystemData::getMenuItemImageByPlist("ui_btn_chenghaopeidai");//SystemData::getMenuItemImageByPlist("ui_btn_chenghaopeidai");
	btn->setPosition(ccp(650,250));
	btnLabel = SystemData::getLabelTTF("ui_btn_label_peidai");
	btnLabel->setPosition(btn->getPosition());
	btnLabel->setFontSize(20);
	btnLabel->setColor(ccWHITE);
	topNode->addChild(btn);
	topNode->addChild(btnLabel);

	m_pTime = CCLabelTTF::create("","",18);
	m_pTime->setPosition(ccp(btn->getPositionX()-btn->getContentSize().width-40,btn->getPositionY()));
	addChild(m_pTime);
	m_pTime->setVisible(false);

}

void Design::initLeftList()
{
	CCSize listSize = CCSizeMake(160,421);
	CCSize btnItemSize = CCSizeMake(155,50);
	btnItemList = CPItemComponents::create(listSize, new CPLayoutList(btnItemSize,true));
	btnItemList->setAnchorPoint(CCPointZero);
	btnItemList->setPosition(ccp(11,9));
	listLayer->addChild(btnItemList);

	const CCSize &barSize = CCSizeMake(4,421);
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	btnItemList->setScrollbar(scrollBar);

	int cnt = 0;
	StaticData::getHeadNamesCount(cnt);
	for (int i=0;i<cnt;i++)
	{
		CCNode *norm = CCNode::create();
		norm->setContentSize(btnItemSize);

		CCScale9Sprite * normalsprite = LayoutData::getScale9Sprite(DESIGN,"norm");
		normalsprite->setPosition(LayoutData::getCenter(btnItemSize));
		norm->addChild(normalsprite);

		CCNode *sel = CCNode::create();
		sel->setContentSize(btnItemSize);

		CCScale9Sprite * selectsprite = LayoutData::getScale9Sprite(DESIGN,"sel");
		selectsprite->setPosition(LayoutData::getCenter(btnItemSize));
		sel->addChild(selectsprite);

		CCMenuItemSprite* btnsprite = NULL;

		if (HeroData::getHeadNameIsOwned(i+1))
		{
			btnsprite = CCMenuItemSprite::create(norm,sel);
		}else
		{
			CCNode *norm = CCNode::create();
			norm->setContentSize(btnItemSize);

			CCScale9Sprite * normalsprite = LayoutData::getScale9Sprite(DESIGN,"huise");
			normalsprite->setPosition(LayoutData::getCenter(btnItemSize));
			norm->addChild(normalsprite);

			CCNode *sel = CCNode::create();
			sel->setContentSize(btnItemSize);

			CCScale9Sprite * selectsprite = LayoutData::getScale9Sprite(DESIGN,"huise");
			selectsprite->setPosition(LayoutData::getCenter(btnItemSize));
			sel->addChild(selectsprite);
			btnsprite = CCMenuItemSprite::create(norm,sel);
		}
		btnsprite->setAnchorPoint(CCPointZero);
		btnsprite->setTarget(this,menu_selector(Design::showRight));
		if (SystemData::getLayoutValue("tag_merried_tmp") == i+1)
		{
			continue;
		}
		btnItemList->addItem(btnsprite);
		btnsprite->setTag(i);

		CCLabelTTF* name=CCLabelTTF::create();
		std::string headName = "";
		StaticData::getHeadNamesTitle(i+1,HeroData::getJob(),HeroData::getGender(),headName);
		name->setString(headName.c_str());
		name->setColor(ccWHITE);
		name->setPosition(ccp(btnsprite->getContentSize().width/2,btnsprite->getContentSize().height/2));
		name->setFontSize(18);
		btnsprite->addChild(name);

		if (true)
		{
			CCScale9Sprite* rim = LayoutData::getScale9Sprite(DESIGN,"rim_chenghaolist");
			rim->setAnchorPoint(ccp(-0.008f,-0.1f));
			if(HeroData::getHeadNameIsWorn(i+1))
			{
//				rim->setTag(i+1);
				btnsprite->addChild(rim); 
			}else
			{
				rim->removeFromParent();
			}
		}

	}/*
	IDVector vect = HeroData::getOwnedHeadNames();
	IDVector vect2 = HeroData::getWornHeadNames();*/
}

void Design::onClick( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case tag_peidai:
			addHeadName();
			break;
		case tag_quxiao:
			cancelHeadName();
			break;
		case tag_notOwn:
			CPEventHelper::uiNotify("","",Error::HasNotTitle);
			break;
		default:
			break;
		}
	}
}

void Design::showRight( CCObject *pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		currentBtn = (CCMenuItemSprite*)pNode;
		int tag = pNode->getTag();
		refresh(tag);
	}
}

void Design::refresh( int tag )
{
	descLayer->removeAllChildrenWithCleanup(true);
	propertyLayer->removeAllChildrenWithCleanup(true);
	if (btnLabel)
	{
		btnLabel->removeFromParentAndCleanup(true);
		btnLabel = NULL;
	}
	if (true)
	{
		currentIndex = tag+1;

		StaticData::getHeadNamesData(currentIndex,SystemData::getLayoutString("durationgene"),durationgene);
		int curtime = ActivityData::getWorldTime();
		int starttime = HeroData::getBuffStartTime(durationgene);

		m_iOddTime = HeroData::getBuffTime(durationgene) - ( curtime - starttime );
		bool isOwned = HeroData::getHeadNameIsOwned(currentIndex);
		bool isWorn = HeroData::getHeadNameIsWorn(currentIndex);
		if (durationgene > 0 && m_iOddTime>0 && isOwned)
		{
			m_pTime->setString(StringUtils::timeToString(m_iOddTime,TimeType::dhms).c_str());
			m_pTime->setVisible(true);
			CCLabelTTF* time_label = SystemData::getLabelTTF("timelimitgift.label.timelimit");
			time_label->setPosition(ccp(250,30));
			propertyLayer->addChild(time_label);
		}else
		{
			if (m_pTime)
			{
				m_pTime->setVisible(false);
			}
		}
		
		//-----------------------------------------------------------------------------------

		std::string prostr = "";
		int propCnt = 0;
		StaticData::getHeadNamesAddPropCnt(tag+1,propCnt);
		if (propCnt > 0)
		{
			int x = 0;
			int y = 0;
			for(int i = 0;i < propCnt;i++)
			{
				StaticData::getHeadNamesAttrstring(tag+1,i+1,prostr);
				if (prostr != "0")
				{
					CCLabelTTF* prop=CCLabelTTF::create();
					prop->setString(prostr.c_str());
					prop->setColor(ccWHITE);
					prop->setFontSize(15);
					prop->setAnchorPoint(CCPointZero);
					prop->setPosition(ccp(10+250*x,150-40*y));
					if (propCnt == 1)
					{
						prop->setDimensions(CCSizeMake(propertyLayer->getContentSize().width-50,0));
						prop->setPosition(ccp(10,130));
					}
					propertyLayer->addChild(prop);
					x++;
					if (x==2)
					{
						x = 0;
						y++;
					}
				}

			}
		}

		CCLabelTTF* name=CCLabelTTF::create();
		std::string headName = "";
		StaticData::getHeadNamesData(tag+1,"desc",headName);
		name->setString(headName.c_str());
		name->setColor(ccWHITE);
		name->setFontSize(15);
		name->setAnchorPoint(CCPointZero);
		name->setPosition(ccp(10,150));
// 		name->setHorizontalAlignment(kCCTextAlignmentLeft);
// 		name->setDimensions(descLayer->getContentSize());
		descLayer->addChild(name);

		//佩带按钮根据左边列表每个称号变化

		btn->setPosition(ccp(650,250));
		int btnTag = 0;
		if (isOwned)
		{
			if (isWorn)
			{
				btnTag = tag_quxiao;
				btnLabel = SystemData::getLabelTTF("ui_btn_label_peidai_cancel");
			}
			else
			{
				btnTag = tag_peidai;
				btnLabel = SystemData::getLabelTTF("ui_btn_label_peidai");
			}
		}
		else
		{
			btnTag = tag_notOwn;
			btnLabel = SystemData::getLabelTTF("ui_btn_label_peidai");
		}
		btn->setTag(btnTag);
		btn->setTarget(this,menu_selector(Design::onClick));
		
		btnLabel->setPosition(btn->getPosition());
		btnLabel->setFontSize(20);
		btnLabel->setColor(ccWHITE);
		topNode->addChild(btnLabel);

	}
	
}

void Design::refreshLeftlist(int index)
{
	listLayer->removeAllChildrenWithCleanup(true);
	initLeftList();
	
}

void Design::onEnter()
{
	CCLayer::onEnter();
	this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(Design::initLeftList)),NULL));
}

void Design::addHeadName()
{
	MsgOpenHeadTitleRequest* msg=new MsgOpenHeadTitleRequest;
	msg->idx = currentIndex;
	HandleMessage::sendMessage(msg);
}

void Design::cancelHeadName()
{
	MsgCloseHeadTitleRequest* msg = new MsgCloseHeadTitleRequest;
	msg->idx = currentIndex;
	HandleMessage::sendMessage(msg);
}

void Design::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (CPEventHelper::getEventSource() == "HandleMessageHeadTitleOperationResponse")
		{
			refresh(currentIndex-1); 
			refreshLeftlist(currentIndex);
		}
	}

	else if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			refreshTime();
		}
	}
}


void Design::refreshTime()
{
	if (m_iOddTime>0)
	{
		m_iOddTime--;
	}
	else
	{
		if (m_pTime)
		{
			m_pTime->setVisible(false);
		}
		return;
	}
	if (m_pTime)
	{
		m_pTime->setString(StringUtils::timeToString(m_iOddTime,TimeType::dhms).c_str());
	}
	if (m_iOddTime==0)
	{
		if (m_pTime)
		{
			m_pTime->setVisible(false);
		}
	}
}
