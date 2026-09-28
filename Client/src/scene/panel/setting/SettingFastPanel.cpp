#include "SettingFastPanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/LayoutData.h"
#include "userdata/netdata/GameRole.h"
#include "controls/CPCheckBox.h"
#include "res/AudioLoader.h"
#include "module/UserDataModule.h"
#include "scene/panel/functionPanel/BagCellPanel.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "scene/panel/functionPanel/SkillPanel.h"
#include "module/ModuleData.h"
#include "userdata/HeroData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/luadata/LuaData.h"
#include "event/EventProtocol.h"
#include "ext/CCActionDestroy.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "EffectDefinition.h"
#include "scene/panel/EffectSprite.h"

CCPoint m_pos[8]={
	ccp(94,350),
	ccp(94,260),
	ccp(94,170),
	ccp(94,80),
	ccp(250,350),
	ccp(250,260),
	ccp(250,170),
	ccp(250,80)
};

SettingFastPanel::SettingFastPanel( void ):
	m_pMainMenu(NULL),
	m_CurSubPanel(0),
	m_pRightMenu(NULL),
	m_pLeftMenu(NULL),
	m_iSelectTag(-1),
	m_pEffect(NULL),
	m_pBtnMenu(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::DATA_CHANGE, this);
}

SettingFastPanel::~SettingFastPanel( void )
{
	CPEvtDispatcher.removeEventListener(CPEventName::DATA_CHANGE, this);
}

SettingFastPanel* SettingFastPanel::create()
{
	SettingFastPanel* pPanel = new SettingFastPanel();
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

bool SettingFastPanel::init()
{
	m_iSelectTag=UserData::getemptyFast();
	//左边
	CCScale9Sprite* pleftborder2=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_base_border2.w"),SystemData::getLayoutValue("ui_setting_base_border2.h"));
	pleftborder2->setAnchorPoint(CCPointZero);
	pleftborder2->setPosition(SystemData::getLayoutPoint("ui_setting_fast_left_text"));
	addChild(pleftborder2);

	CCScale9Sprite* pleftborder1=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_base_border1.w"),SystemData::getLayoutValue("ui_setting_base_border1.h"));
	pleftborder1->setAnchorPoint(CCPointZero);
	pleftborder1->setPosition(ccp(pleftborder2->getPositionX(),pleftborder2->getPositionY()+pleftborder2->getContentSize().height));
	addChild(pleftborder1);

	CCLabelTTF* pleftlabel=SystemData::getLabelTTF("ui_setting_fast_left_text");
	pleftlabel->setColor(ccWHITE);
	pleftlabel->setFontSize(18);
	pleftlabel->setPosition(ccp(pleftborder1->getContentSize().width/2,pleftborder1->getContentSize().height/2));
	pleftborder1->addChild(pleftlabel);


	//you边
	CCScale9Sprite* prightborder2=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_fast_border2.w"),SystemData::getLayoutValue("ui_setting_fast_border2.h"));
	prightborder2->setAnchorPoint(CCPointZero);
	prightborder2->setPosition(SystemData::getLayoutPoint("ui_setting_base_right_text"));
	addChild(prightborder2);

	CCScale9Sprite* prightborder1=SystemData::getScale9SpriteByPlist("ui_setting_base_border",SystemData::getLayoutValue("ui_setting_fast_border1.w"),SystemData::getLayoutValue("ui_setting_fast_border1.h"));
	prightborder1->setAnchorPoint(CCPointZero);
	prightborder1->setPosition(ccp(prightborder2->getPositionX(),prightborder2->getPositionY()+prightborder2->getContentSize().height));
	addChild(prightborder1);



//	initrightPanel();
	m_pBtnMenu=GeneralMenu::create();
	m_pBtnMenu->setAnchorPoint(CCPointZero);
	m_pBtnMenu->setPosition(CCPointZero);
	addChild(m_pBtnMenu);
	
	m_pLeftMenu=GeneralMenu::create();
	m_pLeftMenu->setAnchorPoint(CCPointZero);
	m_pLeftMenu->setPosition(CCPointZero);
	addChild(m_pLeftMenu);

	m_pRightMenu=GeneralMenu::create();
	m_pRightMenu->setAnchorPoint(CCPointZero);
	m_pRightMenu->setPosition(CCPointZero);
	addChild(m_pRightMenu);

	m_nWidth=prightborder1->getContentSize().width;
	m_nHeight=prightborder1->getContentSize().height;
	addCover(prightborder1->getPosition(),kCCMenuHandlerPriority-1);


	m_pMainMenu=CCMenu::create();
	m_pMainMenu->setTouchPriority(kCCMenuHandlerPriority-1);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_pMainMenu->setPosition(CCPointZero);

	addChild(m_pMainMenu);

	CCMenuItemImage* pFirstBtn=SystemData::getMenuItemImageByPlist("ui_setting_fast_btn");
	pFirstBtn->setTag(setting_SkillPanel);
	pFirstBtn->setPosition(SystemData::getLayoutPoint("ui_setting_fast_btn1"));
	pFirstBtn->setTarget(this,menu_selector(SettingFastPanel::menucallback));
	m_pMainMenu->addChild(pFirstBtn);

	CCLabelTTF* plabel1=SystemData::getLabelTTF("ui_setting_fast_btn_text1");
	plabel1->setFontSize(18);
	plabel1->setColor(ccWHITE);
	plabel1->setPosition(ccp(pFirstBtn->getContentSize().width/2,pFirstBtn->getContentSize().height/2));
	pFirstBtn->addChild(plabel1);

	pFirstBtn->selected();

	CCMenuItemImage* SecondBtn=SystemData::getMenuItemImageByPlist("ui_setting_fast_btn");
	SecondBtn->setTag(setting_BagPanel);
	SecondBtn->setPosition(SystemData::getLayoutPoint("ui_setting_fast_btn2"));
	SecondBtn->setTarget(this,menu_selector(SettingFastPanel::menucallback));
	m_pMainMenu->addChild(SecondBtn);

	CCLabelTTF* plabel2=SystemData::getLabelTTF("ui_setting_fast_btn_text2");
	plabel2->setFontSize(18);
	plabel2->setColor(ccWHITE);
	plabel2->setPosition(ccp(SecondBtn->getContentSize().width/2,SecondBtn->getContentSize().height/2));
	SecondBtn->addChild(plabel2);
	//plabel2->setPosition(SecondBtn->getPosition());
	//m_pMainMenu->addChild(plabel2);



	initLeftPanel();

	initBtn(setting_SkillPanel);
	insertLeftItem();

	if (m_pEffect==NULL)
	{
		if (m_iSelectTag==0)
		{
			m_iSelectTag=1;
		}
		m_pEffect=EffectSprite::create(Effect::effect_activityopen);
		m_pEffect->setPosition(m_pos[m_iSelectTag-1]);
		addChild(m_pEffect);
	}

	return true;
}

void SettingFastPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		switch (tag)
		{
		case setting_BagPanel:
			initBtn(tag);
			break;
		case setting_SkillPanel:
			initBtn(tag);
			break;
		default:
			break;
		}
	}
}

