#include "LuckyCircle.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/FuncData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/HeroData.h"
#include "userdata/ActivityData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "module/ActivityModule.h"
#include "GeneralMenu.h"
#include "MsgPlayer.h"
#include "EntityDefinition.h"
#include "event/EventDispatcher.h"
#include "event/EventProtocol.h"

const float PI = 3.1415926f;

#define		ANGLE_MAX	360
#define		ANGLE_OFFSET_MOVE	10

#define		TIME_PER_ANGLE_SLOW	0.003f
#define		TIME_PER_ANGLE_SLOWER	0.02f

LuckyCircle::LuckyCircle():
	circlezhizhen(NULL)
	,m_pRotateNode(NULL)
	,menu(NULL)
	,m_iTimeSpan(0)
	,m_id_pos(0)
	,startBtn(NULL)
	,goldLab(NULL)
	,timesLab(NULL)
	,actionBy(NULL)
	,yuanBao(0)
	,lotteryTimes(0)
	,circlespendGold(0)
	,circleEctraspendGold(0)
{
	CPEvtDispatcher.addEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

LuckyCircle::~LuckyCircle()
{
	CPEvtDispatcher.removeEventListener(CPEventName::LGC_TIMER, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

bool LuckyCircle::init()
{
	if (!PartPanel::init())
	{
		return false;
	}

	circlespendGold = SystemData::getLayoutValue("circlespendGold");
	circleEctraspendGold = SystemData::getLayoutValue("circleEctraspendGold");
	
	// ========== 设置面板位置 ==========
	// 设置到(240, 100)位置
	this->setPosition(ccp(240, 100));
	this->setAnchorPoint(ccp(0.5, 0.5));  // 中心锚点
	
	// 调试
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	CCLOG("幸运转盘位置: (800, 100), 屏幕: %.0fx%.0f", screenSize.width, screenSize.height);
	// ========== 位置设置结束 ==========
	
	initUI();
	return true;
}

void LuckyCircle::initUI()
{
	m_nHeight = LayoutData::getSize(CPModuleName::ACTIVITY,"LuckyCircleBigBKG").height;
	m_nWidth = LayoutData::getSize(CPModuleName::ACTIVITY,"LuckyCircleBigBKG").width;
	

	CCSprite* pbkg1 = LayoutData::getSprite(CPModuleName::ACTIVITY,"luckycircleRightBkg");
	pbkg1->setAnchorPoint(CCPointZero);
	addChild(pbkg1);

	CCSprite* pbkg0= LayoutData::getSprite(CPModuleName::ACTIVITY,"luckycircleLeftBkg");
	pbkg0->setAnchorPoint(CCPointZero);
	addChild(pbkg0);

	m_pRotateNode = CCNode::create();
	m_pRotateNode->setPosition(ccp(233,253));
	addChild(m_pRotateNode);

	circlezhizhen = LayoutData::getSprite(CPModuleName::ACTIVITY,"circleZhizhen");
	circlezhizhen->setPosition(LayoutData::getCenter(m_pRotateNode->getContentSize()));
	m_pRotateNode->addChild(circlezhizhen);

	addCover(LayoutData::getPoint(CPModuleName::ACTIVITY,"luckycircleCoverpos"));

	initButton();
	initLabel();
	initItems();

}

void LuckyCircle::initButton()
{
	menu = GeneralMenu::create();
	if (menu)
	{
		menu->setAnchorPoint(CCPointZero);
		menu->setPosition(CCPointZero);
		addChild(menu);
	}
	CCMenuItemImage* pclose=LayoutData::getMenuItemImg(CPModuleName::ACTIVITY,"luckycircleTuichu");
	pclose->setTarget(this,menu_selector(LuckyCircle::closecallback));
	menu->addChild(pclose);

	startBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY,"luckycircleStart");
	startBtn->setTarget(this,menu_selector(LuckyCircle::menuCallBack));
	startBtn->setTag(1);
	startBtn->setVisible(true);
	menu->addChild(startBtn);

	CCMenuItemImage* payBtn = LayoutData::getMenuItemImg(CPModuleName::ACTIVITY,"luckycirclePay");
	payBtn->setTarget(this,menu_selector(LuckyCircle::menuCallBack));
	payBtn->setTag(2); 
	menu->addChild(payBtn);
}

void LuckyCircle::closecallback( CCObject* target )
{
	this->removeFromParent();
}

void LuckyCircle::initLabel()
{
	CCLabelTTF* descTitle = LayoutData::getLabelTTF(CPModuleName::ACTIVITY,"circleDescTitle");
	addChild(descTitle);

	CCLabelTTF* words1Label1 = CCLabelTTF::create(LayoutData::getString(CPModuleName::ACTIVITY,"circleDescWords01").c_str(),"",16);
	CCLabelTTF* words1Label2 = CCLabelTTF::create(LayoutData::getString(CPModuleName::ACTIVITY,"circleDescWords02").c_str(),"",16);
	CCLabelTTF* words1Label3 = CCLabelTTF::create(LayoutData::getString(CPModuleName::ACTIVITY,"circleDescWords03").c_str(),"",16);
	CCLabelTTF* words1Label4 = CCLabelTTF::create(LayoutData::getString(CPModuleName::ACTIVITY,"circleDescWords04").c_str(),"",16);

	if (words1Label1)
	{
		words1Label1->setAnchorPoint(CCPointZero);
		words1Label1->setPosition(ccp(descTitle->getPositionX()-42,descTitle->getPositionY()-35));
	}
	if (words1Label2)
	{
		words1Label2->setAnchorPoint(CCPointZero);
		words1Label2->setPosition(ccp(descTitle->getPositionX()-42,descTitle->getPositionY()-65));
	}
	if (words1Label3)
	{
		words1Label3->setAnchorPoint(CCPointZero);
		words1Label3->setPosition(ccp(descTitle->getPositionX()-42,descTitle->getPositionY()-95));
	}
	if (words1Label4)
	{
		words1Label4->setAnchorPoint(CCPointZero);
		words1Label4->setPosition(ccp(descTitle->getPositionX()-42,descTitle->getPositionY()-125));
	}

	yuanBao = HeroData::getProp(Entity::attr_gold);
	lotteryTimes =ActivityData::getExDataZ(6000);
	if (lotteryTimes<0)
	{
		lotteryTimes = 0;
	}

	std::string goldStr = SystemData::intToString(yuanBao);
	goldLab = CCLabelTTF::create();
	goldLab->setString(goldStr.c_str());
	goldLab->setFontSize(16);
	goldLab->setAnchorPoint(CCPointZero);
	goldLab->setPosition(ccp(words1Label4->getPositionX()+135,words1Label4->getPositionY()));

	std::string freeTimesStr = SystemData::intToString(lotteryTimes);//抽奖剩余次数
	timesLab = CCLabelTTF::create();
	timesLab->setString(freeTimesStr.c_str());
	timesLab->setFontSize(16);
	timesLab->setAnchorPoint(CCPointZero);
	timesLab->setPosition(ccp(words1Label3->getPositionX()+135,words1Label3->getPositionY()));

	addChild(words1Label1);
	addChild(words1Label2);
	addChild(words1Label3);
	addChild(words1Label4);
	addChild(goldLab);
	addChild(timesLab);


}

void LuckyCircle::menuCallBack( CCObject* target )
{
	CCNode* pNode = dynamic_cast<CCNode*>(target);
	if (pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case 1:
			{
				if (checkIfCanStart())
				{
					if (true)
					{
						startCircle();
//						CCEaseBackOut* backOut  = CCEaseBackOut::create(dynamic_cast<CCActionInterval *>(actionBy) );
//						CCActionInterval* backOutBack = backOut->reverse();
						//--------------------
// 						int endAngle = 0;
// 						int rotation = m_pRotateNode->getRotation();
// 						int angle = ANGLE_MAX - rotation%ANGLE_MAX + endAngle + ANGLE_OFFSET_MOVE;
// 						CCRotateBy *rb1 = CCRotateBy::create(angle * TIME_PER_ANGLE_SLOW, angle);
// 						CCEaseSineOut *eso = CCEaseSineOut::create(rb1);
// 						CCRotateBy *rb2 = CCRotateBy::create(ANGLE_OFFSET_MOVE * TIME_PER_ANGLE_SLOWER, -ANGLE_OFFSET_MOVE);
//						CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(LayerDestiny::onActionEnd));
// 
// 						CCAction *act = CCSequence::create(eso, rb2, NULL);
// 						m_pRotateNode->runAction(act);
						//--------------------
						
						//--------------------
//						m_pRotateNode->runAction(backOut);
						
						m_iTimeSpan = SystemData::getLayoutValue("Luckycircle_timespan");
					}
					else
					{
//						CPEventHelper::uiNotify("","",Error::time10sspan);
					} 
				}
				else
				{
					CPEventHelper::uiNotify("","",20);
				}
			}
			break;
		case 2:
			{
				CPEventHelper::openPanel("RechargePanel");
			}
			break;
		default:
			break;
		}
	}
}

void LuckyCircle::initItems()
{
	for (int i=0;i<8;i++)
	{
		int reqsid = 0;
		int reqcnt = 0;
		LuaData::getProp("gdLuckyCircleReward",i+1,"itemID",reqsid);
		LuaData::getProp("gdLuckyCircleReward",i+1,"cnt",reqcnt); 
		UserItem* pUserItem = CommonFunction::createNewItem(reqsid);
		pUserItem->count = reqcnt;
		CCMenuItemImage* pItem = CommonFunction::getItemIconButDelete(pUserItem);
		pItem->setTarget(this,menu_selector(LuckyCircle::itemClickCallBack));
		pItem->setPosition(ccp(235+cos((0.5f-0.25f*i)*PI)*110,253+sin((0.5f-0.25f*i)*PI)*110));
		menu->addChild(pItem);
	}
}

void LuckyCircle::itemClickCallBack( CCObject* target )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)target;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips);
}



