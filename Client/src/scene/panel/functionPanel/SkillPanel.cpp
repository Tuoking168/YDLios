#include "SkillPanel.h"
#include <algorithm>
#include "MainUIModule.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/luadata/LuaData.h"
#include "ext/CCMenuEx.h"
#include "ItemTooltip.h"
#include "module/ModuleData.h"
#include "module/UserDataModule.h"
#include "userdata/HeroData.h"
#include "event/EventProtocol.h"
#include "event/CPEventHelper.h"
#include "ErrorDefinition.h"
#include "scene/panel/MainPanel.h"
#include "scene/Game.h"
#include "scene/GameUI.h"

struct SkillData
{
	int skillid;
	int openLevel;
	int openReborn;
	SkillData()
		: skillid(0)
		, openLevel(0)
		, openReborn(0)
	{}
};

bool compare(SkillData sa, SkillData sb)
{
	if (sa.openReborn != sb.openReborn)
		return sa.openReborn < sb.openReborn;
	else
		return sa.openLevel < sb.openLevel;
}


SkillPanel::SkillPanel():
	m_icurSkillPanelType(0)
{

}

SkillPanel::~SkillPanel()
{

}

SkillPanel* SkillPanel::create(int tag)
{
	SkillPanel* skillPanel = new SkillPanel();
	if(skillPanel && skillPanel->init(tag))
	{
		skillPanel->autorelease();
		return skillPanel;
	}
	if (skillPanel)
	{
		delete skillPanel;
	}
	return NULL;
}

bool SkillPanel::init(int tag)
{
	m_icurSkillPanelType=tag;
	if (!GeneralMenuListener::init())
	{
		return false;
	}
	int height=0;
	if (m_icurSkillPanelType==s_RolePanel)
	{
		CCScale9Sprite* m_pBkgSprite = SystemData::getScale9SpriteByPlist("ui.bag.small_bkg", 305, 429);
		m_pBkgSprite->setAnchorPoint(CCPointZero);
		m_pBkgSprite->setPosition(CCPointZero);
		addChild(m_pBkgSprite);
	}
	else
	{
		height=60;
	}
	//init the unmoved elements in the skill panel,other parts will be added dynamically
	//init the scrollable table view
	m_pContainer = GeneralMenu::create();
	m_pContainer->setAnchorPoint(CCPointZero); 

	m_pTableView=CCTableViewEx::create(this,CCSizeMake(SystemData::getLayoutSize("skillpanel.view.size").width,SystemData::getLayoutSize("skillpanel.view.size").height-height),kCCScrollViewDirectionVertical,this,m_pContainer);
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pTableView->setAnchorPoint(CCPointZero);
	m_pTableView->setPosition(SystemData::getLayoutPoint("attribute_pos"));
	m_pTableView->reloadData();  
	addChild(m_pTableView);
	
	m_szListCellSize = CCSizeMake(m_pTableView->getContentSize().width,900);

	setAnchorPoint(CCPointZero);
	setPosition(CCPointZero);

	return true;
}

cocos2d::CCSize SkillPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
//	static std::string job[] = {"nil","zhanshi","fashi","daoshi"};
//	static std::string key = "skillpanel." + job[HeroData::getJob()] + ".cell.size";
//	static CCSize cellsize = SystemData::getLayoutSize(key);
//	return cellsize;
	return m_szListCellSize;
}

