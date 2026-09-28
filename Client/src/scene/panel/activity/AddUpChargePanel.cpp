#include "AddUpChargePanel.h"
#include "EntityDefinition.h"
#include "WorldDefinition.h"
#include "MsgPlayer.h"
#include "GiftDefinition.h"
#include "EffectDefinition.h"
#include "ActivityDataHelper.h"
#include "ModuleData.h"
#include "MainUIModule.h"

#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "userdata/ActivityData.h"
#include "userdata/LayoutData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/GameRole.h"

#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"
#include "ext/CCActionDestroy.h"
#include "ext/GeneralMenu.h"
#include "ext/CCMenuEx.h"

#include "network/HandleMessage.h"

#include "scene/SlideTable.h"
#include "scene/ConfirmPrompt.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "scene/panel/guide/GuideHelper.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"

#include "controls/CPItemComponents.h"

#include "utils/StringUtils.h"

#include "res/CPAnimationManager.h"



///////////AddUpChargePanel///////////////////////////////////////////////
AddUpChargePanel::AddUpChargePanel()
	: m_updater(NULL)
	, m_InfoMainNode(NULL)
	,mPanLongNeedGoldLabel(NULL)
{
	m_OptionsList.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

AddUpChargePanel::~AddUpChargePanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool AddUpChargePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	initFrame();

	//Ö÷Òªmenu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_pMainMenu);

	initLabels();
	initButtons();

	if (GuideHelper::canOpenFunction(WorldDefination::pan_long_bao_xiang))
	{
		initPanLongReward();
	}

	m_InfoMainNode = CCNode::create();
	m_InfoMainNode->setPosition(CCPointZero);
	m_InfoMainNode->setAnchorPoint(CCPointZero);
	addChild(m_InfoMainNode);

	m_InfoMainMenu = GeneralMenu::create();
	m_InfoMainMenu->setPosition(CCPointZero);
	m_InfoMainMenu->setAnchorPoint(CCPointZero);
	addChild(m_InfoMainMenu);

	refreshInfo(getGiftRewardCurrentIndex());
	
	return true;
}

void AddUpChargePanel::initPanLongReward()
{
	CCLabelTTF *panlongLable = SystemData::getLabelTTF("addupcharge.label.panlongbaoxiang");
	addChild(panlongLable);

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	const int sid = SystemData::getLayoutValue("addupcharge.value.panlongbaoxiang.sid");
	CCMenuItemSprite *boxBtn = CCMenuItemSprite::create(
		SystemData::getSpriteByPlist("activity.sprite.item.frame")
		, SystemData::getSpriteByPlist("activity.sprite.item.frame"));
	boxBtn->setTarget(this, menu_selector(AddUpChargePanel::onBoxItem));
	boxBtn->setPosition(SystemData::getLayoutPoint("addupcharge.point.panlongbaoxiang.box"));
	menu->addChild(boxBtn, 0, sid);

	CCSprite *boxIcon = LayoutData::getItemIcon(sid);
	boxIcon->setPosition(LayoutData::getCenter(boxBtn->getContentSize()));
	boxBtn->addChild(boxIcon);

	mPanLongNeedGoldLabel = SystemData::getLabelTTF("addupcharge.label.panlongbaoxiang.need");
	addChild(mPanLongNeedGoldLabel);
}

int AddUpChargePanel::getGiftRewardMinIndex()
{
	const int giftIndexData = HeroData::getProp(Entity::attr_recharge_gift);
	int mark = 1;
	for (int i = 0; i < 32; i++)
	{
		mark = 1 << i;
		if ((giftIndexData & mark) == 0)
		{
			return i;
		}
	}
	return 0;
}

int AddUpChargePanel::getGiftRewardCurrentIndex()
{
	const int rechargeMoney = HeroData::getProp(Entity::attr_recharge_money);
	const int rewardSize = ActivityDataHelper::getRewardsSize(Gift_AddUpCharge);
	int vPhase = 1;
	for (int i = 1; i <= rewardSize; i++)
	{
		int datax = ActivityDataHelper::getDataX(Gift_AddUpCharge, i);
		if (rechargeMoney<datax)
		{
			vPhase = i;
			break;
		}
	}
	return vPhase;
}

