#include "FirstChargePanel.h"
#include "EntityDefinition.h"
#include "MsgPlayer.h"
#include "GiftDefinition.h"
#include "EffectDefinition.h"

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

FirstChargePanel::FirstChargePanel()
	: m_updater(NULL)
{
	m_OptionsList.clear();
}

FirstChargePanel::~FirstChargePanel()
{
	
}

bool FirstChargePanel::init()
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

void FirstChargePanel::onCPEvent(const std::string &eventName)
{

}

void FirstChargePanel::initFrame()
{
	CCSize rewardSize = SystemData::getLayoutSize("firstcharge.frame.reward");
	CCPoint rewardPoint = SystemData::getLayoutPoint("firstcharge.frame.reward");
	CCScale9Sprite *rewardFrame=SystemData::getScale9SpriteByPlist("guild.menuback",rewardSize.width,rewardSize.height);
	rewardFrame->setAnchorPoint(CCPointZero);  
	rewardFrame->setPosition(rewardPoint); 
	addChild(rewardFrame);	
	rewardFrame->setOpacity(255*0.7);
}
void FirstChargePanel::initSprite()
{
	CCSprite* sprite5 = SystemData::getSpriteByPlist("firstcharge.sprite.shengyiji");
	sprite5->setAnchorPoint(CCPointZero);
	addChild(sprite5);
	CCSprite* sprite1 = SystemData::getSpriteByPlist("firstcharge.sprite.qingsongchongzhi");
	sprite1->setAnchorPoint(CCPointZero);
	addChild(sprite1);
	CCSprite* sprite2 = SystemData::getSpriteByPlist("firstcharge.sprite.renyijine");
	sprite2->setAnchorPoint(CCPointZero);
	addChild(sprite2);
	CCSprite* sprite3 = SystemData::getSpriteByPlist("firstcharge.sprite.1888yuanbaochongzhidalibao");
	sprite3->setAnchorPoint(CCPointZero);  
	addChild(sprite3);
	CCSprite* sprite4 = SystemData::getSpriteByPlist("firstcharge.sprite.mianfei");
	sprite4->setAnchorPoint(CCPointZero);
	addChild(sprite4);
	CCSprite* sprite6 = SystemData::getSpriteByPlist("firstcharge.sprite.1888dalibao");
	sprite6->setAnchorPoint(CCPointZero);
	addChild(sprite6);
	for (int i=0;i<8;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
		CCPoint point = SystemData::getLayoutPoint("firstcharge.sprite.item"+StringUtils::toString(i));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point);
		addChild(sprite);
	}
}
void FirstChargePanel::initRewards()
{
	for (int i=0;i<8;i++)
	{
		CCPoint point = SystemData::getLayoutPoint("firstcharge.sprite.item"+StringUtils::toString(i));
		
		int sid = ActivityDataHelper::getItemStaticID(Gift_FirstCharge,1,i+1);
		int cnt = ActivityDataHelper::getItemCount(Gift_FirstCharge,1,i+1); 
		if (sid>0&&cnt>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(FirstChargePanel::itemCallBack));
			m_pMainMenu->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_pMainMenu->addChild(pSprite);
		}
	}
}
void FirstChargePanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}
void FirstChargePanel::MenuCallBack(CCObject* pSender)
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
				msg->GiftCate = Gift::gift_recharge_all;
				msg->GiftType = 0;
				HandleMessage::sendMessage(msg);
				break;
			}
		default:
			break;
		}
	}
}

void FirstChargePanel::initLabels()
{
	CCLabelTTF* label1 = SystemData::getLabelTTF("firstcharge.label.qinaidewanjia");
	label1->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label1);

	CCLabelTTF* label2 = SystemData::getLabelTTF("firstcharge.label.jike");
	label2->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label2);

	CCLabelTTF* label3 = SystemData::getLabelTTF("firstcharge.label.huode");
	label3->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label3);

	CCLabelTTF* label4 = SystemData::getLabelTTF("firstcharge.label.bingqie");
	label4->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(label4);
	/*
	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.browse.title.rank");
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRank);
	*/  
}

void FirstChargePanel::initButtons()
{
	CCMenuItemImage* button1 = SystemData::getMenuItemImageByPlist("firstcharge.button.gorecharge");
	button1->setTarget(this,menu_selector(FirstChargePanel::MenuCallBack)); 
	button1->setTag(Button_GoCharge);
	button1->setAnchorPoint(CCPointZero);
	m_pMainMenu->addChild(button1); 
	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("firstcharge.button.getreward");
	button2->setTarget(this,menu_selector(FirstChargePanel::MenuCallBack));
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

void FirstChargePanel::showTooltip(CCMenuItem* pImage)
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