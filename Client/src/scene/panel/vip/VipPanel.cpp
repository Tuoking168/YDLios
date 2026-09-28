#include "VipPanel.h"
#include "VIPModule.h"

#include "ItemDefinition.h"

#include "PlatformDefinition.h"

#include "utils/StringUtils.h"
#include "utils/RichTextUtils.h"

#include "controls/CPItemComponents.h"
#include "controls/CPProgressBar.h"
#include "controls/CPRichText.h"
#include "controls/CPScrollbar.h"

#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"
#include "userdata/StaticData.h"

#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"

#include "network/HandleMessage.h"

#include "EntityDefinition.h"
#include "PlatformDefinition.h"
#include "logic/platform/IPlatform.h"

VipPanel::VipPanel()
	:mPage(0)	
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE,this);
}

VipPanel::~VipPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE,this);
}

bool VipPanel::init()
{
	 if (!FullScreenPanel::create())
	 {
		 return false;
	 }	 
	
	 if (HeroData::getProp(Entity::attr_vip_level) == 0)
	 {
		 mPage = 1;	     
	 }
	 else
	 {
		 mPage = HeroData::getProp(Entity::attr_vip_level);		 
	 }	 	 

	 initUI();
	 initTopFrame();
	 initBottomFrame();

	 refereshTopImg();
	 refereshBottomImg();
	 refereshBottomBtn();

	 return true; 
}

void VipPanel::initUI()
{
	CCLabelTTF *vipTitle = LayoutData::getLabelTTF(CPModuleName::VIP,"vipPanelTitleLabel");
	addChild(vipTitle);

	const int cnt = LayoutData::getInt(CPModuleName::VIP,"vipPanelBoardCnt");
	for (int i=0;i<cnt;i++)
	{
		const std::string &key = "vipPanelBoard" + StringUtils::toString(i);
		CCScale9Sprite *board = LayoutData::getScale9Sprite(CPModuleName::VIP, key);
		addChild(board);
	}	
}

void VipPanel::initTopFrame()
{
	CCSprite *vipLogo = LayoutData::getSprite(CPModuleName::VIP,"vipPanelVipLogo");
	addChild(vipLogo);	

	mRechargeNode = CCNode::create();
	addChild(mRechargeNode);		

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItem *rechargeBtn = LayoutData::getMenuItemImg(CPModuleName::VIP,"vipPanelRechargeBtn");	
	rechargeBtn->setTarget(this,menu_selector(VipPanel::onRechargeBtn));
	menu->addChild(rechargeBtn);

	if(CPPlatformMnger.getIntData(CPPlatformData::CHANNEL_ID) != ChannelID::tencent_msdk)
	{
		//腾讯渠道去掉改VIP显示内容
		CCLabelTTF *vipService=LayoutData::getLabelTTF(CPModuleName::VIP,"vipPanelVipService");
		addChild(vipService);
	}
}

void VipPanel::initBottomFrame()
{	
	CCScale9Sprite *lineImg = LayoutData::getScale9Sprite(CPModuleName::VIP, "vipPanelLineImg");
	addChild(lineImg);	
	
	CCLabelTTF *wordInLine1 = LayoutData::getLabelTTF(CPModuleName::VIP,"vipPanelWordInLine0");
	addChild(wordInLine1,1);
	
	CCLabelTTF *wordInLine2 = LayoutData::getLabelTTF(CPModuleName::VIP,"vipPanelWordInLine1");
	addChild(wordInLine2,1);

	mNode = CCNode::create();	
	addChild(mNode);

	//刷新框
	const CCSize &listSize = LayoutData::getSize(CPModuleName::VIP,"vipPanelList");
	mItemList = CPItemComponents::create(listSize,new CPLayoutList());
	mItemList ->setPosition(LayoutData::getPoint(CPModuleName::VIP,"vipPanelList"));
	const CCSize &barSize = LayoutData::getSize(CPModuleName::VIP, "vipPanelItemScroll");
	CPScrollbar *scrollBar = CPScrollbar::create(LayoutData::getScale9Sprite(CPModuleName::COMMON, "scrollbar"), barSize);
	mItemList->setScrollbar(scrollBar);
	addChild(mItemList);	

	CCMenu *menu=CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);	
	
	mLeftBtn = LayoutData::getMenuItemImg(CPModuleName::VIP,"vipPanelBottomLeftBtn");
	mLeftBtn->setTarget(this,menu_selector(VipPanel::onLeftBtn));
	menu->addChild(mLeftBtn);
	
	mRightBtn = LayoutData::getMenuItemImg(CPModuleName::VIP,"vipPanelBottomRightBtn");
	mRightBtn->setTarget(this,menu_selector(VipPanel::onRightBtn));
	menu->addChild(mRightBtn);
}