cocos2d::extension::CCTableViewCell* SkillPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = new CCTableViewCell();
	cell->autorelease();

	CCMenuEx* menuex = CCMenuEx::create();
	//menuex->setTouchPriority(kCCMenuHandlerPriority+1);
	menuex->setPosition(CCPointZero);
	cell->addChild(menuex);

	GeneralMenu* menu = GeneralMenu::create();
	//menu->setTouchPriority(kCCMenuHandlerPriority+1);
	menu->setAnchorPoint(CCPointZero);
	menu->setPosition(CCPointZero);
	cell->addChild(menu);

	int y = cellSizeForTable(table).height;
	int height = y;

	//traverse the skill data, and add the skill icons and short description of the player's job
	//add the initiative skill title
	CCScale9Sprite* pInitiativeSkillBkg = SystemData::getScale9SpriteByPlist("skillpanel.initiative.title",100,30);
	cell->addChild(pInitiativeSkillBkg);
	if (m_icurSkillPanelType==s_SettingPanel)
	{
		pInitiativeSkillBkg->setPositionX(140);
	}
	pInitiativeSkillBkg->setPositionY(y-pInitiativeSkillBkg->getContentSize().height/2-10);
	y -= pInitiativeSkillBkg->getContentSize().height + 30;
	CCLabelTTF* pInititiveLabel = CCLabelTTF::create(SystemData::getLayoutString("skillpanel.initiative.label").c_str(),"",18);
	pInititiveLabel->setPosition(ccp(pInitiativeSkillBkg->getContentSize().width/2,pInitiativeSkillBkg->getContentSize().height/2));
	pInititiveLabel->setColor(ccc3(0,255,255));
	pInitiativeSkillBkg->addChild(pInititiveLabel);

	if (m_icurSkillPanelType!=s_SettingPanel)
	{
		CCMenuItemImage *setBtn = LayoutData::getMenuItemLabelImage(CPModuleName::MAIN_UI, "skillPanelToSetting");
		setBtn->setTarget(this, menu_selector(SkillPanel::onSetting));
		setBtn->setPositionY(pInitiativeSkillBkg->getPositionY());
		menuex->addChild(setBtn);
	}

	std::vector<SkillData> skillVec;

	//add the initiative skills
	int job = HeroData::getJob();
	int begin = (job == UserData::CARRER_ZS) ? 101 : (job == UserData::CARRER_FS ? 201 : (job == UserData::CARRER_DS ? 301 : 101)); 
	int endJob = (job == UserData::CARRER_OMNI) ? 3 : 1;
	for (int jobStep=0; jobStep<endJob; jobStep++)
	{
		int curBegin = (job == UserData::CARRER_OMNI) ? (101 + jobStep*100) : begin;
		for (int i=curBegin; i<curBegin+88; i+=10)
		{
			if(LuaData::checkIdExist(LuaData::SKILL,i))
			{
				int type = 1;
				std::string key = "type";
				LuaData::getProp(LuaData::SKILL,i,key,type);
				int id = i;
				GameData::s_user->m_pMainRole->isSkillLearned(i, id);

				if(type == 1 || type == 3)
				{
					SkillData skilldata;
					skilldata.skillid = id;
					key = "reqlvl";
					LuaData::getProp(LuaData::SKILL,i,key,skilldata.openLevel);
					key = "reborn";
					LuaData::getProp(LuaData::SKILL,i,key,skilldata.openReborn);
					/*if (skilldata.openReborn==0)
					{
						
					}*/
					skillVec.push_back(skilldata);
				}
			}
		}
	}

	std::sort(skillVec.begin(),skillVec.end(),compare);

	for(unsigned int i=0; i<skillVec.size(); i++)
	{
		CCMenuItem* pItem = createSkillDescription(skillVec[i].skillid);
		pItem->setAnchorPoint(ccp(0,1));
		pItem->setPosition(ccp(0,y));
		menuex->addChild(pItem);

		if (m_icurSkillPanelType==s_SettingPanel)
		{
			CCLabelTTF* plabel=SystemData::getLabelTTF("skillpanel.skill.btn.name");
			plabel->setColor(ccWHITE);
			plabel->setFontSize(16);
			CCMenuItem* pBtn=SystemData::getScale9MenuItemImageByPlist("skillpanel.skill.btn");
			pBtn->setTarget(this,menu_selector(SkillPanel::clickSkillCallback));
			pBtn->setPosition(ccp(pItem->getPositionX()+230,pItem->getPositionY()-20));
			pBtn->setTag(pItem->getTag());
			plabel->setPosition(pBtn->getPosition());
			menu->addChild(pBtn);
			menu->addChild(plabel);
		}

		y -= 90;
	}

	skillVec.clear();

	if (m_icurSkillPanelType!=s_SettingPanel)
	{
		//add the passive skill title
		CCScale9Sprite* pPassiveSkillBkg = SystemData::getScale9SpriteByPlist("skillpanel.passive.title",100,30);
		//pPassiveSkillBkg->setScaleX(300.0/380);
		if (m_icurSkillPanelType==s_SettingPanel)
		{
			pPassiveSkillBkg->setPositionX(140);
		}
		pPassiveSkillBkg->setPositionY(y-pPassiveSkillBkg->getContentSize().height/2+10);
		cell->addChild(pPassiveSkillBkg );
		y -= pPassiveSkillBkg->getContentSize().height + 20;
		CCLabelTTF* pPassiveLabel = CCLabelTTF::create(SystemData::getLayoutString("skillpanel.passive.label").c_str(),"",18);
		pPassiveLabel->setPosition(ccp(pPassiveSkillBkg->getContentSize().width/2,pPassiveSkillBkg->getContentSize().height/2));
		pPassiveLabel->setColor(ccORANGE);
		pPassiveSkillBkg->addChild(pPassiveLabel);

		y += 10;

		//add the passive skills
		for (int jobStep=0; jobStep<endJob; jobStep++)
		{
			int curBegin = (job == UserData::CARRER_OMNI) ? (101 + jobStep*100) : begin;
			for (int i=curBegin; i<curBegin+88; i+=10)
			{
				if(LuaData::checkIdExist(LuaData::SKILL,i))
				{ 
					int type = 1;
					std::string key = "type";
					LuaData::getProp(LuaData::SKILL,i,key,type);	
					int id = i;
					GameData::s_user->m_pMainRole->isSkillLearned(i, id);

					if(type == 2)
					{
						SkillData skilldata;
						skilldata.skillid = id;
						key = "reqlvl";
						LuaData::getProp(LuaData::SKILL,i,key,skilldata.openLevel);

						key = "reborn";
						LuaData::getProp(LuaData::SKILL,i,key,skilldata.openReborn);

						skillVec.push_back(skilldata);

					}
				}
			}
		}

		std::sort(skillVec.begin(),skillVec.end(),compare);

		for(unsigned int i=0; i<skillVec.size(); i++)
		{
			CCMenuItem* pItem = createSkillDescription(skillVec[i].skillid);
			pItem->setAnchorPoint(ccp(0,1));
			pItem->setPosition(ccp(0,y));
			menuex->addChild(pItem);

			y -= 90;
		}

	}
	

	height -= y+20;

	m_szListCellSize.height = height;
	
	return cell;
}

