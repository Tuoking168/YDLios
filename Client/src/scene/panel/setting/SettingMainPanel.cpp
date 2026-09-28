#include "SettingMainPanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "SettingBasePanel.h"
#include "SettingFastPanel.h"
#include "SettingTakePanel.h"
#include "SettingProtectPanel.h"
#include "event/CPEventHelper.h"

SettingMainPanel::SettingMainPanel( void ):
	m_icurTop(0),
	m_pMainPanel(NULL),
	m_pcurBtn(NULL)
{

}

SettingMainPanel::~SettingMainPanel( void )
{

}

SettingMainPanel* SettingMainPanel::create()
{
	SettingMainPanel* pPanel = new SettingMainPanel();
	if(pPanel && pPanel->init())
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

bool SettingMainPanel::init()
{

	int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);	
	CCScale9Sprite* pBorder=SystemData::getScale9SpriteByPlist("taskcontent_bigborder",SystemData::getLayoutValue("taskcontent_bigborder.w"),SystemData::getLayoutValue("taskcontent_bigborder.h"));
	pBorder->setAnchorPoint(CCPointZero);
	pBorder->setPosition(SystemData::getLayoutPoint("taskcontent_bigborder"));
	addChild(pBorder);

	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	//¶¥²¿°´Å¥µÄ°Ú·Å
	int mWidth=0;
	std::string topbtnname[4] = {"ui_setting_base","ui_setting_take","ui_setting_protect","ui_setting_fast"};
	for (int i=0;i<4;i++)
	{
		CCLabelTTF* plabel=CCLabelTTF::create(SystemData::getLayoutString(topbtnname[i]).c_str(),"Î¢ÈíÑÅºÚ",19);
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("ui_setting_Btn",plabel->getContentSize().width+20,SystemData::getLayoutValue("ui_func.anniu.h"));
		CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("ui_setting_Btn.sel",plabel->getContentSize().width+20,SystemData::getLayoutValue("ui_func.anniu.h"));
		CCMenuItemSprite* pBtn=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(SettingMainPanel::menucallback));
		pBtn->setAnchorPoint(ccp(0,1));
		pBtn->setTag(i);
		pBtn->setPosition(ccp(SystemData::getLayoutPoint("ui.bagself.leftmenu").x+mWidth,SystemData::getLayoutPoint("ui.bagself.leftmenu").y));
		pMenu->addChild(pBtn);
		plabel->setPosition(ccp(pBtn->getContentSize().width/2, pBtn->getContentSize().height/2));
		pBtn->addChild(plabel);
		mWidth+=pBtn->getContentSize().width;
		if (i==data2)
		{
			m_pcurBtn=pBtn;
			m_pcurBtn->selected();
		}
	}

	m_pMainPanel=GeneralMenu::create();
	m_pMainPanel->setAnchorPoint(CCPointZero);
	m_pMainPanel->setPosition(CCPointZero);
	addChild(m_pMainPanel);


	addPanel(m_pcurBtn->getTag());
	return true;
}

void SettingMainPanel::menucallback( CCObject* pSender )
{
	CCMenuItemSprite* pNode=(CCMenuItemSprite*)pSender;
	if (pNode)
	{
		if (m_pcurBtn)
		{
			m_pcurBtn->unselected();
		}
		pNode->selected();
		int tag=pNode->getTag();
		addPanel(tag);
		m_pcurBtn=pNode;
	}
}

void SettingMainPanel::addPanel( int tag )
{
	m_pMainPanel->removeAllChildren();
	BasePanel* pPanel=NULL;
	switch (tag)
	{
	case Base_Panel:
		pPanel=SettingBasePanel::create();
		break;
	case Take_Panel:
		pPanel=SettingTakePanel::create();
		break;
	case Protect_Panel:
		pPanel=SettingProtectPanel::create();
		break;
	case Fast_Panel:
		pPanel=SettingFastPanel::create();
		break;
	default:
		break;
	}
	if (pPanel)
	{
		pPanel->setAnchorPoint(CCPointZero);
		pPanel->setPosition(CCPointZero);
		m_pMainPanel->addChild(pPanel);
	}
}
