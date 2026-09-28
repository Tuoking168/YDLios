#include "NpcShopComp.h"
#include "NpcShopPanel.h"
#include "userdata/SystemData.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "ext/RadioGroup.h"
#include "scene/panel/ForgingPanel/RoleBag.h"
#include "userdata/ItemOperationDef.h"
#include "network/HandleMessage.h"
#include "MsgShop.h"
#include "ModuleData.h"
#include "userdata/LayoutData.h"
#include "event/CPEventHelper.h"
#include "logic/BagOperator.h"

NpcShopComp::NpcShopComp()
	: m_pNpcShopPanel(NULL)
	, m_pBagPanel(NULL)
	, m_pBagTab(NULL)
	, m_pPetBagTab(NULL)
	, m_pEquipedTab(NULL)
{

}

NpcShopComp::~NpcShopComp()
{

}

bool NpcShopComp::init()//随身商店ui
{
	if (!CCLayer::init())
	{
		return false;
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	int shopID = TAG_NPCSHOP_MEDICINE;
	const std::string &openPanel = CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (openPanel == "NpcShopComp")
	{
		shopID = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
	}
	
	// 添加背景
	CCScale9Sprite *bkg = LayoutData::getScale9Sprite(CPModuleName::COMMON, "bkg");
	addChild(bkg);

	m_nWidth = bkg->getContentSize().width;
	m_nHeight = bkg->getContentSize().height;
	addCover();//swallow the touch event in case of leaking to the map layer

	// 添加顶部Bar
	CCScale9Sprite *topbar = LayoutData::getScale9Sprite(CPModuleName::COMMON, "titleBoard");
	addChild(topbar);

	//add the left NPC shop panel
	m_pNpcShopPanel = NpcShopPanel::create(shopID);
	m_pNpcShopPanel->setPosition(CCPointZero);
	addChild(m_pNpcShopPanel);	

	//add the right backpack panels and so on
	//add the bag panel
	m_pBagPanel = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPlayerBagSlot"),Self_Bag,Bag_Type_Npcshop);
	m_pBagPanel->setPosition(ccp(487,8));
	m_pBagPanel->setTag(TAG_NPC_COMP_BAG);
	addChild(m_pBagPanel);

	//add the close button
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("npcshop.common.close");
	pClose->setTarget(this,menu_selector(NpcShopPanel::closeCallBack));
	CCMenu* pMenu = CCMenu::create(pClose,NULL);
	pMenu->setPosition(CCPointZero);
	pMenu->setTouchPriority(kCCMenuHandlerPriority-1);
	addChild(pMenu);

	//add the top buttons
	RadioGroup* pTopMenu = RadioGroup::create();
	pTopMenu->setPosition(CCPointZero);
	addChild(pTopMenu);
	CCMenuItem** pTabArr[3] = {&m_pBagTab,&m_pPetBagTab,&m_pEquipedTab};
	std::string lblKey[3] = {"bag","petbag","equiped"};
	int	tagArr[3] = {TAG_NPC_COMP_BAG,TAG_NPC_COMP_PET_BAG,TAG_NPC_COMP_EQUIPTED};
	for (int i=0; i<2; i++)
	{
		CCMenuItemImage* pItem = SystemData::getMenuItemImageByPlist("npcshop.common.btn."+lblKey[i]);
		if (i>0)
		{
			CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("npcshop.common.btn."+lblKey[i],105,45);
			p1->setAnchorPoint(CCPointZero);
			p1->setPosition(CCPointZero); 
			pItem->setNormalImage(p1);
			CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("npcshop.common.btn."+lblKey[i]+".sel",105,45);
			pItem->setSelectedImage(p2);
		}
		pItem->setPositionY(pItem->getPositionY()-5);
		pItem->setTag(tagArr[i]);
		pItem->setTarget(this,menu_selector(NpcShopComp::tabCallback));
		pTopMenu->addChild(pItem);
		CCLabelTTF* pLabel = SystemData::getLabelTTF("npcshop.common.lbl."+lblKey[i]);
		pLabel->setPosition(ccp(pItem->getContentSize().width/2,pItem->getContentSize().height/3));
		pLabel->setFontName("Consolas");
		pLabel->setFontSize(20);
		pItem->addChild(pLabel);
		*(pTabArr[i]) = pItem;
		if (i==0)
		{
			pItem->selected();  
		}
	}

	//add the bottom buttons	
	if (shopID!=TAG_NPCSHOP_CARRY)
	{
		RadioGroup* pBottomMenu = RadioGroup::create();
		pBottomMenu->setPosition(CCPointZero);
		pBottomMenu->setTouchPriority(kCCMenuHandlerPriority-1);
		addChild(pBottomMenu);
		std::string btnarr[2] = {"fix","fixall"};
		int tag[2] = {TAG_SHOP_FIX,TAG_SHOP_FIXALL};
		for(int i=1; i<2; i++)
		{
			std::string key = "npcshop."+btnarr[i];
			CCMenuItemImage* pBtn = SystemData::getMenuItemImageByPlist(key);
			if (i==1)
			{
				CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist(key,105,48);
				p1->setAnchorPoint(CCPointZero);
				p1->setPosition(CCPointZero); 
				pBtn->setNormalImage(p1);   
				CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist(key+".sel",105,48);
				pBtn->setSelectedImage(p2);
			}    
			key = "npcshop.lbl."+btnarr[i];
			pBtn->setPosition(SystemData::getLayoutPoint(key)); 
			CCLabelTTF* pLabel = SystemData::getLabelTTF(key);
			pLabel->setPosition(ccp(pBtn->getContentSize().width/2,pBtn->getContentSize().height/2));
			pBtn->addChild(pLabel);
			pBtn->setTag(tag[i]); 
			pBtn->setTarget(this,menu_selector(NpcShopComp::bottomBtnCallback));
			if(i == 0 || i==2)
			{ 
				pBottomMenu->addChild(pBtn);
			}
			else
			{
				pMenu->addChild(pBtn);
			}
		}
	}
	setTouchEnabled(true);

	return true;
}

void NpcShopComp::hide()
{
	//send the shop closing message
	MsgCloseShopRequest* msg = new MsgCloseShopRequest;
	HandleMessage::sendMessage(msg);
	this->removeFromParent();
}

void NpcShopComp::tabCallback( CCObject* pSender )
{
	CCNode* pNode = (CCNode*)pSender;
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_NPC_COMP_BAG:
			if (m_pBagPanel->getTag()==TAG_NPC_COMP_BAG)
			{
				break;
			}

			this->removeChild(m_pBagPanel);
			m_pBagPanel=NULL;
			m_pBagPanel = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPlayerBagSlot"),Self_Bag,Bag_Type_Npcshop);
			m_pBagPanel->setTag(TAG_NPC_COMP_BAG);
			m_pBagPanel->setPosition(ccp(487,8));
			addChild(m_pBagPanel); 

			setBagVisibility(false);
			m_pBagTab->selected();
			//setBagVisibility(true);
			//setPetBagVisibility(false);
			break;
		case TAG_NPC_COMP_PET_BAG:
			if (m_pBagPanel->getTag()==TAG_NPC_COMP_PET_BAG)
			{
				break;
			}

			this->removeChild(m_pBagPanel);
			m_pBagPanel=NULL;
			m_pBagPanel = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPetBagSlot"),Pet_Bag,Bag_Type_Npcshop);
			m_pBagPanel->setTag(TAG_NPC_COMP_PET_BAG);
			m_pBagPanel->setPosition(ccp(487,8));
			addChild(m_pBagPanel); 

			setBagVisibility(false);
			m_pPetBagTab->selected();
			//setPetBagVisibility(true);
			//setBagVisibility(false);
			break;
		case TAG_NPC_COMP_EQUIPTED:
			if (m_pBagPanel->getTag()==TAG_NPC_COMP_EQUIPTED)
			{
				break;
			}
			this->removeChild(m_pBagPanel);
			m_pBagPanel=NULL;
			m_pBagPanel = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPlayerBagSlot"),Role_Bag,Bag_Type_Npcshop);
			m_pBagPanel->setTag(TAG_NPC_COMP_EQUIPTED);
			m_pBagPanel->setPosition(ccp(487,8));
			addChild(m_pBagPanel); 
			break;
		default:
			break;
		}
	}
}