void VipPanel::refereshTopImg()
{
	mRechargeNode->removeAllChildren();

    const int levelNum = HeroData::getProp(Entity::attr_vip_level);
	const int compareMaxLevel = LayoutData::getInt(CPModuleName::VIP,"vipPanelCompareMaxLevel");	
	CCPoint levelPoint = LayoutData::getPoint(CPModuleName::VIP,"vipPanelTopPoint");

	if (levelNum <= 0)
	{		
		CCLabelTTF *levelLabel = LayoutData::getLabelTTF(CPModuleName::VIP,"vipPanelTopLabel2");			
		mRechargeNode->addChild(levelLabel);
	}
	else if (levelNum > 0 && levelNum <= compareMaxLevel)
	{
		const int labelCnt = LayoutData::getInt(CPModuleName::VIP,"vipPanelTopLabelCnt");
		for (int i = 0; i < labelCnt; i++)
		{
			const std::string &key = "vipPanelTopLabel" +StringUtils::toString(i);
			CCLabelTTF *topLabel = LayoutData::getLabelTTF(CPModuleName::VIP,key);
			addChild(topLabel);
		}//for	

		float scaleNum = LayoutData::getFloat(CPModuleName::VIP,"vipPanelScaleNum");
        const std::string &key = "vipPanelBottomImg" + StringUtils::toString(levelNum);	   
	    CCSprite *levelImg = LayoutData::getSprite(CPModuleName::VIP,key);	
        levelImg->setScale(scaleNum);
	    levelImg->getTexture()->setAntiAliasTexParameters();
	    levelImg->setPosition(levelPoint);
	    mRechargeNode->addChild(levelImg);	
	}//else if	

	float percentNum = 0;	
	float nowRecharge = HeroData::getProp(Entity::attr_recharge_money);
	float nowNeedMoney = 0; 
	
	float fullPercent = LayoutData::getFloat(CPModuleName::VIP,"vipPanelFullPercent");	

	if (levelNum < compareMaxLevel)
	{
		StaticData::getVIPData(HeroData::getProp(Entity::attr_vip_level) + 1,"money",nowNeedMoney);
	}
	else if (levelNum == compareMaxLevel)
	{
		StaticData::getVIPData(compareMaxLevel,"money",nowNeedMoney);
	}
	
	if (nowNeedMoney == 0)
	{
		nowRecharge = 0;
		nowNeedMoney = 1; 
	}
	
	if (levelNum == compareMaxLevel)
	{
		percentNum = fullPercent;		
	}
	else
	{
        percentNum = (nowRecharge/nowNeedMoney)*fullPercent;
	}			

	CCSprite *barImg = LayoutData::getSprite(CPModuleName::VIP,"vipPanelBarImg");
	mRechargeNode->addChild(barImg);

	CCSprite *changeBar = LayoutData::getSprite(CPModuleName::VIP,"vipPanelChangeBarImg");	
	CCPoint barPoint = LayoutData::getPoint(CPModuleName::VIP,"vipPanelBarPoint");
	CPProgressBar *bar = CPProgressBar::create(changeBar);
	bar->setPercentage(percentNum);
	bar->setPosition(barPoint);
	mRechargeNode->addChild(bar);	
	
    const std::string &numStr = StringUtils::toString(nowRecharge)+"/"+StringUtils::toString(nowNeedMoney);
	CCLabelTTF *numLabel = LayoutData::getLabelTTF(CPModuleName::VIP,"vipPanelNumLabel");
	numLabel->setString(numStr.c_str());
	mRechargeNode->addChild(numLabel,1);
}

