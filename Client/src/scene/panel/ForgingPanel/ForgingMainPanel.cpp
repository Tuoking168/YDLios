#include "ForgingMainPanel.h"
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
#include "ZBSJpanel.h"
#include "HWpanel.h"
#include "SXZYpanel.h"
#include "ZBJDpanel.h"
#include "ZBQHpanel.h"
#include "ZSDZpanel.h"
#include "ZBFMpanel.h"
#include "RoleBag.h"
#include "CommonFunction.h"
#include "scene/panel/functionPanel/BagCellPanel.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "scene/panel/guide/GuideHelper.h"
#include "event/CPEventHelper.h"
#include "userdata/LayoutData.h"

ForgingMainPanel::ForgingMainPanel(void):
	m_iCurrentType(0)
{
	
}


ForgingMainPanel::~ForgingMainPanel(void)
{
	
}


ForgingMainPanel* ForgingMainPanel::create(int type)
{
	ForgingMainPanel* pPanel = new ForgingMainPanel();
	if(pPanel && pPanel->init(type))
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

bool ForgingMainPanel::init( int type )
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_iCurrentTopTag=-1;
	m_iCurrentRightTag=-1;


	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="MainPanel")
	{
		int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);
		if (data2>=TAG_ZBSJ && data2<=TAG_Max2)
		{
			type=data2;

		}
	}
	/*m_nWidth = SystemData::getLayoutValue("taskcontent_leftmenu_size.w");
	m_nHeight = SystemData::getLayoutValue("taskcontent_leftmenu_size.h");
	addCover(SystemData::getLayoutPoint("ui_func.rightmenu.pos"));*/

	//顶部menu
	m_pTopList=GeneralMenu::create();
	m_pTopList->setPosition(CCPointZero);
	addChild(m_pTopList);
	

	std::string topName[TAG_Max2]={
		"forging_ZBQH","forging_ZBJD","forging_ZBSJ","forging_HWQL","forging_SXZY","forging_ZSDZ","forging_ZBFM"
	};

	int topTag[TAG_Max2]={
		TAG_ZBQH,TAG_ZBJD,TAG_ZBSJ,TAG_HWTH,TAG_SXZY,TAG_ZSDZ,TAG_ZBFM,
	};

	int m_MaxCellCount=TAG_Max2;
	if (!GuideHelper::canOpenFunction(FunctionName::HUAN_WU_QI_LING))
	{
		int n=0;
		for (int i=0;i<TAG_Max2;i++)
		{
			if (topTag[i]==TAG_HWTH)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max2-1]=temp;

		std::string tempstr=topName[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topName[i]=topName[i+1];
		}
		topName[TAG_Max2-1]=tempstr;

		m_MaxCellCount--;
	}

	if (!GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_JIAN_DING))
	{
		int n=0;
		for (int i=0;i<TAG_Max2;i++)
		{
			if (topTag[i]==TAG_ZBJD)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max2-1]=temp;

		std::string tempstr=topName[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topName[i]=topName[i+1];
		}
		topName[TAG_Max2-1]=tempstr;

		m_MaxCellCount--;
	}
	if (!GuideHelper::canOpenFunction(FunctionName::SHU_XING_ZHUAN_YI))
	{
		int n=0;
		for (int i=0;i<TAG_Max2;i++)
		{
			if (topTag[i]==TAG_SXZY)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max2-1]=temp;

		std::string tempstr=topName[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topName[i]=topName[i+1];
		}
		topName[TAG_Max2-1]=tempstr;

		m_MaxCellCount--;
	}
	if (!GuideHelper::canOpenFunction(FunctionName::ZHUAN_SHENG_DUAN_ZAO))
	{
		int n=0;
		for (int i=0;i<TAG_Max2;i++)
		{
			if (topTag[i]==TAG_ZSDZ)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max2-1]=temp;

		std::string tempstr=topName[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topName[i]=topName[i+1];
		}
		topName[TAG_Max2-1]=tempstr;

		m_MaxCellCount--;
	}
	if (!GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_SHENG_JI))
	{
		int n=0;
		for (int i=0;i<TAG_Max2;i++)
		{
			if (topTag[i]==TAG_ZBSJ)
			{
				n=i;
				break;
			}
		}
		int temp=topTag[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topTag[i]=topTag[i+1];
		}
		topTag[TAG_Max2-1]=temp;

		std::string tempstr=topName[n];
		for (int i=n;i<TAG_Max2-1;i++)
		{
			topName[i]=topName[i+1];
		}
		topName[TAG_Max2-1]=tempstr;

		m_MaxCellCount--;
	}

	const int top_btn_interval = SystemData::getLayoutValue("forging_top_btn_interval");	// 间距
	const CCSize &top_btn_size = SystemData::getLayoutSize("forging_top_btn_size");
	//加载顶部按钮
	for (int i=0;i<m_MaxCellCount;i++)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF(topName[i]);
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		
		CCScale9Sprite *pSprite=SystemData::getScale9SpriteByPlist("forging_select", top_btn_size.width, top_btn_size.height);
		CCMenuItemSprite *pTopButton=CCMenuItemSprite::create(pSprite, pSprite, NULL, this, menu_selector(ForgingMainPanel::menuCallBack));
		pTopButton->setTag(topTag[i]);
		pTopButton->setPosition(ccp(SystemData::getLayoutPoint("forging_top_pos").x + i * (top_btn_size.width + top_btn_interval), SystemData::getLayoutPoint("forging_top_pos").y - 1));
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
	 

	std::string RightName[3]={
		"forging_SSZB","forging_BBWP","forging_CWWP"
	};
	for (int i=0;i<3;i++)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF(RightName[i]); 
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		CCMenuItemImage *pRightButton=SystemData::getMenuItemImageByPlist("forging_bag_button");
		pRightButton->setScaleX(1.1);
		pRightButton->setTarget(this,menu_selector(ForgingMainPanel::menuCallBack));
		pRightButton->setTag(i+300);
		pRightButton->setPosition(ccp(SystemData::getLayoutPoint("forging_rightmenu_button_pos").x+i*103,SystemData::getLayoutPoint("forging_rightmenu_button_pos").y));
		pLabel->setPosition(ccp(pRightButton->getPositionX(),pRightButton->getPositionY()));
		m_pRightMenu->addChild(pRightButton);
		m_pRightMenu->addChild(pLabel);
	}
	m_iCurrentRightTag=TAG_SSZB;
	
	//加载左边主界面
	updateTopList(type);
		
	return true;
}

