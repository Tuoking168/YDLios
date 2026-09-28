#include "MergeMainPanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"
#include "scene/Game.h"
#include "scene/GameUI.h"

#include "ext/CCActionDestroy.h"
#include "HSHCpanel.h"
#include "HWTHpanel.h"
#include "WPHCpanel.h"
#include "RoleBag.h"
#include "ForgingMainPanel.h"
#include "CommonFunction.h"
#include "scene/panel/functionPanel/BagCellPanel.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "event/CPEventHelper.h"

MergeMainPanel::MergeMainPanel(void):
	m_iCurrentType(0)
{
}


MergeMainPanel::~MergeMainPanel(void)
{
}


MergeMainPanel* MergeMainPanel::create(int tag)
{
	MergeMainPanel* pPanel = new MergeMainPanel();
	if(pPanel && pPanel->init(tag))
	{
		pPanel->autorelease();
		return pPanel;
	}

	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}

bool MergeMainPanel::init( int tag )
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_iCurrentTopTag=tag;
	m_iCurrentRightTag=-1;



	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="MainPanel")
	{
		int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);
		if (data2>=TAG_LZ && data2<=TAG_HSZH)
		{
			m_iCurrentTopTag=data2;
		}
	}
	/*m_nWidth = SystemData::getLayoutValue("taskcontent_leftmenu_size.w");
	m_nHeight = SystemData::getLayoutValue("taskcontent_leftmenu_size.h");
	addCover(SystemData::getLayoutPoint("ui_func.rightmenu.pos"));*/

	//顶部menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);

	m_pMainMenu=GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	addChild(m_pMainMenu);

	int topTag[TAG_Max1-50]={
		TAG_LZ,TAG_ZSJNS,TAG_ZB,TAG_WP,TAG_CB,TAG_MJS,TAG_HSHC
	};
	 
	std::string topName[TAG_Max1-50]={
		"Merge_LZ","Merge_ZSJNS","Merge_ZB","Merge_WP","Merge_CB","Merge_MJS","Merge_HS"
	};

	int m_MaxCellCount=TAG_Max1-50;
	if (true)
	{
		int n=0;
		for (int i=0;i<m_MaxCellCount;i++)
		{
			if (topTag[i]==TAG_MJS)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<m_MaxCellCount-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[m_MaxCellCount-1]=temp;

		std::string tempstr=topName[n];
		for (int i=n;i<m_MaxCellCount-1;i++)
		{
			topName[i]=topName[i+1];
		}
		topName[m_MaxCellCount-1]=tempstr;

		m_MaxCellCount--;
	}

	//加载顶部按钮
	for (int i=0;i<m_MaxCellCount;i++)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF(topName[i]);
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		CCScale9Sprite *pSprite=SystemData::getScale9SpriteByPlist("forging_select",82,45);
		CCMenuItemSprite *pTopButton=CCMenuItemSprite::create(pSprite,pSprite,NULL,this,menu_selector(MergeMainPanel::menuCallBack));
		pTopButton->setTag(topTag[i]);
		pTopButton->setPosition(ccp(SystemData::getLayoutPoint("forging_top_pos").x+(i)*86,SystemData::getLayoutPoint("forging_top_pos").y));
		pLabel->setPosition(ccp(pTopButton->getPositionX(),pTopButton->getPositionY()));
		m_pTopList->addChild(pTopButton);
		m_pTopList->addChild(pLabel);
	}
	 
	//加载右边界面
	m_pRightMenu=GeneralMenu::create();
	m_pRightMenu->setPosition(CCPointZero);
	addChild(m_pRightMenu);

	m_pBagMenu=GeneralMenu::create();
	m_pBagMenu->setPosition(CCPointZero);
	addChild(m_pBagMenu);
	
	CCScale9Sprite *pRightBorder=SystemData::getScale9SpriteByPlist("forging_border",SystemData::getLayoutValue("forging_bag_size.x"),SystemData::getLayoutValue("forging_bag_size.y"));
	pRightBorder->setPosition(SystemData::getLayoutPoint("forging_rightmenu_pos"));
	pRightBorder->setAnchorPoint(CCPointZero);
	m_pRightMenu->addChild(pRightBorder);


	/*std::string RightName[3]={
		"forging_SSZB","forging_BBWP","forging_CWWP"
	};*/
	std::string RightName[2]={
		"forging_BBWP","forging_CWWP"
	};
	for (int i=0;i<2;i++)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF(RightName[i]);
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		CCMenuItemImage *pRightButton=SystemData::getMenuItemImageByPlist("forging_bag_button");
		pRightButton->setScaleX(1.1);
		pRightButton->setTarget(this,menu_selector(MergeMainPanel::menuCallBack));
		pRightButton->setTag(i+300+1);
		pRightButton->setPosition(ccp(SystemData::getLayoutPoint("merging_rightmenu_button_pos").x+i*120,SystemData::getLayoutPoint("merging_rightmenu_button_pos").y));
		pLabel->setPosition(ccp(pRightButton->getPositionX(),pRightButton->getPositionY()));
		m_pRightMenu->addChild(pRightButton);
		m_pRightMenu->addChild(pLabel);
	}

	m_iCurrentRightTag=TAG_BBWP;

	//加载左边主界面
	updateTopList(m_iCurrentTopTag);

		
	return true;
}

void MergeMainPanel::menuCallBack( CCObject *pSender )
{
	CCLog("Press Down");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag<100 && tag>=0)
		{
			updateTopList(tag);
		}		
		else
		{
			updateRightList(tag,m_iCurrentType);
	    }
	}
}