void AddUpChargePanel::refreshInfo(int vPhase)
{
	m_InfoMainNode->removeAllChildren();

	CCSprite* sprite1 = SystemData::getSpriteByPlist("addupcharge.sprite.qingsongchongzhi");
	sprite1->setAnchorPoint(CCPointZero);
	m_InfoMainNode->addChild(sprite1);

	CCLabelTTF* label1 = SystemData::getLabelTTF("addupcharge.label.qinaidewanjia");
	label1->setHorizontalAlignment(kCCTextAlignmentLeft); 
	m_InfoMainNode->addChild(label1);
	CCLabelTTF* label2 = SystemData::getLabelTTF("addupcharge.label.jike");
	label2->setHorizontalAlignment(kCCTextAlignmentLeft); 
	m_InfoMainNode->addChild(label2);
	CCLabelTTF* label3 = SystemData::getLabelTTF("addupcharge.label.huode");
	label3->setHorizontalAlignment(kCCTextAlignmentLeft); 
	m_InfoMainNode->addChild(label3);

	const int rechargeMoney = HeroData::getProp(Entity::attr_recharge_money);
	const int datax = ActivityDataHelper::getDataX(Gift_AddUpCharge, vPhase);

	const std::string &path = LayoutData::getString(CPModuleName::MAIN_UI, "lvlUpNum");
	const CCSize &size = LayoutData::getSize(CPModuleName::MAIN_UI, "lvlUpNum");
	CCLabelAtlas *label = CCLabelAtlas::create(StringUtils::toString(datax-rechargeMoney).c_str(), path.c_str(), size.width, size.height, '0');
	label->setAnchorPoint(ccp(0.5f, 0));
	label->setPosition(SystemData::getLayoutPoint("addupcharge.sprite.goldenough"));
	m_InfoMainNode->addChild(label);
	label->setScale(0.4f);

	//
	const int ten = (vPhase + 1)/10;
	const int bits = (vPhase + 1)%10;
	std::string wordStr;
	if (ten > 0)
	{
		wordStr += "0";
	}

	if (bits > 0)
	{
		wordStr += StringUtils::toString(bits);
	}
	
	const std::string &wordPath = LayoutData::getString(CPModuleName::COMMON, "wordNumber");
	const CCSize &wordSize = LayoutData::getSize(CPModuleName::COMMON, "wordNumber");
	CCLabelAtlas *wordLabel = CCLabelAtlas::create(wordStr.c_str(), wordPath.c_str(), wordSize.width, wordSize.height, '0');
	wordLabel->setPosition(SystemData::getLayoutPoint("addupcharge.sprite.phase"));
	m_InfoMainNode->addChild(wordLabel);

	CCSprite* sprite7 = SystemData::getSpriteByPlist("addupcharge.sprite.phasegift");  
	sprite7->setAnchorPoint(CCPointZero);
	sprite7->setPositionX(wordLabel->getPositionX() + wordLabel->getContentSize().width);
	m_InfoMainNode->addChild(sprite7);
	
	CCLabelTTF* label6 = SystemData::getLabelTTF("addupcharge.label.hasrecharge");
	label6->setHorizontalAlignment(kCCTextAlignmentLeft); 
	m_InfoMainNode->addChild(label6);   
	std::string str1 = SystemData::getLayoutString("addupcharge.label.hasrecharge");
	std::string str2 = SystemData::getLayoutString("addupcharge.label.hasrecharge.yuanbao");
	label6->setString((str1+StringUtils::toString(rechargeMoney)+str2).c_str()); 

	if (mPanLongNeedGoldLabel)
	{
		const int perGold = SystemData::getLayoutValue("addupcharge.value.panlongbaoxiang.gold");
		const int needGold = perGold - (rechargeMoney%perGold);
		char ch[256];
		sprintf(ch, SystemData::getLayoutString("addupcharge.label.panlongbaoxiang.need").c_str(), needGold);
		mPanLongNeedGoldLabel->setString(ch);
	}

	refreshRewards();
}