void ForgingMainPanel::menuCallBack( CCObject *pSender )
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

void ForgingMainPanel::updateTopList( int tag )
{
	if (m_iCurrentTopTag==tag)
	{
		return;
	}
	else
	{
		const CCSize &top_btn_size = SystemData::getLayoutSize("forging_top_btn_size");

		CCMenuItemSprite* pItem =(CCMenuItemSprite*)m_pTopList->getChildByTag(tag);
		if (pItem)
		{
			CCScale9Sprite *pSprite1=SystemData::getScale9SpriteByPlist("forging_is_selected", top_btn_size.width, top_btn_size.height);
			pItem->setNormalImage(pSprite1);//变为选中
		}


		if(m_iCurrentTopTag>=0)
		{
			CCMenuItemSprite* pOldItem =(CCMenuItemSprite*)m_pTopList->getChildByTag(m_iCurrentTopTag);
			CCScale9Sprite *pSprite=SystemData::getScale9SpriteByPlist("forging_select", top_btn_size.width, top_btn_size.height);
			if (pOldItem)
			{
				pOldItem->setNormalImage(pSprite);//变为未选中
			}
		}
		addTopFunc(tag);
	}
}

void ForgingMainPanel::addTopFunc( int tag )//加载子panel
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
	case TAG_ZBSJ:
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_SHENG_JI))
		{
			panel=ZBSJpanel::create();
			m_iCurrentType=TYPE_ZBSJ;
		}
		break;
	case TAG_ZBQH:
		panel=ZBQHpanel::create();
		m_iCurrentType=TYPE_ZBQH;
		panel->setPosition(ccp(0,-40));
		break;
	case TAG_ZBJD:
		if(GuideHelper::canOpenFunction(FunctionName::ZHUANG_BEI_JIAN_DING))
		{
			panel=ZBJDpanel::create();
			m_iCurrentType=TYPE_ZBJD;
		}
		break;	
	case TAG_ZSDZ:
		if(GuideHelper::canOpenFunction(FunctionName::ZHUAN_SHENG_DUAN_ZAO))
		{
			panel=ZSDZpanel::create();
			m_iCurrentType=TYPE_ZSDZ;
		}
		break;	
	case TAG_SXZY:
		if(GuideHelper::canOpenFunction(FunctionName::SHU_XING_ZHUAN_YI))
		{
			panel=SXZYPanel::create();
			m_iCurrentType=TYPE_JPZY;//默认极品转移
		}
		break;
	case TAG_HWTH:
		panel=HWpanel::create();
		m_iCurrentType=TYPE_HWTH;
		break;
	case  TAG_ZJTH:
		panel=HWpanel::create();
		m_iCurrentType=TYPE_ZJTH;
		break;
	case TAG_JPZY:
		panel=SXZYPanel::create(TAG_JPZY);
		m_iCurrentType=TYPE_JPZY;//默认极品转移
		break;
	case TAG_QHZY:
		panel=SXZYPanel::create(TAG_QHZY);
		m_iCurrentType=TYPE_QHZY;
		break;
	case TAG_JDZY:
		panel=SXZYPanel::create(TAG_JDZY);
		m_iCurrentType=TYPE_JDZY;
		break;
	case TAG_JPQX:
		panel=SXZYPanel::create(TAG_JPQX);
		m_iCurrentType=TYPE_JPQX;//默认极品转移
		break;
	case TAG_ZBFM:
		panel=ZBFMMainpanel::create(TAG_ZBFM_ZBFM);
		m_iCurrentType=TYPE_ZBFM;//默认装备附魔
		break;
	}
	if (panel)
	{
		panel->setTag(m_iCurrentTopTag);
		panel->setAnchorPoint(CCPointZero);
		addChild(panel);

		updateRightList(m_iCurrentRightTag,m_iCurrentType);
	}
	else
	{
		CPEventHelper::uiNotify("","",Error::NotOpenNewFunc);	
	}
}