void SettingFastPanel::initLeftPanel()
{
	for (int i=0;i<8;i++)
	{
		CCMenuItemImage* pitembkg=SystemData::getMenuItemImageByPlist("ui_setting_fast_itembkg");
		pitembkg->setTarget(this,menu_selector(SettingFastPanel::leftBtnCallBack));
		pitembkg->setTag(i+1);
		pitembkg->setPosition(m_pos[i]);
		m_pBtnMenu->addChild(pitembkg);

		CCLabelTTF* plabel=CCLabelTTF::create(SystemData::intToString(i+1).c_str(),"",18);
		plabel->setPosition(pitembkg->getPosition());
		m_pBtnMenu->addChild(plabel);
	}
}

void SettingFastPanel::initrightPanel(int tag)
{
	if (tag==setting_BagPanel)
	{
		addBagPanel();
	}
	else if (tag==setting_SkillPanel) 
	{
		addSkillPanel();
	}
}

void SettingFastPanel::onEnter()
{
	BasePanel::onEnter();
}

void SettingFastPanel::onExit()
{
	UserData::saveData();
	BasePanel::onExit();
}

void SettingFastPanel::initBtn( int tag )
{
	if ((tag==setting_BagPanel || tag==setting_SkillPanel) && m_CurSubPanel!=0)
	{
		((CCMenuItemImage*)(m_pMainMenu->getChildByTag(m_CurSubPanel)))->unselected();
	}
	((CCMenuItemImage*)(m_pMainMenu->getChildByTag(tag)))->selected();
	if (m_CurSubPanel==tag)
	{
		return;
	}
	initrightPanel(tag);
	m_CurSubPanel=tag;
}

void SettingFastPanel::addSkillPanel()
{
	m_pRightMenu->removeAllChildren();
	SkillPanel* pPanel=SkillPanel::create(s_SettingPanel);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(ccp(380,8));
	m_pRightMenu->addChild(pPanel);

}

void SettingFastPanel::addBagPanel()
{
	m_pRightMenu->removeAllChildren();
	BagCellPanel* pPanel=BagCellPanel::create(5,4,80,Setting_Bag,Bag_Type_Setting);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(ccp(378,-58));
	m_pRightMenu->addChild(pPanel);
}