unsigned int SkillPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

CCMenuItem* SkillPanel::createSkillDescription( int skillid )
{
	//create the menu item to contain the description of one skill
	CCMenuItem* pItem = CCMenuItem::create(this,menu_selector(SkillPanel::clickSkillCallback));
	if (m_icurSkillPanelType==s_SettingPanel)
	{
		pItem->setTarget(this,menu_selector(SkillPanel::setSetting));
	}
	pItem->setContentSize(SystemData::getLayoutSize("skillpanel.description.size"));
	pItem->setTag(skillid);
	
	//create the item background
	CCScale9Sprite* pItemBkg = SystemData::getScale9SpriteByPlist("skillpanel.item.bkg",pItem->getContentSize().width,pItem->getContentSize().height+10);
	pItem->addChild(pItemBkg);

	//create the skill sprite from the key
	CCSprite* pIconbkg = SystemData::getSpriteByPlist("skillpanel.iconbkg");
	pItem->addChild(pIconbkg);

	CCSprite *pIcon = NULL;
	std::string strIconUrl;
	std::string strKey = "icon";
	LuaData::getProp(LuaData::SKILL,skillid,strKey,strIconUrl);
	if (!strIconUrl.empty() &&
		strIconUrl != "0")
	{
		strIconUrl = "skill_" + strIconUrl;
		pIcon = LayoutData::getSpriteByFrameName(strIconUrl + ".png");
		pIcon->setPosition(SystemData::getLayoutPoint("skillpanel.icon.pos"));
		pItem->addChild(pIcon);
	}
	
	//create name, magic cost, level label
	std::string skillname;
	strKey = "name";
	LuaData::getProp(LuaData::SKILL,skillid,strKey,skillname);
	CCLabelTTF* pName = CCLabelTTF::create(skillname.c_str(),"",16);
	pName->setColor(ccc3(101,246,234));
	pName->setPosition(SystemData::getLayoutPoint("skillpanel.name.pos"));
	pName->setAnchorPoint(ccp(0,0.5));
	pItem->addChild(pName);

	int temp = 0;
	if (!GameData::getMyRole()->isSkillLearned(skillid,temp))
	{
		int reqlv = 0;// XXX????????
		strKey = "reqlvl" ;
		LuaData::getProp(LuaData::SKILL,skillid,strKey,reqlv);
		std::string strReqLv = SystemData::intToString(reqlv) + SystemData::getLayoutString("skillpanel.reqlvl");
		CCLabelTTF* pReqLv = CCLabelTTF::create(strReqLv.c_str(),"",16);
		pReqLv->setColor(ccYELLOW);
		pReqLv->setPosition(ccp(SystemData::getLayoutPoint("skillpanel.reqlvl").x,SystemData::getLayoutPoint("skillpanel.name.pos").y));
		pReqLv->setAnchorPoint(ccp(0,0.5));
		if (reqlv != 0)
		{
			pItem->addChild(pReqLv);
		}
		
	}
	


	strKey = "mana";
	int magic_cost = 0;
	LuaData::getProp(LuaData::SKILL,skillid,strKey,magic_cost);
	std::string strMagicCost = SystemData::getLayoutString("skillpanel.magiccost") + SystemData::intToString(magic_cost);
	CCLabelTTF* pMagic = CCLabelTTF::create(strMagicCost.c_str(),"",16);
	pMagic->setColor(ccWHITE);
	pMagic->setPosition(SystemData::getLayoutPoint("skillpanel.magiccost.pos"));
	pMagic->setAnchorPoint(ccp(0,0.5));
	pItem->addChild(pMagic);
	
	strKey = "lvl";		
	int level = 0;
	LuaData::getProp(LuaData::SKILL,skillid,strKey,level);
	std::string strLevel = SystemData::getLayoutString("skillpanel.level") + SystemData::intToString(level);
	CCLabelTTF* pLevel = CCLabelTTF::create(strLevel.c_str(),"",16);
	pLevel->setColor(ccWHITE);
	pLevel->setPosition(SystemData::getLayoutPoint("skillpanel.level.pos"));
	pLevel->setAnchorPoint(ccp(0,0.5));
	pItem->addChild(pLevel);

	//create the experience progress bar with CCScale9Sprite
	int tgtexp = 0;
	strKey = "tgtexp";
	LuaData::getProp(LuaData::SKILL,skillid,strKey,tgtexp);
	CCScale9Sprite* pExperienceBkg = SystemData::getScale9SpriteByPlist("skillpanel.experience.bkg",110,10);
	if (tgtexp > 0)
	{
		pItem->addChild(pExperienceBkg);
	}
	

	temp = 0;
	if(GameData::getMyRole()->isSkillLearned(skillid, temp))
	{
		int curexp = HeroData::getSkillExp(skillid);
		
		if(tgtexp>0)
		{
			
			CCScale9Sprite* pExperienceBar = SystemData::getScale9SpriteByPlist("skillpanel.experience",110,10);
			pExperienceBar->setAnchorPoint(ccp(0,0.5f));
			pExperienceBar->setPosition(ccp(176,17));
			float percent = (float)curexp/(float)tgtexp;
			if(percent>100)
				percent = 1;
			if(percent<0)
				percent = 0;
			pExperienceBar->setScaleX(percent);
			pItem->addChild(pExperienceBar);

			std::string strExp2 =SystemData::intToString(curexp) + "/" + SystemData::intToString(tgtexp);	
			CCLabelTTF* p5=CCLabelTTF::create(strExp2.c_str(),"",11);
			p5->setPosition(ccp(pExperienceBkg->getPositionX()+pExperienceBkg->getContentSize().width/2,pExperienceBkg->getPositionY()));
			pItem->addChild(p5);

		}
	
	}
	else
	{
		if (pIcon)
		{
			pIcon->setColor(ccc3(80,80,80));
		}
	}
		
	return pItem;
}