void LuckyCircle::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();

	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source=="HandleMessageFuncDataNotify")
		{
			
		}
	}
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source=="HandleMessageFuncDataNotify")
		{

			int funcid = FuncData::getCurFuncID();
			if (funcid == 18)
			{
				if (startBtn)
				{
					startBtn->setVisible(false);
				}
				actionBy = CCRotateBy::create(1,1080);
				CCActionInterval* actionByBack = actionBy->reverse();
				m_pRotateNode->runAction(CCRepeatForever::create(actionBy));
				runAction(CCSequence::create(CCDelayTime::create(4)
					, CCCallFunc::create(this, callfunc_selector(LuckyCircle::showStop))
					, NULL));
				func_locate();
				m_id_pos=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
				float time = 3;//6秒后显示得到的物品
				CCActionInterval* action =
					CCSequence::create(CCDelayTime::create(time),
					CCCallFunc::create(this, callfunc_selector(LuckyCircle::showGetTip)),
					CCDelayTime::create(time),NULL);
				this->runAction(action);

				
			}
		}
	}
	if (eventName == CPEventName::LGC_TIMER)
	{
		if (source == "TimeManager")
		{
			Update(1);
		}
	}
}

void LuckyCircle::startCircle()
{
	FuncData::sendFuncMsgWithID(18,0,0,0);
}

