#include "RubbishBagPanel.h"
#include "ext/CCMenuItemTextImage.h"
#include "userdata/SystemData.h"
#include "userdata/ItemOperationDef.h"
#include "scene/panel/functionpanel/BagCellPanel.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "scene/panel/shop/NpcShopComp.h"
#include "MsgItem.h"
#include "network/HandleMessage.h"

RubbishBagPanel::RubbishBagPanel()
{

}

RubbishBagPanel::~RubbishBagPanel()
{

}

bool RubbishBagPanel::init()
{
	if (!PartPanel::init())
	{
		return false;
	}
	initUI();
	return true;
}

bool RubbishBagPanel::initUI()//背包里的垃圾装备ui
{
	m_nHeight=480;
	m_nWidth=320;
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	CCScale9Sprite* pbkg1=SystemData::getScale9SpriteByPlist("activity_spider_bkg",SystemData::getLayoutValue("rubbish_bag_bkg.w"),SystemData::getLayoutValue("rubbish_bag_bkg.h"));
	pbkg1->setPosition(SystemData::getLayoutPoint("rubbish_bag_bkg"));
	pbkg1->setAnchorPoint(CCPointZero);
	addChild(pbkg1);

	CCScale9Sprite* pbkg=SystemData::getScale9SpriteByPlist("activity_spider_bkg",SystemData::getLayoutValue("rubbish_bag_bkg.w"),SystemData::getLayoutValue("rubbish_bag_bkg.h"));
	pbkg->setPosition(SystemData::getLayoutPoint("rubbish_bag_bkg"));
	pbkg->setAnchorPoint(CCPointZero);
	addChild(pbkg);

	addCover(pbkg->getPosition());

	CCLabelTTF* pLabel=SystemData::getLabelTTF("rubbish_bag_text");
	pLabel->setColor(ccWHITE);
	pLabel->setFontSize(18);
	pLabel->setPosition(SystemData::getLayoutPoint("rubbish_bag_text"));
	pbkg->addChild(pLabel);

	BagPanel* pPanel=BagPanel::create(5,4,80,Sell_Bag,Bag_Type_Null);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(ccp(285,-20)); 
	addChild(pPanel);

	initButton();

	return true;
}

void RubbishBagPanel::closecallback( CCObject* pSender )
{
	this->removeFromParent();
}

void RubbishBagPanel::initButton()
{
	GeneralMenu* menu = GeneralMenu::create();
	if (menu)
	{
		menu->setAnchorPoint(CCPointZero);
		menu->setPosition(CCPointZero);
		addChild(menu);
	}
	CCMenuItemImage* pclose=SystemData::getMenuItemImageByPlist("rubbish_bag_close");
	pclose->setTarget(this,menu_selector(RubbishBagPanel::closecallback));
	menu->addChild(pclose);

	CCMenuItemTextImage *pPutOff =  SystemData::getMenuItemTextImage("ui.button",SystemData::getLayoutString("rubbish_oneKey_sell").c_str(),"微软雅黑",15,ccWHITE);
	pPutOff->setTarget(this,menu_selector(RubbishBagPanel::buttonCallBack));
	pPutOff->setTag(oneKeySell);
	pPutOff->setPosition(ccp(345,23));
	menu->addChild(pPutOff);
}

void RubbishBagPanel::buttonCallBack( CCObject* pSender )
{
	std::vector<UserItem*> equipItem;
	equipItem=CommonFunction::getBagItem(Type_rubbish,Sell_Bag);
	if (equipItem.size()>0)
	{
		for(std::vector<UserItem*>::iterator it = equipItem.begin(); it!=equipItem.end(); it++)
		{
			UserItem* pItem= *it;
			MsgItemOperationRequestSell* msgSell = new MsgItemOperationRequestSell;
			msgSell->iid = pItem->iid;
			msgSell->count = pItem->count;
			HandleMessage::sendMessage(msgSell);

			NpcShopComp::_s_state = ItemOperationDefine::item_op_sell;
		}
	}
}