void AddUpChargePanel::initFrame()
{
	const CCSize &rewardSize = SystemData::getLayoutSize("addupcharge.frame.reward");
	const CCPoint &rewardPoint = SystemData::getLayoutPoint("addupcharge.frame.reward");
	CCScale9Sprite *rewardFrame=SystemData::getScale9SpriteByPlist("guild.menuback",rewardSize.width,rewardSize.height);
	rewardFrame->setAnchorPoint(CCPointZero);  
	rewardFrame->setPosition(rewardPoint); 
	addChild(rewardFrame);	
	rewardFrame->setOpacity(255*0.7f);

	CCSprite* sprite6 = SystemData::getSpriteByPlist("addupcharge.sprite.jieduanchongzhi");
	sprite6->setAnchorPoint(CCPointZero);
	addChild(sprite6);
}

void AddUpChargePanel::MenuCallBack(CCObject* pSender)
{
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
				msg->GiftType = getGiftRewardMinIndex();
				HandleMessage::sendMessage(msg);
				break;
			}
		default:
			break;
		}
	}
}

void AddUpChargePanel::initLabels()
{
	CCLabelTTF* noteLabel = SystemData::getLabelTTF("addupcharge.label.notice");
	noteLabel->setDimensions(CCSizeMake(175, 175));
	noteLabel->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(noteLabel);
}

void AddUpChargePanel::initButtons()
{
	CCMenuItemImage* button1 = SystemData::getMenuItemImageByPlist("addupcharge.button.gorecharge");
	button1->setTarget(this,menu_selector(AddUpChargePanel::MenuCallBack));
	button1->setAnchorPoint(CCPointZero);
	button1->setTag(Button_GoCharge);
	m_pMainMenu->addChild(button1); 
	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("addupcharge.button.getreward");
	button2->setTarget(this,menu_selector(AddUpChargePanel::MenuCallBack));
	button2->setAnchorPoint(CCPointZero);
	button2->setTag(Button_GetReward);
	m_pMainMenu->addChild(button2);
}

void AddUpChargePanel::refreshRewards()
{
	m_InfoMainMenu->removeAllChildren();

	int giftIndex = getGiftRewardMinIndex();
	if (giftIndex <= 0)
	{
		giftIndex = 1;
	}

	const int rewardCnt = 9;
	const std::string &ptKey = "addupcharge.sprite.item";
	for (int i = 0; i < rewardCnt; i++)
	{
		const int sid = ActivityDataHelper::getItemStaticID(Gift_AddUpCharge, giftIndex, i + 1);
		const int cnt = ActivityDataHelper::getItemCount(Gift_AddUpCharge, giftIndex, i + 1); 
		if (sid > 0
			&& cnt > 0)
		{
			const CCPoint &point = SystemData::getLayoutPoint(ptKey + StringUtils::toString(i));

			CCSprite* board = SystemData::getSpriteByPlist("activity.sprite.item.frame");
			board->setAnchorPoint(CCPointZero);
			board->setPosition(point);
			m_InfoMainMenu->addChild(board);

			const CCSize &size = board->getContentSize();
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(item);
			pItem->setPosition(ccp(point.x + size.width/2, point.y + size.height/2));
			pItem->setTarget(this, menu_selector(AddUpChargePanel::itemCallBack));
			m_InfoMainMenu->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_InfoMainMenu->addChild(pSprite);
		}
	}
}

void AddUpChargePanel::showTooltip(CCMenuItem* pImage)
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

void AddUpChargePanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}

void AddUpChargePanel::onBoxItem( CCObject *target )
{
	CCNode *node = dynamic_cast<CCNode *>(target);
	if (node)
	{
		ItemTooltip *tips = ItemTooltip::create();
		tips->setTooltipContentbysid(node->getTag());
		tips->setPositionX(node->getPositionX());
		tips->setPositionY(node->getPositionY() - tips->getContentSize().height);
		addChild(tips);
	}
}

void AddUpChargePanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			const int type = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			if (type == Entity::attr_recharge_money
				|| type == Entity::attr_recharge_gift)
			{
				refreshInfo(getGiftRewardCurrentIndex());
			}
		}
	}
}