void ForgingMainPanel::updateRightList( int tag ,int type)
{
	if (m_iCurrentRightTag!=-1 )
	{
		m_pBagMenu->removeChildByTag(m_iCurrentRightTag);
	}
	
	m_iCurrentRightTag=tag;
	

	//按钮变更
	reloadRightButton();

	CCMenuItemSprite *pItem=NULL;

	pItem=(CCMenuItemSprite *)m_pRightMenu->getChildByTag(m_iCurrentRightTag);
	CCSprite* pSprite=SystemData::getSpriteByPlist("forging_bag_button.sel");
	pItem->setNormalImage(pSprite);

	updateBag(type);
	
}

void ForgingMainPanel::updateBag( int type )
{
	if (type>=Type_special)
	{
		if (m_pBagMenu->getChildByTag(m_iCurrentRightTag))
		{
			((BagCellPanel*)(m_pBagMenu->getChildByTag(m_iCurrentRightTag)))->setCurVisibleType(type);
		}
		else
		{
			m_pBagMenu->removeAllChildren();
			
			BagCellPanel* panel = NULL;
			//panel=RoleBag::create(m_iCurrentRightTag ,type);

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
			panel=BagCellPanel::create(x,y,count,type1,Bag_Type_ItemEx1);
			//panel->setCurVisibleType(type);
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
	}
	else
	{
		if (m_pBagMenu->getChildByTag(m_iCurrentRightTag))
		{
			m_pBagMenu->removeChildByTag(m_iCurrentRightTag);
		}
		BagCellPanel* panel = NULL;
		//panel=RoleBag::create(m_iCurrentRightTag ,type);

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
		panel=BagCellPanel::create(x,y,count,type1,Bag_Type_ItemEx1);
		//panel->setCurVisibleType(type);
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
	
	m_iCurrentType=type;
}


void ForgingMainPanel::reloadRightButton()
{
	for (int i=0;i<3;i++)
	{
		CCMenuItemSprite *pItem=(CCMenuItemSprite *)m_pRightMenu->getChildByTag(i+300);
		CCSprite* pSprite=SystemData::getSpriteByPlist("forging_bag_button");
		pItem->setNormalImage(pSprite);
	}
}

void ForgingMainPanel::PostNotic(UserItem* pObject)
{
	switch (m_iCurrentTopTag)
	{
	case TAG_ZBSJ:
		((ZBSJpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_ZBQH:
		((ZBQHpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_ZBJD:
		((ZBJDpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;	
	case TAG_ZSDZ:
		((ZSDZpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);		
		break;
	case TAG_SXZY:
		((SXZYPanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_HWTH:
		((HWpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_ZJTH:
		((HWpanel *)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	case TAG_ZBFM:
		((ZBFMMainpanel*)this->getChildByTag(m_iCurrentTopTag))->addItem(pObject);
		break;
	default:
		break;
	}
}

void ForgingMainPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_CANCEL)
	{
		switch (m_iCurrentTopTag)
		{
		case TAG_ZBSJ:
			((ZBSJpanel *)this->getChildByTag(m_iCurrentTopTag))->removeItem();
			break;
		case TAG_ZBQH:
			((ZBQHpanel *)this->getChildByTag(m_iCurrentTopTag))->removeItem();
			break;
		case TAG_ZBJD:
			((ZBJDpanel *)this->getChildByTag(m_iCurrentTopTag))->removeItem();
			break;	
		case TAG_ZSDZ:
			((ZSDZpanel *)this->getChildByTag(m_iCurrentTopTag))->removeItem();
			break;
		case TAG_SXZY:
			((SXZYPanel *)this->getChildByTag(m_iCurrentTopTag))->removeItem();
			break;
		case TAG_HWTH:
			((HWpanel *)this->getChildByTag(m_iCurrentTopTag))->removeItem();
			break;
		case TAG_ZJTH:
			((HWpanel *)this->getChildByTag(m_iCurrentTopTag))->removeItem();
			break;
		case TAG_ZBFM:
			((ZBFMMainpanel *)this->getChildByTag(m_iCurrentTopTag))->removeItem();
			break;
		default:
			break;
		}
	}
	
}