void NpcShopComp::bottomBtnCallback( CCObject* pSender )
{
	///TODO:finish the fix,fixall,and sell logic
	CCMenuItemImage* pNode = (CCMenuItemImage*)pSender;
	if(pNode)
	{
		int tag = pNode->getTag();
//		CCMenuItemImage* pSellNode = (CCMenuItemImage*)getChildByTag(TAG_SHOP_SELL);
//		CCMenuItemImage* pFixNode = (CCMenuItemImage*)getChildByTag(TAG_SHOP_FIX);
//		if(pFixNode)
//		{
//			pFixNode->unselected();
//		}
//		if(pSellNode)
//		{
//			pSellNode->unselected();
//		}
		switch (tag)
		{
		/*case TAG_SHOP_SELL:
			_s_state = ItemOperationDefine::item_op_sell;
			m_pBagTab->setEnabled(true);
			setBagVisibility(true);
			setPetBagVisibility(true);
			setEquipedVisibility(false);
			m_pPetBagPanel->setVisible(false);
//			pSellNode->selected();
//			pFixNode->unselected();
			break;*/
		case TAG_SHOP_FIX:
			_s_state = ItemOperationDefine::item_op_fix;
			/*m_pEquipedTab->setEnabled(false);
			setBagVisibility(false);
			setPetBagVisibility(false);
			setEquipedVisibility(true);*/
//			pFixNode->selected();
//			pSellNode->unselected();
			break;
		case TAG_SHOP_FIXALL:
			///TODO:send a message,and show a tips when got response

		//	BagOperator::StartDoRepairItem();
			BagOperator::RepairAllFromServer(ItemRepair_Money);
			_s_state = ItemOperationDefine::item_op_buy;
			/*setBagVisibility(true);
			m_pBagTab->setEnabled(false);
			setPetBagVisibility(false);
			setEquipedVisibility(false);*/
			break;
		default:
			break;
		}
	}
}

void NpcShopComp::setBagVisibility( bool visible )
{
	m_pBagTab->unselected();
	m_pPetBagTab->unselected();
}

void NpcShopComp::setPetBagVisibility( bool visible )
{
	m_pPetBagTab->setVisible(visible);
	m_pPetBagTab->selected();
}

void NpcShopComp::setEquipedVisibility( bool visible )
{
	m_pRoleBagPanel->setVisible(visible);
}

int NpcShopComp::_s_state = ItemOperationDefine::item_op_buy;