void SkillPanel::clickSkillCallback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(!pNode)
		return;
	showSkillTips(pNode->getTag());
}

void SkillPanel::showSkillTips( int skillid )
{
	/*if (getChildByTag(100))
	{
		removeChildByTag(100);
	}
	ItemTooltip* ptips=ItemTooltip::create();
	CCPoint pos=ccp(100,100);
	pos=convertToNodeSpace(pos);
	ptips->setTooltipSkill(skillid);
	ptips->setPosition(pos);
	ptips->setTag(100);
	addChild(ptips);*/
	Game::getGameUI()->showSkillTipsPanel(skillid);
	return;
}

void SkillPanel::setSetting( CCObject* pSender )
{
	//???????????
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(!pNode)
		return;
	int tag=pNode->getTag();
	if (GameData::s_user->m_pMainRole->isSkillLearned(tag,tag))
	{
		CPEventHelper::setEventIntData(CPEventName::DATA_CHANGE, CPEventData::VALUE_2, 1);
		CPEventHelper::setEventIntData(CPEventName::DATA_CHANGE, CPEventData::VALUE_3, tag);
		CPEventHelper::dispatcher(CPEventName::DATA_CHANGE, "", "SettingFastPanel");
	}
	else
	{
		CPEventHelper::uiNotify("","",Error::NotLearnSkill);
	}

	/*int id=UserData::getemptyFast();
	if (id==0)
	{
		CPEventHelper::msgResponse("","",Error::Max_FastKey);
	}
	else
	{
		UserData::setIntData(HeroData::getPID(),CPUserData::FAST_TYPE_,id,1);
		UserData::setIntData(HeroData::getPID(),CPUserData::FAST_NUM_,id,tag);
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_FAST_KEY);
	}*/
}

void SkillPanel::onSetting( CCObject *target )
{
	CPEventHelper::openPanel("MainPanel", TAG_Setting_Panel, 3, 0, 1);
}

