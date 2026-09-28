#include "MonthGiftPanel.h"
#include "EntityDefinition.h"
#include "MsgPlayer.h"
#include "EffectDefinition.h"
#include "GiftDefinition.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"

#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"
#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/SlideTable.h"

#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "controls/CPItemComponents.h"
#include "utils/StringUtils.h"
#include "ActivityDataHelper.h"

#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"

MonthGiftPanel::MonthGiftPanel()
	: m_updater(NULL)
{
	m_OptionsList.clear();
}

MonthGiftPanel::~MonthGiftPanel()
{
	
}

bool MonthGiftPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	initFrame();
	initSprite();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();
	initRewards();
	
	return true;
}

void MonthGiftPanel::onCPEvent(const std::string &eventName)
{

}

void MonthGiftPanel::initFrame()
{
	CCSize rewardSize = SystemData::getLayoutSize("monthgift.frame.reward");
	CCPoint rewardPoint = SystemData::getLayoutPoint("monthgift.frame.reward");
	CCScale9Sprite *rewardFrame=SystemData::getScale9SpriteByPlist("guild.menuback",rewardSize.width,rewardSize.height);
	rewardFrame->setAnchorPoint(CCPointZero);  
	rewardFrame->setPosition(rewardPoint); 
	addChild(rewardFrame);	
	rewardFrame->setOpacity(255*0.7);
}
void MonthGiftPanel::initSprite()
{
	CCSprite* sprite1 = SystemData::getSpriteByPlist("monthgift.sprite.qingsongchongzhi");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1);
	CCSprite* sprite2 = SystemData::getSpriteByPlist("monthgift.sprite.jine");
	sprite2->setAnchorPoint(CCPointZero); 
	addChild(sprite2);
	CCSprite* sprite3 = SystemData::getSpriteByPlist("monthgift.sprite.dalibao");
	sprite3->setAnchorPoint(CCPointZero);  
	addChild(sprite3);
	CCSprite* sprite4 = SystemData::getSpriteByPlist("monthgift.sprite.titlebg");
	//sprite4->setAnchorPoint(getSpriteByPlist);
	addChild(sprite4);
	CCSprite* sprite5 = SystemData::getSpriteByPlist("monthgift.sprite.nmonth");
	//sprite5->setAnchorPoint(CCPointZero);
	addChild(sprite5);   
// 	CCSprite* sprite6 = SystemData::getSprite("monthgift.sprite.1888dalibao");
// 	sprite6->setAnchorPoint(CCPointZero);
// 	addChild(sprite6);
	for (int i=0;i<8;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
		CCPoint point = SystemData::getLayoutPoint("monthgift.sprite.item"+StringUtils::toString(i));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point);
		addChild(sprite);
	}
}
void MonthGiftPanel::MenuCallBack(CCObject* pSender)
{
	CCLog("______________%s",__FUNCTION__);
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Button_GoCharge:
			{
				CPEventHelper::openPanel("RechargePanel");
				break;
			}
		case Button_GetReward:
			{
				MsgGetGiftRequest* msg = new MsgGetGiftRequest;
				msg->GiftCate = Gift::gift_recharge_month;
				msg->GiftType = 0;
				HandleMessage::sendMessage(msg);
				break;
			}
		default:
			break;
		}
	}
}

void MonthGiftPanel::initLabels()
{
	CCLabelTTF* label1 = SystemData::getLabelTTF("monthgift.label.qinaidewanjia");
	label1->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label1);

	CCLabelTTF* label2 = SystemData::getLabelTTF("monthgift.label.jike");
	label2->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label2);

	CCLabelTTF* label3 = SystemData::getLabelTTF("monthgift.label.huode");
	label3->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label3);
	/*
	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.browse.title.rank");
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRank); 
	*/  
}

void MonthGiftPanel::initButtons()
{
	CCMenuItemImage* button1 = SystemData::getMenuItemImageByPlist("monthgift.button.gorecharge");
	button1->setTarget(this,menu_selector(MonthGiftPanel::MenuCallBack));
	button1->setAnchorPoint(CCPointZero);
	button1->setTag(Button_GoCharge);
	m_pMainMenu->addChild(button1); 
	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("monthgift.button.getreward");
	button2->setTarget(this,menu_selector(MonthGiftPanel::MenuCallBack));
	button2->setAnchorPoint(CCPointZero);
	button2->setTag(Button_GetReward);
	m_pMainMenu->addChild(button2);
	/*
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",100,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",100,45);
	CCMenuItemSprite *pDetail =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildBrowsePanel::MenuCallBack));//行会信息按钮
	if(pDetail)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.browse.button.detail.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pDetail->setTag(Tag_Detail);
		pDetail->setPosition(SystemData::getLayoutPoint("guild.browse.button.detail"+tail));
		pLabel->setPosition(pDetail->getPosition());
		m_pMainMenu->addChild(pDetail);
		m_pMainMenu->addChild(pLabel);
	}
	*/
}
void MonthGiftPanel::initRewards()
{
	for (int i=0;i<8;i++)
	{
		CCPoint point = SystemData::getLayoutPoint("monthgift.sprite.item"+StringUtils::toString(i));

		int sid = ActivityDataHelper::getItemStaticID(Gift_MonthGift,1,i+1);
		int cnt = ActivityDataHelper::getItemCount(Gift_MonthGift,1,i+1); 
		if (sid>0&&cnt>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setUserData(item);
			//pItem->setTag(i+Item_Start);
			//pItem->setAnchorPoint(CCPointZero);
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(MonthGiftPanel::itemCallBack));
			m_pMainMenu->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_pMainMenu->addChild(pSprite);
		}
	}
}
void MonthGiftPanel::showTooltip(CCMenuItem* pImage)
{
	// show tips
	CCPoint tipsPos = pImage->convertToWorldSpace(ccp(pImage->getContentSize().width,pImage->getContentSize().height-125));
	if(tipsPos.x+245>SystemData::size_x) 
	{
		tipsPos.x -= 245+pImage->getContentSize().width;
	}
	UserItem* userItem = (UserItem*)pImage->getUserData();
	if (userItem->category==ItemCate_Equip)
	{
		tipsPos.y=0;
	}
	Game::getGameUI()->showTipsPanel(userItem,TAG_Tips,tipsPos);
}
void MonthGiftPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}