void LuckyCircle::showGetTip()
{
	m_pRotateNode->stopAllActions();

	m_pRotateNode->setRotation((m_id_pos-1)*45-5);
	if (startBtn)
	{
		startBtn->setVisible(true);
		lotteryTimes = ActivityData::getExDataZ(6000);

		goldLab->setString(SystemData::intToString(HeroData::getProp(Entity::attr_gold)).c_str());
		timesLab->setString(SystemData::intToString(lotteryTimes).c_str());
	}
	//指针停下来提示物品获得

}

void LuckyCircle::Update(float dt)
{
	if (m_iTimeSpan > 0)
	{
		m_iTimeSpan--;
	}
}

bool LuckyCircle::checkIfCanStart()
{
	lotteryTimes = ActivityData::getExDataZ(6000);
	if (lotteryTimes<0)
	{
		lotteryTimes = 0;
	}
	if (lotteryTimes > 0)
	{
		return true;
	}
	return true;
}


//---------------------------------------------------
/*
{
	int endAngle = getAngleByTag(mData->dataMsg->indexCurrent);
	int rotation = mData->wheelPointer->getRotation();
	int angle = ANGLE_MAX - rotation%ANGLE_MAX + endAngle + ANGLE_OFFSET_MOVE;
	CCRotateBy *rb1 = CCRotateBy::create(angle * TIME_PER_ANGLE_SLOW, angle);
	CCEaseSineOut *eso = CCEaseSineOut::create(rb1);
	CCRotateBy *rb2 = CCRotateBy::create(ANGLE_OFFSET_MOVE * TIME_PER_ANGLE_SLOWER, -ANGLE_OFFSET_MOVE);
	CCCallFunc *func = CCCallFunc::create(this, callfunc_selector(LayerDestiny::onActionEnd));

	CCAction *act = CCSequence::create(eso, rb2, func, NULL);
	mData->wheelPointer->runAction(act);



}*/
void LuckyCircle::func_locate()
{
	m_id_pos=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
	float d_rotation = (m_id_pos-1)*45-m_pRotateNode->getRotation();
	CCActionInterval* actionBy = CCRotateBy::create(3.2,d_rotation+10*360);
	CCEaseExponentialOut* backOut  = CCEaseExponentialOut::create(dynamic_cast<CCActionInterval *>(actionBy) );
	m_pRotateNode->runAction(backOut);
}

void LuckyCircle::showStop()
{
	m_pRotateNode->stopAllActions();
}