void VipPanel::refereshBottomImg()
{	
    mNode->removeAllChildren();
	mItemList->removeAllItems();
	
    const int compareMaxLevel = LayoutData::getInt(CPModuleName::VIP,"vipPanelCompareMaxLevel");	

	const std::string &levelStr= StringUtils::toString(mPage);
	CCLabelTTF *levelInLine = LayoutData::getLabelTTF(CPModuleName::VIP,"vipPanelLevelInLine");
	levelInLine->setString(levelStr.c_str());
	mNode->addChild(levelInLine,1);

	CCPoint leftPoint=LayoutData::getPoint(CPModuleName::VIP,"vipPanelBottomLeftPoint");
	CCPoint rightPoint=LayoutData::getPoint(CPModuleName::VIP,"vipPanelBottomRightPoint");
	const int bottomCnt = LayoutData::getInt(CPModuleName::VIP,"vipPanelBottomCnt");		

	if (mPage > 1)
	{
		const std::string &key0 = "vipPanelBottomImg"+StringUtils::toString(mPage-1);
	    CCSprite *bottomLeftImg=LayoutData::getSprite(CPModuleName::VIP,key0);
	    bottomLeftImg->setPosition(leftPoint);
	    mNode->addChild(bottomLeftImg);
	}	   

    if(mPage < compareMaxLevel)
	{
	    std::string key1 = "";
		
	    key1 = "vipPanelBottomImg"+StringUtils::toString(mPage + 1);
			
		CCSprite *bottomRightImg=LayoutData::getSprite(CPModuleName::VIP,key1);
		bottomRightImg->setPosition(rightPoint);
		mNode->addChild(bottomRightImg);	    
	}		

	std::string strInfo="";
	int wordLevel = 0;

	if (mPage == 0)
	{
		mPage = 1;
		wordLevel = mPage;
	}
	else
	{
		wordLevel = mPage;
	}
		
	StaticData::getVIPDesc(wordLevel,strInfo);		
	int fontSize = LayoutData::getInt(CPModuleName::VIP,"vipPanelFontSize");
	int width = LayoutData::getInt(CPModuleName::VIP,"vipPanelTextWidth");
	CPRichText *text = RichTextUtils::getRichText(strInfo,fontSize,width,0);//text, fontSize, width, heigh
	mItemList->addItem(text);
	
	const std::string &pageStr = StringUtils::toString(wordLevel) + "/" + StringUtils::toString(compareMaxLevel);//此处因为分子不能包含0，所有用wordLevel
	mPageLabel = LayoutData::getLabelTTF(CPModuleName::VIP,"vipPanelPageLabel");
	mPageLabel->setString(pageStr.c_str());
	mNode->addChild(mPageLabel);

	wordLevel++;
}

void VipPanel::refereshBottomBtn()
{
	const int compareMaxLevel = LayoutData::getInt(CPModuleName::VIP,"vipPanelCompareMaxLevel");

	if (mPage > 1)
	{
		mLeftBtn->setVisible(true);
	}
	else
	{
		mLeftBtn->setVisible(false);
	}

	if (mPage < compareMaxLevel)
	{
		mRightBtn->setVisible(true);
	}
	else
	{
		mRightBtn->setVisible(false);
	}
}

void VipPanel::onRechargeBtn(CCObject *target)
{
	CPEventHelper::openPanel("RechargePanel");	
}

void VipPanel::onLeftBtn(CCObject *target)
{		
	if (mPage > 1)
	{
		mPage--;
		refereshTopImg();
		refereshBottomBtn();
		refereshBottomImg();	
	}	
}

void VipPanel::onRightBtn(CCObject *target)
{	
	const int compareMaxLevel = LayoutData::getInt(CPModuleName::VIP,"vipPanelCompareMaxLevel");

	if (mPage < compareMaxLevel)
	{
		mPage++;
		refereshTopImg();
		refereshBottomBtn();
		refereshBottomImg();
	}			
}

void VipPanel::onCPEvent(const std::string &eventName)
{
	if (eventName == CPEventName::MSG_CHANGE)
	{
		const std::string source = CPEventHelper::getEventSource();
		if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			int temp =CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (temp == Entity::attr_vip_level || temp == Entity::attr_recharge_money)
			{
				refereshTopImg();
				refereshBottomBtn();
				refereshBottomImg();
			}		
		}
	}
}