void SettingFastPanel::insertLeftItem()
{
	CCArray *children = m_pLeftMenu->getChildren();
	if (children && children->count() > 0)
	{
		CCObject *obj = NULL;
		CCARRAY_FOREACH(children, obj)
		{
			CCNode *child = dynamic_cast<CCNode *>(obj);
			if (child)
			{
				CCHide *hi = CCHide::create();
				CCDelayTime *dl = CCDelayTime::create(0.5f);
				CCActionInstantRemoveFromParent *rmv = CCActionInstantRemoveFromParent::create();
				CCAction *action = CCSequence::create(hi, dl, rmv, NULL);
				child->runAction(action);
			}
		}
	}
	for (int i=0;i<8;i++)
	{
		int sid=UserData::getIntData(HeroData::getPID(),CPUserData::FAST_NUM_,i+1);
		int type=UserData::getIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,i+1);
		if (type==0)
		{
			continue;
		}
		if (type==1)//技能
		{
			std::string strIconUrl;
			std::string strKey = "icon";
			LuaData::getProp(LuaData::SKILL,sid,strKey,strIconUrl);
			strIconUrl = "skill_" + strIconUrl;

			CCSprite *norm = LayoutData::getSpriteByFrameName(strIconUrl + ".png");
			CCSprite *sel = LayoutData::getSpriteByFrameName(strIconUrl + "_sel.png");
			CCMenuItemSprite *pIcon = CCMenuItemSprite::create(norm, sel);
			pIcon->setTag(i+1);
			pIcon->setPosition(m_pos[i]);
			pIcon->setTarget(this,menu_selector(SettingFastPanel::fastclickback));
			m_pLeftMenu->addChild(pIcon);
		}
		else if (type==2)//物品
		{
			CCMenuItemImage* pItem=CommonFunction::getItemIconButDelete(CommonFunction::createNewItem(sid),false);
			pItem->setTag(i+1);
			pItem->setPosition(m_pos[i]);
			pItem->setTarget(this,menu_selector(SettingFastPanel::fastclickback));
			m_pLeftMenu->addChild(pItem);
		}
	}
	//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE); 
}

void SettingFastPanel::fastclickback( CCObject* pSender )
{
	CCNode* pNode=dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		int tag=pNode->getTag();


		if (m_iSelectTag==tag)
		{
			UserData::setIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,tag,0);
			UserData::setIntData(HeroData::getPID(),CPUserData::FAST_NUM_,tag,0);
			insertLeftItem();
			EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE); 
			return;
		}
		else
		{
			m_iSelectTag=pNode->getTag();
		}

		if (m_pEffect)
		{
			m_pEffect->setPosition(pNode->getPosition());
		}
		else
		{
			m_pEffect=EffectSprite::create(Effect::effect_activityopen);
			m_pEffect->setPosition(pNode->getPosition());
			addChild(m_pEffect);
		}
	}
}

void SettingFastPanel::handleEvent( int channel )
{
	if (channel== EventProtocol::EVENT_FAST_KEY)
	{
		insertLeftItem();
	}
}

void SettingFastPanel::leftBtnCallBack( CCObject* pSender )
{
	CCNode* pNode=(CCNode*)pSender;
	if (pNode)
	{
		int tag=pNode->getTag();
		UserData::setIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,tag,0);
		UserData::setIntData(HeroData::getPID(),CPUserData::FAST_NUM_,tag,0);
		UserData::saveData();
	}

	insertLeftItem();

	m_iSelectTag=pNode->getTag();

	if (m_pEffect)
	{
		m_pEffect->setPosition(pNode->getPosition());
	}
	else
	{
		m_pEffect=EffectSprite::create(Effect::effect_activityopen);
		m_pEffect->setPosition(pNode->getPosition());
		addChild(m_pEffect);
	}
}

void SettingFastPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::DATA_CHANGE)
	{
		int type=CPEventHelper::getEventIntData(CPEventData::VALUE_2);
		int tag=CPEventHelper::getEventIntData(CPEventData::VALUE_3);
		if (m_iSelectTag!=-1)
		{
			/*if (m_pEffect)
			{
				removeChild(m_pEffect);
				m_pEffect=NULL;
			}*/
			UserData::setIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,m_iSelectTag,type);
			UserData::setIntData(HeroData::getPID(),CPUserData::FAST_NUM_,m_iSelectTag,tag);
			//m_iSelectTag=-1;
		}
		else
		{
			int id=UserData::getemptyFast();
			if (id==0)
			{
				CPEventHelper::msgResponse("","",Error::Max_FastKey);
			}
			else
			{
				UserData::setIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,id,type);
				UserData::setIntData(HeroData::getPID(),CPUserData::FAST_NUM_,id,tag);
			}
		}
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_FAST_KEY);
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_NET_SKILL_CHANGE); 
		UserData::saveData();
	}
}