void MergeMainPanel::updateTopList( int tag )
{
	if(m_iCurrentTopTag>=0)
	{
		int oldtag=m_iCurrentTopTag;
		if (m_iCurrentTopTag==TAG_HSZH)
		{
			oldtag=TAG_HSHC;
		}
		CCMenuItemSprite* pOldItem =(CCMenuItemSprite*)m_pTopList->getChildByTag(oldtag);
		CCScale9Sprite *pSprite=SystemData::getScale9SpriteByPlist("forging_select",82,45);
		pOldItem->setNormalImage(pSprite);//变为未选中
	}
 
	CCMenuItemSprite* pItem =(CCMenuItemSprite*)m_pTopList->getChildByTag(tag);
	CCScale9Sprite *pSprite1=SystemData::getScale9SpriteByPlist("forging_is_selected",82,45);
	pItem->setNormalImage(pSprite1);//变为选中

	
	addTopFunc(tag);

}

void MergeMainPanel::addTopFunc( int tag )//加载子panel
{
	//删除已有的panel
	if (m_iCurrentTopTag!=-1)
	{
		removeChildByTag(m_iCurrentTopTag);
	}	
	m_iCurrentTopTag=tag;
	CCNode* panel = NULL;
	//加载新panel
	switch (tag)
	{
	case TAG_LZ:
		panel=WPHCpanel::create(TAG_LingZhu);
		m_iCurrentType=TYPE_LingZhu;
		break;
	case TAG_ZSJNS:
		panel=WPHCpanel::create(TAG_JiNengShu);
		m_iCurrentType=TYPE_JiNengShu;
		break;
	case TAG_ZB:
		panel=WPHCpanel::create(TAG_ZhuangBei);
		m_iCurrentType=TYPE_XunZhang;
		break;
	case TAG_WP:
		panel=WPHCpanel::create(TAG_WuPin);
		m_iCurrentType=TYPE_DaoJu;
		break;
	case TAG_CB:
		panel=WPHCpanel::create(TAG_ChiBang);
		m_iCurrentType=TYPE_ChiBang;
		break;
	case TAG_MJS:
		panel=WPHCpanel::create(TAG_MoJingShi);
		m_iCurrentType=TYPE_MoJingShi;
		break;
	case TAG_HSHC:
		panel=HSHC_HSHCpanel::create();
		m_iCurrentType=TYPE_HunShi;
		break;
	case TAG_HSZH:
		panel=HSHC_HSZHpanel::create();
		m_iCurrentType=TYPE_HunShiZH;
		break;
	default:
		break;
	}
	if (panel)
	{
		panel->setTag(m_iCurrentTopTag);
		panel->setAnchorPoint(CCPointZero);
		addChild(panel);

		//更新背包
		updateRightList(m_iCurrentRightTag,m_iCurrentType);

	}
}


void MergeMainPanel::updateRightList( int tag ,int type)
{
	if (m_iCurrentRightTag!=-1)
	{
		m_pBagMenu->removeChildByTag(m_iCurrentRightTag);
	}
	m_iCurrentRightTag=tag;

	//按钮变更
	reloadRightButton();
	BagCellPanel* panel = NULL;
	CCMenuItemSprite *pItem=NULL;
	
	pItem=(CCMenuItemSprite *)m_pRightMenu->getChildByTag(tag);
	CCSprite* pSprite=SystemData::getSpriteByPlist("forging_bag_button.sel");
	pItem->setNormalImage(pSprite);

	//panel=RoleBag::create(tag ,type);
	int type1=Self_Bag;
	int x=5;
	int y=4;
	int count=80;
	switch (m_iCurrentRightTag)
	{
	case TAG_SSZB:
		type1=Role_Bag;
		count=20;
		break;
	case TAG_BBWP:
		type1=Self_Bag;
		break;
	case TAG_CWWP:
		type1=Pet_Bag;
		break;
	default:
		break;
	}
	panel=BagCellPanel::create(x,y,count,type1,Bag_Type_ItemEx2);
	panel->setPosition(ccp(SystemData::getLayoutPoint("forging_rightmenu_pos").x,SystemData::getLayoutPoint("forging_rightmenu_pos").y-60));
	
	//背包内容变更
	if (panel)
	{
		panel->setTag(m_iCurrentRightTag);
		panel->setAnchorPoint(CCPointZero);
		m_pBagMenu->addChild(panel);
		panel->setCurVisibleType(type);
	}
}

void MergeMainPanel::reloadRightButton()
{
	for (int i=1;i<3;i++)
	{
		CCMenuItemSprite *pItem=(CCMenuItemSprite *)m_pRightMenu->getChildByTag(i+300);
		CCSprite* pSprite=SystemData::getSpriteByPlist("forging_bag_button");
		pItem->setNormalImage(pSprite);
	}
}


void MergeMainPanel::PostNotic(UserItem* pObject)
{
	switch (m_iCurrentTopTag)
	{
	case TAG_LZ:
		((WPHCpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_ZSJNS:
		((WPHCpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_WP:
		((WPHCpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;	
	case TAG_ZB:
		((WPHCpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_CB:
		((WPHCpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_MJS:
		((WPHCpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_HSHC:		
		((HSHC_HSHCpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);			
		break;	
	case TAG_HSZH:
		((HSHC_HSZHpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	default:
		break;
	}
}
