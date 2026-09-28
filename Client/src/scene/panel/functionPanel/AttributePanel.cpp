#include "AttributePanel.h"
#include "userdata/SystemData.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "event/EventProtocol.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "CombatDefinition.h"
#include "script/LuaWrapper.h"
#include "userdata/luadata/LuaData.h"
#include "EntityDefinition.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/OtherRole.h"
#include "BuffExPanel.h"

AttributePanel* AttributePanel::attributePanel = 0;

AttributePanel::AttributePanel():
	m_Height(0),
	m_bIsSelf(true)
{
	m_pMainMenu=NULL;
}


AttributePanel::~AttributePanel()
{

	CC_SAFE_RELEASE(m_pMainMenu);
}

void AttributePanel::setMainMenu(CCLayer* var)
{
	CC_SAFE_RELEASE(m_pMainMenu);
	m_pMainMenu=var;
	CC_SAFE_RETAIN(m_pMainMenu);
}

CCLayer* AttributePanel::getMainMenu()
{
	return m_pMainMenu;
}


AttributePanel* AttributePanel::create(bool isSelf)
{
	AttributePanel* attributePanel = new AttributePanel();
	if(attributePanel && attributePanel->init(isSelf))
	{
		attributePanel->autorelease();
		return attributePanel;
	}

	if (attributePanel)
	{
		delete attributePanel;
	}
	return NULL;

}
bool AttributePanel::init(bool isSelf)
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_bIsSelf=isSelf;
	m_iCurrentTag=0;
	CCScale9Sprite* m_pBkgSprite = SystemData::getScale9SpriteByPlist("ui.bag.small_bkg", 305, 429);

	if(!m_pBkgSprite)
	{
		return false;
	}
	m_pBkgSprite->setAnchorPoint(CCPointZero);
	//m_pBkgSprite->setPosition(SystemData::getLayoutPoint("ui.bagpanel"));
	m_pBkgSprite->setPosition(CCPointZero);
	addChild(m_pBkgSprite);

	// initialize comprehensive capabilities and switch button
	CCLabelTTF* p_cap = CCLabelTTF::create(SystemData::getLayoutString("wx.property.fight").c_str(),"微软雅黑",16);
	p_cap->setAnchorPoint(CCPointZero);
	p_cap->setColor(ccYELLOW);
	p_cap->setPosition(ccp(8,388));	
	addChild(p_cap);

	//显示战斗力
	int combatnum=0;
	if(m_bIsSelf)
	{
		combatnum=HeroData::getProp(Entity::attr_combat_data_num);
	}
	else
	{
		combatnum=GameData::s_user->m_pOtherRole->mCombatNum;
	}
	m_pCombatNum=CCLabelAtlas::create(SystemData::intToString(combatnum).c_str(), SystemData::getLayoutString("ui.attribute_panel.num").c_str(), 17, 20, '0');
	m_pCombatNum->setAnchorPoint(ccp(0,0));
	m_pCombatNum->setPosition(ccp(p_cap->getPositionX()+p_cap->getContentSize().width+5,p_cap->getPositionY()));
	addChild(m_pCombatNum);

	// switch button
	m_pTopMenu = GeneralMenu::create();
	if (m_pTopMenu)
	{
		m_pTopMenu->setAnchorPoint(CCPointZero);
		m_pTopMenu->setPosition(CCPointZero);
		addChild(m_pTopMenu);
	}
	else
		return false;
	CCMenuItemTextImage *switchBaseButton = SystemData::getMenuItemTextImage("ui.attribute_panel.base_button",SystemData::getLayoutString("wx.property.base1").c_str(),	"微软雅黑",16,ccWHITE);
		/*CCMenuItemTextImage::create(
		SystemData::getLayoutString("ui.attribute_panel.base_button").c_str(),
		SystemData::getLayoutString("ui.attribute_panel.base_button_sel").c_str(),
		this,
		menu_selector(AttributePanel::callBack),
		SystemData::getLayoutString("wx.property.base1").c_str(),
		"微软雅黑",
		16,
		ccWHITE
		);*/
	if(switchBaseButton)
	{
		switchBaseButton->setTarget(this,menu_selector(AttributePanel::callBack));
		switchBaseButton->setTag(TAG_PROP_SWITCH_BASE);
		switchBaseButton->setPosition(ccp(260,395));
		m_pTopMenu->addChild(switchBaseButton);
		switchBaseButton->setVisible(false);
	}
	CCMenuItemTextImage *switchAddButton =  SystemData::getMenuItemTextImage("ui.attribute_panel.ex_button",SystemData::getLayoutString("wx.property.ex1").c_str(),	"微软雅黑",16,ccWHITE);
		/*CCMenuItemTextImage::create(
		SystemData::getLayoutString("ui.attribute_panel.ex_button").c_str(),
		SystemData::getLayoutString("ui.attribute_panel.ex_button_sel").c_str(),
		this,
		menu_selector(AttributePanel::callBack),
		SystemData::getLayoutString("wx.property.ex1").c_str(),
		"微软雅黑",
		16,
		ccWHITE
		);*/
	
	if(switchAddButton)
	{
		switchAddButton->setTarget(this,menu_selector(AttributePanel::callBack));
		switchAddButton->setTag(TAG_PROP_SWITCH_ADDITION);
		switchAddButton->setPosition(ccp(260,395));
		m_pTopMenu->addChild(switchAddButton);
	}

	//加载滚动界面
	pTabelView=CCTableViewEx::create(this,CCSizeMake(284, 360),kCCScrollViewDirectionVertical,this,NULL);
	pTabelView->setVerticalFillOrder(kCCTableViewFillTopDown);
	pTabelView->setAnchorPoint(CCPointZero);
	pTabelView->setPosition(SystemData::getLayoutPoint("attribute_pos"));
	pTabelView->reloadData();  
	m_pTopMenu->addChild(pTabelView);

	updateList(TAG_PROP_SWITCH_BASE);

	return true;
}


void AttributePanel::callBack( CCObject* pSender )
{
 	CCMenuItemTextImage* pMenu = dynamic_cast<CCMenuItemTextImage*>(pSender);
 	if(pMenu)
 	{
 		int tag = pMenu->getTag();
 		switch(tag)
 		{
			case TAG_PROP_SWITCH_ADDITION:
				CCLog(">>>>>>>>>>>>TAG_PROP_SWITCH_ADDITION>>>>>>>>>>>>>>>>>");
				pMenu->setVisible(false);
				m_pTopMenu->getChildByTag(TAG_PROP_SWITCH_BASE)->setVisible(true);
				break;
			case TAG_PROP_SWITCH_BASE:
				CCLog(">>>>>>>>>>>>TAG_PROP_SWITCH_BASE>>>>>>>>>>>>>>>>>");
				pMenu->setVisible(false);
				m_pTopMenu->getChildByTag(TAG_PROP_SWITCH_ADDITION)->setVisible(true);
				break;
 			default:
				CCLog("default press");
 				break;
 		}
		updateList(tag);
 	}
}



void AttributePanel::updateList( int tag )
{
	pTabelView->removeAllChildren();
	m_iCurrentTag=tag;
	CCLayer* layer=NULL;
	if (m_iCurrentTag==TAG_PROP_SWITCH_ADDITION)//如果是加成按钮点击
	{
		layer=AdditonMenu::create(m_bIsSelf);
	}
	else if (m_iCurrentTag==TAG_PROP_SWITCH_BASE)
	{
		layer=BaseMenu::create(m_bIsSelf);
	}
	if (layer)
	{
		m_Height=layer->getContentSize().height;
		layer->setAnchorPoint(CCPointZero);
		pTabelView->setContainer(layer);
	}
	pTabelView->reloadData();	
}



CCSize AttributePanel::cellSizeForTable(CCTableView *table)
{
	if (m_iCurrentTag==TAG_PROP_SWITCH_BASE)
	{
		return CCSizeMake(SystemData::getLayoutSize("attribute_Base_Content").width,m_Height);
	}
	else if (m_iCurrentTag==TAG_PROP_SWITCH_ADDITION)
	{
		return CCSizeMake(SystemData::getLayoutSize("attribute_Addition_Content").width,m_Height);
	}
	return CCSizeMake(0,0);
}

CCTableViewCell* AttributePanel::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		
	}
	return cell;
}

unsigned int AttributePanel::numberOfCellsInTableView(CCTableView *table)
{
	return 1;
}

void AttributePanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ATTRIBUTE_CHANGE )
	{
		//CCLog("Event Recieve");
		updateList(m_iCurrentTag);

		int combatnum = 0;
		if(m_bIsSelf)
		{
			combatnum=HeroData::getProp(Entity::attr_combat_data_num);
		}
		else
		{
			combatnum=GameData::s_user->m_pOtherRole->mCombatNum;
		}
		m_pCombatNum->setString(SystemData::intToString(combatnum).c_str());
	}
}



//-----------------------------------------------------------------//


BaseMenu::BaseMenu():
	m_bIsSelf(true),
	m_iFirstHeight(0),
	m_iBuffHeight(0),
	m_iSecondHeight(0),
	m_iThirdHeight(0)
{

}

BaseMenu::~BaseMenu()
{

}

BaseMenu* BaseMenu::create(bool isSelf)
{
	BaseMenu* characterPanel = new BaseMenu();
	if(characterPanel && characterPanel->init(isSelf))
	{
		characterPanel->autorelease();
		return characterPanel;
	}
	if (characterPanel)
	{
		delete characterPanel;
	}

	return NULL;
}

bool BaseMenu::init(bool isSelf)
{
	m_bIsSelf=isSelf;
	initThirdPart();
	initSecondPart();
	if (isSelf)
	{
		initBuffPart();
	}
	initFirstPart();
	this->setContentSize(CCSizeMake(SystemData::getLayoutSize("attribute_Base_Content").width,m_iFirstHeight + m_iBuffHeight + m_iSecondHeight + m_iThirdHeight));
	
	return true;
}

void BaseMenu::initFirstPart()
{
	CCPoint pos = CCPointZero;
	m_iFirstHeight = 0;
	if (getChildByTag(1))
	{
		removeChildByTag(1);
	}
	CCString *pStr0=NULL;
	CCString *pStr1=NULL;
	CCString *pStr2=NULL;
	CCString *pStr3=NULL;
	CCString *pStr4=NULL;
	CCString *pStr5=NULL;
	CCString *pStr6=NULL;
	CCString *pStr7=NULL;
	CCString *pStr8=NULL;
	CCString *pStr9=NULL;
	CCString *pStr10=NULL;
	CCString *pStr11=NULL;
	CCString *pStr12=NULL;
	CCString *pStr13=NULL;
	CCString *pStrExp=NULL;
	//准备数据

	if (!m_bIsSelf)
	{
		if (!GameData::s_user || !GameData::s_user->m_pOtherRole) return;
		pStr0=CCString::createWithFormat("%d/%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_HP],GameData::s_user->m_pOtherRole->CombatData[Combat::prop_HPMax]);
		pStr1=CCString::createWithFormat("%d/%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_MP],GameData::s_user->m_pOtherRole->CombatData[Combat::prop_MPMax]);	
		pStr2=CCString::createWithFormat("%d-%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_PATK_Min],GameData::s_user->m_pOtherRole->CombatData[Combat::prop_PATK_Max]);
		pStr3=CCString::createWithFormat("%d-%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_MATK_Min],GameData::s_user->m_pOtherRole->CombatData[Combat::prop_MATK_Max]);
		pStr4=CCString::createWithFormat("%d-%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_TATK_Min],GameData::s_user->m_pOtherRole->CombatData[Combat::prop_TATK_Max]);
		pStr5=CCString::createWithFormat("%d-%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_PDEF_Min],GameData::s_user->m_pOtherRole->CombatData[Combat::prop_PDEF_Max]);
		pStr6=CCString::createWithFormat("%d-%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_MDEF_Min],GameData::s_user->m_pOtherRole->CombatData[Combat::prop_MDEF_Max]);
	//pStr6=CCString::createWithFormat("%d/%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_MP],GameData::s_user->m_pOtherRole->CombatData[Combat::prop_MPMax]);	
		pStr7=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Accuracy]);
		pStr8=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Agility]);
		pStr9=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Luck]);
		pStr10=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Curse]);
		pStr11=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Move_Speed]/10);//移动速度
		pStr12=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Attack_Speed]/10);//攻击速度
		pStr13=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Armor_Penetration]);//护甲穿透
		pStrExp = CCString::create("");
	}
	else
	{
		GameRole* myRole = GameData::getMyRole();
		if (!myRole) return;
		pStr0=CCString::createWithFormat("%d/%d",myRole->CombatData[Combat::prop_HP],myRole->CombatData[Combat::prop_HPMax]);
		pStr1=CCString::createWithFormat("%d/%d",myRole->CombatData[Combat::prop_MP],myRole->CombatData[Combat::prop_MPMax]);
		pStr2=CCString::createWithFormat("%d-%d",myRole->CombatData[Combat::prop_PATK_Min],myRole->CombatData[Combat::prop_PATK_Max]);
		pStr3=CCString::createWithFormat("%d-%d",myRole->CombatData[Combat::prop_MATK_Min],myRole->CombatData[Combat::prop_MATK_Max]);
		pStr4=CCString::createWithFormat("%d-%d",myRole->CombatData[Combat::prop_TATK_Min],myRole->CombatData[Combat::prop_TATK_Max]);
		pStr5=CCString::createWithFormat("%d-%d",myRole->CombatData[Combat::prop_PDEF_Min],myRole->CombatData[Combat::prop_PDEF_Max]);
		pStr6=CCString::createWithFormat("%d-%d",myRole->CombatData[Combat::prop_MDEF_Min],myRole->CombatData[Combat::prop_MDEF_Max]);
		//pStr6=CCString::createWithFormat("%d/%d",myRole->CombatData[Combat::prop_MP],myRole->CombatData[Combat::prop_MPMax]);		
		pStr7=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Accuracy]);
		pStr8=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Agility]);
		pStr9=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Luck]);
		pStr10=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Curse]);
		pStr11=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Move_Speed]/10);//移动速度
		pStr12=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Attack_Speed]/10);//攻击速度
		pStr13=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Armor_Penetration]);//护甲穿透
		pStrExp=CCString::createWithFormat("%lld/%lld",myRole->mExperience,myRole->mExperienceNext);
	}
	//准备数据
	std::string str[15]={
		pStr0->getCString(),
		pStr1->getCString(),
		pStr2->getCString(),
		pStr3->getCString(),
		pStr4->getCString(),
		pStr5->getCString(),
		pStr6->getCString(),
		pStr7->getCString(),
		pStr8->getCString(),
		pStr9->getCString(),
		pStr10->getCString(),
		pStr11->getCString(),
		pStr12->getCString(),
		pStr13->getCString(),
		pStrExp->getCString()
	};

	//标题 
	CCLayer *pLayer=CCLayer::create();
	if (!pLayer) return;
	pLayer->setTag(1);
	pLayer->setContentSize(SystemData::getLayoutSize("Base_1_contentsize"));
	CCLabelTTF *ptitle=SystemData::getLabelTTF("attribute_Base_jichushuxing");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,-20));
	ptitle->setFontSize(18); 
	ptitle->setColor(ccYELLOW);
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);
	std::string strlist[14]={
		"Base_1_shengming",
		"Base_1_mofa",
		"Base_1_wuligongji",
		"Base_1_mofagongj",
		"Base_1_daoshugongji",
		"Base_1_wulifangyu",
		"Base_1_mofafangyu",
		"Base_1_zhunque",
		"Base_1_minjie",
		"Base_1_mingyun",
		"Base_1_zuzhou",
		"Base_1_yisu",
		"Base_1_gongsu",
		"Base_1_chuantou"
		
	};
	int x=0;
	int y=0;
	for (int i=0;i<14;i++)
	{		
		CCLabelTTF *plabel=SystemData::getLabelTTF(strlist[i]);
		plabel->setFontSize(14);
		plabel->setColor(ccWHITE);
		plabel->setAnchorPoint(CCPointZero);
		plabel->setPosition(ccp(ptitle->getPositionX()-140+x*220,ptitle->getPositionY()-45-y*30));

		CCLabelTTF *pValue=CCLabelTTF::create(str[i].c_str(),"微软雅黑",14);		
		pValue->setColor(ccGREEN);
		pValue->setAnchorPoint(CCPointZero);
		pValue->setPosition(ccp(plabel->getPositionX()+plabel->getContentSize().width,plabel->getPositionY()));
		pLayer->addChild(pValue);
		pLayer->addChild(plabel);
		y++;
		if (y==7)//6
		{
			y=0;
			x++;
		}
		if (plabel->getPositionY()<pos.y)
		{
			pos = plabel->getPosition();
		}
	}

	if (m_bIsSelf)
	{
		CCLabelTTF *plabel=SystemData::getLabelTTF("Base_3_ExpCur");
		plabel->setFontSize(14);
		plabel->setAnchorPoint(CCPointZero);
		plabel->setColor(ccWHITE);
		plabel->setPosition(ccp(ptitle->getPositionX()-140,ptitle->getPositionY()-255));//225

		CCLabelTTF *pValue=CCLabelTTF::create(str[14].c_str(),"微软雅黑",14);		
		pValue->setColor(ccGREEN);
		pValue->setAnchorPoint(CCPointZero); 
		pValue->setPosition(ccp(plabel->getPositionX()+plabel->getContentSize().width,plabel->getPositionY()));
		pLayer->addChild(pValue);

		pLayer->addChild(plabel);
		if (plabel->getPositionY()<pos.y)
		{
			pos = plabel->getPosition();
		}
	}
	m_iFirstHeight = -pos.y;
	m_iFirstHeight += 20;
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(ccp(0,m_iFirstHeight + m_iBuffHeight + m_iSecondHeight + m_iThirdHeight));
	this->addChild(pLayer);
}

void BaseMenu::initSecondPart()
{
	CCPoint pos = CCPointZero;
	if (getChildByTag(2))
	{
		removeChildByTag(2);
	}
	m_iSecondHeight = 0;
	CCString *pStr0=NULL;
	CCString *pStr1=NULL;
	CCString *pStr2=NULL;
	CCString *pStr3=NULL;
	CCString *pStr4=NULL;
	CCString *pStr5=NULL;
	CCString *pStr6=NULL;
	CCString *pStr7=NULL;
	CCString *pStr8=NULL;
	CCString *pStr9=NULL;
	CCString *pStr10=NULL;
	CCString *pStr11=NULL;
	CCString *pStr12=NULL;
	CCString *pStr13=NULL;
	CCString *pStr14=NULL;

	if (!m_bIsSelf)
	{
		if (!GameData::s_user || !GameData::s_user->m_pOtherRole) return;
		pStr0=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Magic_Hit]/(float)100);
		pStr1=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Magic_Dodge]/(float)100);
		pStr2=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Posion_Dodge]/(float)100);
		pStr3=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Health_Recovery_Point]/(float)100);
		pStr4=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Magic_Recovery_Point]/(float)100);
		pStr5=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Posion_Recovery_Point]/(float)100);
		pStr6=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Death_Recovery_Percent]/(float)100);
		pStr7=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Damage_to_Magic]);
		pStr8=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Holy_Damage]);
		pStr9=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Palsy]);
		pStr10=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Critical_Damage_Bonus]/(float)100);
		pStr11=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Anti_Critical]/(float)100);
		pStr12=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Damage_Reflect_Rate]/(float)100);
		pStr13=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Life_Steal_Rate]/(float)100);
		pStr14=CCString::createWithFormat("%.2f%%",(float)GameData::s_user->m_pOtherRole->CombatData[Combat::prop_Mana_Steal_Rate]/(float)100);

		
	}
	else
	{
		GameRole* myRole = GameData::getMyRole();
		if (!myRole) return;
		pStr0=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Magic_Hit]/(float)100);
		pStr1=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Magic_Dodge]/(float)100);
		pStr2=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Posion_Dodge]/(float)100);
		pStr3=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Health_Recovery_Point]/(float)100);
		pStr4=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Magic_Recovery_Point]/(float)100);
		pStr5=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Posion_Recovery_Point]/(float)100);
		pStr6=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Death_Recovery_Percent]/(float)100);
		pStr7=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Damage_to_Magic]);
		pStr8=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Holy_Damage]);
		pStr9=CCString::createWithFormat("%d",myRole->CombatData[Combat::prop_Palsy]);
		pStr10=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Critical_Damage_Bonus]/(float)100);
		pStr11=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Anti_Critical]/(float)100);
		pStr12=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Damage_Reflect_Rate]/(float)100);
		pStr13=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Life_Steal_Rate]/(float)100);
		pStr14=CCString::createWithFormat("%.2f%%",(float)myRole->CombatData[Combat::prop_Mana_Steal_Rate]/(float)100);
		
	}
	std::string str[15]={
		pStr0->getCString(),
		pStr1->getCString(),
		pStr2->getCString(),
		pStr3->getCString(),
		pStr4->getCString(),
		pStr5->getCString(),
		pStr6->getCString(),
		pStr7->getCString(),
		pStr8->getCString(),
		pStr9->getCString(),
		pStr10->getCString(),
		pStr11->getCString(),
		pStr12->getCString(),
		pStr13->getCString(),
		pStr14->getCString(),
	};
	//标题
	CCLayer *pLayer=CCLayer::create();
    if (!pLayer) return;
	pLayer->setContentSize(SystemData::getLayoutSize("Base_2_contentsize"));
	CCLabelTTF *ptitle=SystemData::getLabelTTF("attribute_Base_xiangxishuxing");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,-20));
	ptitle->setFontSize(18);
	pLayer->setTag(2);
	ptitle->setColor(ccYELLOW);
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);
	std::string strlist[15]={
		"Base_2_mofamingzhong",
		"Base_2_mofashanbi",
		"Base_2_duwushanbi",
		"Base_2_shenminghuifu",
		"Base_2_mofahuifu",
		"Base_2_duwuhuifu",
		"Base_2_siwanghuifu",
		"Base_2_mofazhichexiaoshanghai",
		"Base_2_shensheng",
		"Base_2_mabijilv",
		"Base_2_baoji",  // 暴击（新增）
		"Base_2_fangbao",   // 防爆（新增）
		"Base_2_fantan",  // 反弹（新增）
		"Base_2_xixue",   //吸血（新增）
		"Base_2_xilan"   //吸蓝（新增）
	};
	int x=0;
	int y=0;
	for (int i=0;i<15;i++)//13
	{		
		CCLabelTTF *plabel=SystemData::getLabelTTF(strlist[i]);
		plabel->setFontSize(14);
		plabel->setAnchorPoint(CCPointZero);
		plabel->setColor(ccWHITE);
		plabel->setPosition(ccp(ptitle->getPositionX()-140+x*150,ptitle->getPositionY()-45-y*30));

		CCLabelTTF *pValue=CCLabelTTF::create(str[i].c_str(),"微软雅黑",14);		
		pValue->setColor(ccGREEN);
		pValue->setAnchorPoint(CCPointZero);
		pValue->setPosition(ccp(plabel->getPositionX()+plabel->getContentSize().width,plabel->getPositionY()));
		pLayer->addChild(pValue);

		pLayer->addChild(plabel);

		y++;
		if (y==8)//5
		{
			y=0;
			x++;
		}
		if (plabel->getPositionY()<pos.y)
		{
			pos = plabel->getPosition();
		}
	}
	m_iSecondHeight= -pos.y;
	m_iSecondHeight += 20;
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(ccp(0,m_iSecondHeight + m_iThirdHeight));
	this->addChild(pLayer);
}

void BaseMenu::initThirdPart()
{
	CCPoint pos = CCPointZero;
	if (getChildByTag(3))
	{
		removeChildByTag(3);
	}
	CCString *pStr0=NULL;
	CCString *pStr1=NULL;
	CCString *pStr2=NULL;
	CCString *pStr3=NULL;//灵力
	if (!m_bIsSelf)
	{
		pStr0=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->Honour);
		pStr1=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->mrebornitem);
		pStr2=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->mPKValue);
		pStr3=CCString::createWithFormat("%d",GameData::s_user->m_pOtherRole->mlingliitem);//灵力
	}
	else
	{
		pStr0=CCString::createWithFormat("%d",GameData::s_user->m_pMainRole->Honour);
		pStr1=CCString::createWithFormat("%d",HeroData::getProp(Entity::attr_rebornrqeitem));
		pStr2=CCString::createWithFormat("%d",HeroData::getProp(Entity::attr_pkvalue));
		pStr3=CCString::createWithFormat("%d",HeroData::getProp(Entity::attr_lingliqeitem));//灵力
	}
	std::string str[4] = {//3
		 pStr0->getCString(),
		 pStr1->getCString(),
	     pStr2->getCString(),
		 pStr3->getCString()//灵力
	};


	//标题
	CCLayer *pLayer=CCLayer::create();
	pLayer->setContentSize(SystemData::getLayoutSize("Base_3_contentsize"));
	CCLabelTTF *ptitle=SystemData::getLabelTTF("attribute_Base_qitashuxing");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,-20));
	ptitle->setFontSize(18);
	pLayer->setTag(3);
	ptitle->setColor(ccYELLOW);
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);
	std::string strlist[4]={//4
		"Base_3_rongyu","Base_3_lingpozhuansheng" ,"Base_3_PKzhi","Base_3_lingli"
	};

	int x=0;
	int y=0;
	for (int i=0;i<4;i++)//3
	{		
		CCLabelTTF *plabel=SystemData::getLabelTTF(strlist[i]);
		plabel->setFontSize(14);
		plabel->setAnchorPoint(CCPointZero);
		plabel->setColor(ccWHITE);
		plabel->setPosition(ccp(ptitle->getPositionX()-140+x*150,ptitle->getPositionY()-45-y*30));

		CCLabelTTF *pValue=CCLabelTTF::create(str[i].c_str(),"微软雅黑",14);		
		pValue->setColor(ccGREEN);
		pValue->setAnchorPoint(CCPointZero);
		pValue->setPosition(ccp(plabel->getPositionX()+plabel->getContentSize().width,plabel->getPositionY()));
		pLayer->addChild(pValue);

		pLayer->addChild(plabel);
		y++;
		if (y==2)
		{
			y=0;
			x++;
		}
		if (plabel->getPositionY()<pos.y)
		{
			pos = plabel->getPosition();
		}
	}
	m_iThirdHeight-=pos.y;
	m_iThirdHeight += 20;

	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(ccp(0,m_iThirdHeight));
	this->addChild(pLayer);
}

void BaseMenu::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ATTRIBUTE_CHANGE || channel == EventProtocol::EVENT_CHANGE_HP || channel == EventProtocol::EVENT_CHANGE_MP)
	{
		//CCLog("Event Recieve");
		initFirstPart();
	}
}

void BaseMenu::initBuffPart()
{
	CCPoint pos = CCPointZero;
	if (getChildByTag(4))
	{
		removeChildByTag(4);
	}
	//标题
	CCLayer *pLayer=CCLayer::create();
	pLayer->setContentSize(SystemData::getLayoutSize("Base_3_contentsize"));
	CCLabelTTF *ptitle=SystemData::getLabelTTF("attribute_Base_fujiashuxing");
	ptitle->setPosition(ccp(pLayer->getContentSize().width/2,-20));
	ptitle->setFontSize(18);
	pLayer->setTag(4);
	ptitle->setColor(ccYELLOW);
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);

	BuffExPanel* pPanel = BuffExPanel::create();
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(ccp(0,ptitle->getPositionY()-45));	
	pLayer->addChild(pPanel);

	pos.y = pPanel->getPositionY() - pPanel->getContentSize().height;
	m_iBuffHeight = -pos.y;
	m_iBuffHeight += 20;

	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(ccp(0,m_iBuffHeight + m_iSecondHeight + m_iThirdHeight));
	this->addChild(pLayer);
}



//----------------------------------------------------------------//



AdditonMenu::AdditonMenu():
	m_bIsSelf(true)
{

}

AdditonMenu::~AdditonMenu()
{

}

bool AdditonMenu::init(bool isSelf)
{
	m_bIsSelf=isSelf;

	m_iFirstHeight=0;
	m_iSecondHeight=0;
	m_iThirdHeight=0;
	m_iFourthHeight=0;

	initFourthPart();
	initThirdPart();
	initSecondPart();
	initFirstPart();

	this->setContentSize(CCSizeMake(SystemData::getLayoutSize("attribute_Addition_Content").width,m_iFirstHeight+m_iSecondHeight+m_iThirdHeight+m_iFourthHeight));

	return true;
}

AdditonMenu* AdditonMenu::create( bool isSelf )
{
	AdditonMenu* characterPanel = new AdditonMenu();
	if(characterPanel && characterPanel->init(isSelf))
	{
		characterPanel->autorelease();
		return characterPanel;
	}
	if (characterPanel)
	{
		delete characterPanel;
	}

	return NULL;

}

void AdditonMenu::initFirstPart()
{
	std::string equipstr[12]={
		"Add_equip_1",
		"Add_equip_2",
		"Add_equip_3",
		"Add_equip_4",
		"Add_equip_5",
		"Add_equip_6",
		"Add_equip_7",
		"Add_equip_8",
		"Add_equip_9",
		"Add_equip_10",
		"Add_equip_11",
		"Add_equip_12"
	};

	//判断达到几层效果 
	int currentlvl=0;
	std::vector<int> list=checkFirst(currentlvl+1);
	int enchanceSize = checkEnhanceSize();
	while (list.size()==12 && currentlvl!=enchanceSize)
	{
		currentlvl++;
		list=checkFirst(currentlvl+1);
	}

	//标题
	CCLayer *pLayer=CCLayer::create();
	CCLabelTTF *ptitle=SystemData::getLabelTTF("attribute_Addition_qianghuaxiaoguojiacheng");
	ptitle->setPosition(ccp(150,-20));
	ptitle->setFontSize(18);
	ptitle->setColor(ccYELLOW);
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);

	CCPoint Pos=ccp(5,-20-pback->getContentSize().height);

	//当前效果：
	CCLabelTTF* pTitle_c=SystemData::getLabelTTF("Add_1_dangqianxiaoguo");
	pTitle_c->setPosition(Pos);
	pTitle_c->setAnchorPoint(CCPointZero);
	pTitle_c->setFontSize(14);
	pTitle_c->setColor(ccORANGE);
	pLayer->addChild(pTitle_c);
	Pos=ccp(Pos.x,Pos.y-pTitle_c->getContentSize().height-5);

	if (currentlvl==0)//如果当前没有加成效果 
	{
		CCLabelTTF* p=CCLabelTTF::create(AToU8("无"),"微软雅黑",14);
		p->setAnchorPoint(CCPointZero);
		p->setColor(ccRED);
		p->setPosition(ccp(pTitle_c->getPositionX()+pTitle_c->getContentSize().width+10,pTitle_c->getPositionY()));
		pLayer->addChild(p);
	}
	else
	{
		std::string attrname;
		LuaData::getProp("gdEnhanceAttribute",currentlvl,"name",attrname);
		CCLabelTTF* p_c=CCLabelTTF::create(attrname.c_str(),"微软雅黑",14);
		p_c->setAnchorPoint(CCPointZero);
		p_c->setColor(ccGREEN);
		p_c->setPosition(ccp(pTitle_c->getPositionX()+pTitle_c->getContentSize().width+10,pTitle_c->getPositionY()));
		pLayer->addChild(p_c);

		int attrlvl=0;
		LuaData::getProp("gdEnhanceAttribute",currentlvl,"reqlvl",attrlvl);
		CCLabelTTF* p_cValue=CCLabelTTF::create(("+"+SystemData::intToString(attrlvl)).c_str(),"微软雅黑",14);
		p_cValue->setAnchorPoint(CCPointZero);
		p_cValue->setColor(ccGREEN);
		p_cValue->setPosition(ccp(p_c->getPositionX()+p_c->getContentSize().width+5,p_c->getPositionY()));
		pLayer->addChild(p_cValue);

		CCLabelTTF* p_cCount=CCLabelTTF::create(AToU8("(12/12)"),"微软雅黑",14);
		p_cCount->setAnchorPoint(CCPointZero);
		p_cCount->setColor(ccGREEN);
		p_cCount->setPosition(ccp(p_cValue->getPositionX()+p_cValue->getContentSize().width+5,p_cValue->getPositionY()));
		pLayer->addChild(p_cCount);

		int x=0,y=0;
		for (int i=0;i<12;i++)
		{
			CCLabelTTF* p=SystemData::getLabelTTF(equipstr[i].c_str());
			p->setAnchorPoint(CCPointZero);
			p->setColor(ccWHITE);
			p->setFontSize(14);
			p->setPosition(ccp(Pos.x+x*50,Pos.y-y*(p->getContentSize().height+5)));
			pLayer->addChild(p);
			x++;
			if (x==6)
			{
				y++;
				x=0;
			}
		}
		Pos=ccp(Pos.x,Pos.y-2*20);
		int size=0;
		LuaData::getProp_size("gdEnhanceAttribute",currentlvl,"attr",size);
		for (int i=0;i<size;i++)
		{
			int value=0,type=0;
			std::string name;
			LuaData::getProp("gdEnhanceAttribute",currentlvl,"attr",i+1,"name",name);
			LuaData::getProp("gdEnhanceAttribute",currentlvl,"attr",i+1,"data","type",type,value);			
			CCLabelTTF* p=getSingleLabel(type,value,name);
			p->setPosition(Pos);
			pLayer->addChild(p);
			Pos=ccp(Pos.x,Pos.y-20);
		}
	}

	//下级效果：
	CCLabelTTF* pTitle_x=SystemData::getLabelTTF("Add_1_xiajixiaoguo");
	pTitle_x->setPosition(Pos);
	pTitle_x->setAnchorPoint(CCPointZero);
	pTitle_x->setColor(ccORANGE);
	pTitle_x->setFontSize(14);
	pLayer->addChild(pTitle_x);
	Pos=ccp(Pos.x,Pos.y-pTitle_x->getContentSize().height-5);

	std::string attrname; 
	LuaData::getProp("gdEnhanceAttribute",currentlvl+1,"name",attrname); 
	if (attrname=="0")
	{
		CCLabelTTF* p=CCLabelTTF::create(AToU8("无"),"微软雅黑",14);
		p->setAnchorPoint(CCPointZero);
		p->setColor(ccRED);
		p->setPosition(ccp(pTitle_x->getPositionX()+pTitle_x->getContentSize().width+10,pTitle_x->getPositionY()));
		pLayer->addChild(p);
	}
	else
	{
		std::string attrname;
		LuaData::getProp("gdEnhanceAttribute",currentlvl+1,"name",attrname);
		CCLabelTTF* p_x=CCLabelTTF::create(attrname.c_str(),"微软雅黑",14);
		p_x->setAnchorPoint(CCPointZero);
		p_x->setColor(ccGREEN);
		p_x->setPosition(ccp(pTitle_x->getPositionX()+pTitle_x->getContentSize().width+10,pTitle_x->getPositionY()));
		pLayer->addChild(p_x);
		 
		int attrlvl;
		LuaData::getProp("gdEnhanceAttribute",currentlvl+1,"reqlvl",attrlvl);
		CCLabelTTF* p_xValue=CCLabelTTF::create(("+"+SystemData::intToString(attrlvl)).c_str(),"微软雅黑",14);
		p_xValue->setAnchorPoint(CCPointZero);
		p_xValue->setColor(ccGREEN);
		p_xValue->setPosition(ccp(p_x->getPositionX()+p_x->getContentSize().width+5,p_x->getPositionY()));
		pLayer->addChild(p_xValue);

		int equipcount=list.size();
		std::string attrcount="("+SystemData::intToString(equipcount)+"/12)";
		CCLabelTTF* p_xCount=CCLabelTTF::create(attrcount.c_str(),"微软雅黑",14);
		p_xCount->setAnchorPoint(CCPointZero);
		p_xCount->setColor(ccGREEN);
		p_xCount->setPosition(ccp(p_xValue->getPositionX()+p_xValue->getContentSize().width+5,p_xValue->getPositionY()));
		pLayer->addChild(p_xCount);

		CCLabelTTF* p_xFlag=CCLabelTTF::create(AToU8("(未激活)"),"微软雅黑",14);
		p_xFlag->setAnchorPoint(CCPointZero);
		p_xFlag->setColor(ccRED);
		p_xFlag->setPosition(ccp(p_xCount->getPositionX()+p_xCount->getContentSize().width+10,p_xCount->getPositionY()));
		pLayer->addChild(p_xFlag);

		int x=0,y=0;
		for (int i=0;i<12;i++)
		{
			CCLabelTTF* p=SystemData::getLabelTTF(equipstr[i].c_str());
			p->setAnchorPoint(CCPointZero);
			p->setColor(ccGRAY);
			std::vector<int>::iterator it;
			for (it=list.begin();it!=list.end();it++)
			{
				if (i==(*it))
				{
					p->setColor(ccWHITE);
				}
			}
			p->setFontSize(14);
			p->setPosition(ccp(Pos.x+x*50,Pos.y-y*(p->getContentSize().height+5)));
			pLayer->addChild(p);
			x++;
			if (x==6)
			{
				y++;
				x=0;
			}
		}
		Pos=ccp(Pos.x,Pos.y-2*20);
		int size=0;
		LuaData::getProp_size("gdEnhanceAttribute",currentlvl+1,"attr",size);
		for (int i=0;i<size;i++)
		{
			int value=0,type=0;
			std::string name;
			LuaData::getProp("gdEnhanceAttribute",currentlvl+1,"attr",i+1,"name",name);
			LuaData::getProp("gdEnhanceAttribute",currentlvl+1,"attr",i+1,"data","type",type,value);			
			CCLabelTTF* p=getSingleLabel(type,value,name,false);
			p->setPosition(Pos);
			pLayer->addChild(p);
			Pos=ccp(Pos.x,Pos.y-20);
		}
	}
	

	//加载layer

	m_iFirstHeight = (Pos.y < 0 ? -Pos.y : Pos.y) + 10;
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(ccp(0,m_iFirstHeight+m_iSecondHeight+m_iThirdHeight+m_iFourthHeight));
	this->addChild(pLayer);

}

void AdditonMenu::initSecondPart()
{
	//判断达到几层效果 
	int currentlvl=0;
	int reqstonecnt=0;
	int allsize=0;
	LuaData::getProp_size("gdStoneAttribute",0,"",allsize);
	LuaData::getProp("gdStoneAttribute",currentlvl+1,"reqcnt",reqstonecnt);
	while (checkSecond(currentlvl+1)>=reqstonecnt && currentlvl<allsize)
	{
		currentlvl++;
		LuaData::getProp("gdStoneAttribute",currentlvl+1,"reqcnt",reqstonecnt);
	}

	//标题
	CCLayer *pLayer=CCLayer::create();
	CCLabelTTF *ptitle=SystemData::getLabelTTF("attribute_Addition_hunshixiaoguojiacheng");
	ptitle->setPosition(ccp(150,0));
	ptitle->setFontSize(18);
	ptitle->setColor(ccYELLOW);
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);

	CCPoint Pos=ccp(5,0-pback->getContentSize().height);

	//当前效果：
	CCLabelTTF* pTitle_c=SystemData::getLabelTTF("Add_1_dangqianxiaoguo");
	pTitle_c->setPosition(Pos);
	pTitle_c->setAnchorPoint(CCPointZero);
	pTitle_c->setFontSize(14);
	pTitle_c->setColor(ccORANGE);
	pLayer->addChild(pTitle_c);
	Pos=ccp(Pos.x,Pos.y-pTitle_c->getContentSize().height-5);

	if (currentlvl==0)//如果当前没有加成效果 
	{
		CCLabelTTF* p=CCLabelTTF::create(AToU8("无"),"微软雅黑",14);
		p->setAnchorPoint(CCPointZero);
		p->setColor(ccRED);
		p->setPosition(ccp(pTitle_c->getPositionX()+pTitle_c->getContentSize().width+10,pTitle_c->getPositionY()));
		pLayer->addChild(p);
	}
	else
	{
		std::string attrname;
		LuaData::getProp("gdStoneAttribute",currentlvl,"name",attrname);
		CCLabelTTF* p_c=CCLabelTTF::create(attrname.c_str(),"微软雅黑",14);
		p_c->setAnchorPoint(CCPointZero);
		p_c->setColor(ccGREEN);
		p_c->setPosition(Pos);
		pLayer->addChild(p_c);

		int allcount=0;
		LuaData::getProp("gdStoneAttribute",currentlvl,"reqcnt",allcount);
		std::string attrcount="("+SystemData::intToString(allcount)+"/"+SystemData::intToString(allcount)+")";
		CCLabelTTF* p_c1=CCLabelTTF::create(attrcount.c_str(),"微软雅黑",14);
		p_c1->setAnchorPoint(CCPointZero);
		p_c1->setColor(ccGREEN);
		p_c1->setPosition(ccp(p_c->getPositionX()+p_c->getContentSize().width+5,Pos.y));
		pLayer->addChild(p_c1);

		CCLabelTTF* p_cValue=CCLabelTTF::create(AToU8("（已激活）"),"微软雅黑",14);
		p_cValue->setAnchorPoint(CCPointZero);
		p_cValue->setColor(ccGREEN);
		p_cValue->setPosition(ccp(p_c->getPositionX()+p_c->getContentSize().width+p_c1->getContentSize().width+10,Pos.y));
		pLayer->addChild(p_cValue);

		Pos=ccp(Pos.x,Pos.y-p_c->getContentSize().height);

		int size=0;
		LuaData::getProp_size("gdStoneAttribute",currentlvl,"attr",size);
		for (int i=0;i<size;i++)
		{
			int value=0,type=0;
			std::string name;
			LuaData::getProp("gdStoneAttribute",currentlvl,"attr",i+1,"name",name);
			LuaData::getProp("gdStoneAttribute",currentlvl,"attr",i+1,"data","type",type,value);			
			CCLabelTTF* p=getSingleLabel(type,value,name);
			p->setPosition(Pos);
			pLayer->addChild(p);
			Pos=ccp(Pos.x,Pos.y-20);
		}
	}

	//下级效果：
	CCLabelTTF* pTitle_x=SystemData::getLabelTTF("Add_1_xiajixiaoguo");
	pTitle_x->setPosition(Pos);
	pTitle_x->setAnchorPoint(CCPointZero);
	pTitle_x->setColor(ccORANGE);
	pTitle_x->setFontSize(14);
	pLayer->addChild(pTitle_x);
	Pos=ccp(Pos.x,Pos.y-pTitle_x->getContentSize().height-5);

	std::string attrname; 
	LuaData::getProp("gdStoneAttribute",currentlvl+1,"name",attrname); 
	if (attrname=="0")
	{
		CCLabelTTF* p=CCLabelTTF::create(AToU8("无"),"微软雅黑",14);
		p->setAnchorPoint(CCPointZero);
		p->setColor(ccRED);
		p->setPosition(ccp(pTitle_x->getPositionX()+pTitle_x->getContentSize().width+10,pTitle_x->getPositionY()));
		pLayer->addChild(p);
	}
	else
	{
		std::string attrname;
		LuaData::getProp("gdStoneAttribute",currentlvl+1,"name",attrname);
		CCLabelTTF* p_x=CCLabelTTF::create(attrname.c_str(),"微软雅黑",14);
		p_x->setAnchorPoint(CCPointZero);
		p_x->setColor(ccGREEN);
		p_x->setPosition(Pos);
		pLayer->addChild(p_x);

		int count=checkSecond(currentlvl+1);
		int allcount=0;
		LuaData::getProp("gdStoneAttribute",currentlvl+1,"reqcnt",allcount);
		std::string attrcount="("+SystemData::intToString(count)+"/"+SystemData::intToString(allcount)+")";
		CCLabelTTF* p_x1=CCLabelTTF::create(attrcount.c_str(),"微软雅黑",14);
		p_x1->setAnchorPoint(CCPointZero);
		p_x1->setColor(ccGREEN);
		p_x1->setPosition(ccp(p_x->getPositionX()+p_x->getContentSize().width+5,Pos.y));
		pLayer->addChild(p_x1);

		CCLabelTTF* p_xFlag=CCLabelTTF::create(AToU8("(未激活)"),"微软雅黑",14);
		p_xFlag->setAnchorPoint(CCPointZero);
		p_xFlag->setColor(ccRED);
		p_xFlag->setPosition(ccp(p_x->getPositionX()+p_x->getContentSize().width+p_x1->getContentSize().width+10,Pos.y));
		pLayer->addChild(p_xFlag);

		Pos=ccp(Pos.x,Pos.y-p_x->getContentSize().height);

		int size=0;
		LuaData::getProp_size("gdStoneAttribute",currentlvl+1,"attr",size);
		for (int i=0;i<size;i++)
		{
			int value=0,type=0;
			std::string name;
			LuaData::getProp("gdStoneAttribute",currentlvl+1,"attr",i+1,"name",name);
			LuaData::getProp("gdStoneAttribute",currentlvl+1,"attr",i+1,"data","type",type,value);			
			CCLabelTTF* p=getSingleLabel(type,value,name,false);
			p->setPosition(Pos);
			pLayer->addChild(p);
			Pos=ccp(Pos.x,Pos.y-20);
		}
	}
	

	//加载layer
	m_iSecondHeight = (Pos.y < 0 ? -Pos.y : Pos.y) + 10;
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(ccp(0,m_iSecondHeight+m_iThirdHeight+m_iFourthHeight));
	this->addChild(pLayer);
}

void AdditonMenu::initThirdPart()
{
	//判断达到几层效果 
	int currentlvl = 0;
	if (m_bIsSelf)
	{
		currentlvl = HeroData::getProp(Entity::attr_reborn);
	}
	else
	{
		currentlvl = GameData::s_user->m_pOtherRole->mRebornlvl;
	}

	//标题
	CCLayer *pLayer=CCLayer::create();
	CCLabelTTF *ptitle=SystemData::getLabelTTF("attribute_Addition_zhuanshengxiaoguojiacheng");
	ptitle->setPosition(ccp(150,0));
	ptitle->setFontSize(18);
	ptitle->setColor(ccYELLOW);
	CCSprite *pback=SystemData::getSpriteByPlist("attribute_titleback");
	pback->setPosition(ptitle->getPosition());
	pLayer->addChild(pback);
	pLayer->addChild(ptitle);

	CCPoint Pos=ccp(5,0-pback->getContentSize().height);

	//当前效果：
	CCLabelTTF* pTitle_c=SystemData::getLabelTTF("Add_1_dangqianxiaoguo");
	pTitle_c->setPosition(Pos);
	pTitle_c->setAnchorPoint(CCPointZero);
	pTitle_c->setFontSize(14);
	pTitle_c->setColor(ccORANGE);
	pLayer->addChild(pTitle_c);
	Pos=ccp(Pos.x,Pos.y-pTitle_c->getContentSize().height-5);

	if (currentlvl==0)//如果当前没有加成效果 
	{
		CCLabelTTF* p=CCLabelTTF::create(AToU8("无"),"微软雅黑",14);
		p->setAnchorPoint(CCPointZero);
		p->setColor(ccRED);
		p->setPosition(ccp(pTitle_c->getPositionX()+pTitle_c->getContentSize().width+10,pTitle_c->getPositionY()));
		pLayer->addChild(p);
	}
	else
	{
		std::string attrname;
		LuaData::getProp("gdEvolutionAttribute",currentlvl,"name",attrname);
		CCLabelTTF* p_c=CCLabelTTF::create(attrname.c_str(),"微软雅黑",14);
		p_c->setAnchorPoint(CCPointZero);
		p_c->setColor(ccGREEN);
		p_c->setPosition(ccp(pTitle_c->getPositionX()+pTitle_c->getContentSize().width+10,pTitle_c->getPositionY()));
		pLayer->addChild(p_c);
		
		int size=0;
		LuaData::getProp_size("gdEvolutionAttribute",currentlvl,"attr",size);
		for (int i=0;i<size;i++)
		{
			int value=0,type=0;
			std::string name;
			LuaData::getProp("gdEvolutionAttribute",currentlvl,"attr",i+1,"name",name);
			LuaData::getProp("gdEvolutionAttribute",currentlvl,"attr",i+1,"data","type",type,value);			
			CCLabelTTF* p=getSingleLabel(type,value,name);
			p->setPosition(Pos);
			pLayer->addChild(p);
			Pos=ccp(Pos.x,Pos.y-20);
		}
		std::string str=""; 
		if (GameData::s_user->m_pMainRole->mGhostJob==UserData::CARRER_ZS)
		{
			str="zsattr";
		}
		else if (GameData::s_user->m_pMainRole->mGhostJob==UserData::CARRER_FS)
		{
			str="fsattr";
		}
		else if (GameData::s_user->m_pMainRole->mGhostJob==UserData::CARRER_DS)
		{
			str="dsattr";
		}
		LuaData::getProp_size("gdEvolutionAttribute",currentlvl,str,size);
		for (int i=0;i<size;i++)
		{
			int value=0,type=0;
			std::string name;
			LuaData::getProp("gdEvolutionAttribute",currentlvl,str,i+1,"name",name);
			LuaData::getProp("gdEvolutionAttribute",currentlvl,str,i+1,"data","type",type,value);			
			CCLabelTTF* p=getSingleLabel(type,value,name);
			p->setPosition(Pos);
			pLayer->addChild(p);
			Pos=ccp(Pos.x,Pos.y-20);
		}
	}

	//下级效果：
	CCLabelTTF* pTitle_x=SystemData::getLabelTTF("Add_1_xiajixiaoguo");
	pTitle_x->setPosition(Pos);
	pTitle_x->setAnchorPoint(CCPointZero);
	pTitle_x->setColor(ccORANGE);
	pTitle_x->setFontSize(14);
	pLayer->addChild(pTitle_x);
	Pos=ccp(Pos.x,Pos.y-pTitle_x->getContentSize().height-5);

	std::string attrname; 
	LuaData::getProp("gdEvolutionAttribute",currentlvl+1,"name",attrname); 
	if (attrname=="0")
	{
		CCLabelTTF* p=CCLabelTTF::create(AToU8("无"),"微软雅黑",14);
		p->setAnchorPoint(CCPointZero);
		p->setColor(ccRED);
		p->setPosition(ccp(pTitle_x->getPositionX()+pTitle_x->getContentSize().width+10,pTitle_x->getPositionY()));
		pLayer->addChild(p);
	}
	else
	{
		CCLabelTTF* p_x=CCLabelTTF::create(attrname.c_str(),"微软雅黑",14);
		p_x->setAnchorPoint(CCPointZero);
		p_x->setColor(ccGREEN);
		p_x->setPosition(ccp(pTitle_x->getPositionX()+pTitle_x->getContentSize().width+10,pTitle_x->getPositionY()));
		pLayer->addChild(p_x);


		//详细加成属性
		int size=0;
		LuaData::getProp_size("gdEvolutionAttribute",currentlvl+1,"attr",size);
		for (int i=0;i<size;i++)
		{
			int value=0,type=0;
			std::string name;
			LuaData::getProp("gdEvolutionAttribute",currentlvl+1,"attr",i+1,"name",name);
			LuaData::getProp("gdEvolutionAttribute",currentlvl+1,"attr",i+1,"data","type",type,value);			
			CCLabelTTF* p=getSingleLabel(type,value,name,false);
			p->setPosition(Pos);
			pLayer->addChild(p);
			Pos=ccp(Pos.x,Pos.y-20);
		}
		std::string str="";
		if (GameData::s_user->m_pMainRole->mGhostJob==UserData::CARRER_ZS)
		{
			str="zsattr";
		}
		else if (GameData::s_user->m_pMainRole->mGhostJob==UserData::CARRER_FS)
		{
			str="fsattr";
		}
		else if (GameData::s_user->m_pMainRole->mGhostJob==UserData::CARRER_DS)
		{
			str="dsattr";
		}
		LuaData::getProp_size("gdEvolutionAttribute",currentlvl+1,str,size);
		for (int i=0;i<size;i++)
		{
			int value=0,type=0;
			std::string name;
			LuaData::getProp("gdEvolutionAttribute",currentlvl+1,str,i+1,"name",name);
			LuaData::getProp("gdEvolutionAttribute",currentlvl+1,str,i+1,"data","type",type,value);			
			CCLabelTTF* p=getSingleLabel(type,value,name,false);
			p->setPosition(Pos);
			pLayer->addChild(p);
			Pos=ccp(Pos.x,Pos.y-20);
		}
	}

	//加载layer
	m_iThirdHeight = (Pos.y < 0 ? -Pos.y : Pos.y) + 10;
	pLayer->setAnchorPoint(CCPointZero);
	pLayer->setPosition(ccp(0,m_iThirdHeight+m_iFourthHeight));
	this->addChild(pLayer);
}

void AdditonMenu::initFourthPart()
{

}

CCLabelTTF* AdditonMenu::getSingleLabel( int type,int value ,std::string name,bool flag)
{
	//根据type 取字符串
	CCLabelTTF* p=CCLabelTTF::create(name.c_str(),"微软雅黑",14);
	p->setAnchorPoint(CCPointZero);
	p->setColor(ccWHITE);
	p->setFontSize(14);
	p->setPosition(CCPointZero);

	std::string str_;	
	if (type==Combat::prop_Start ||type==Combat::prop_HPMax+Combat::prop_Muti_Begin || type==Combat::prop_MPMax+Combat::prop_Muti_Begin ||type==Combat::prop_Health_Recovery_Point||type==Combat::prop_Magic_Recovery_Point)
	{
		float fValue=(float)value/100;
		str_="+"+SystemData::floatToString(fValue)+"%";
	}
	else
	{
		str_="+"+SystemData::intToString(value);
	}
	CCLabelTTF* pValue=CCLabelTTF::create(str_.c_str(),"微软雅黑",14);
	pValue->setColor(ccGREEN);
	pValue->setAnchorPoint(CCPointZero);
	pValue->setPosition(ccp(p->getContentSize().width+5,0));
	p->addChild(pValue);

	if (!flag)
	{
		p->setColor(ccGRAY);
		pValue->setColor(ccGRAY);
	}

	return p;
}

std::vector<int> AdditonMenu::checkFirst( int lvl )
{
	std::vector<int> list;
	int reqequiplvl=0;
	LuaData::getProp("gdEnhanceAttribute",lvl,"reqlvl",reqequiplvl);
	UserItems items ;
	if (m_bIsSelf)
	{
		items = GameData::s_user->getUserItemData()->userItems;
	}
	else
	{
		items = GameData::s_user->m_pOtherRole->m_pAllItemMap;
	}
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		if (it->second)
		{
			if (it->first>ItemPosition_stone_begin && it->first<0 && it->second->category==ItemCate_Equip)
			{
				int pos=it->second->position;
				if (pos==ItemPosition_Equip_Neckless ||
					pos==ItemPosition_Equip_Weapon ||
					pos==ItemPosition_Equip_Bangle ||
					pos==ItemPosition_Equip_Ring ||
					pos==ItemPosition_Equip_Stone ||
					pos==ItemPosition_Equip_Belt ||
					pos==ItemPosition_Equip_Shoes ||
					pos==ItemPosition_Equip_Ring_Two ||
					pos==ItemPosition_Equip_Bangle_Two ||
					pos==ItemPosition_Equip_Cloth ||
					pos==ItemPosition_Equip_Medal ||
					pos==ItemPosition_Equip_Helmet 				
					)
				{
					if (it->second->data[ItemEquip::Item_EnhanceLevel]>=reqequiplvl)
					{
						switch (pos)
						{
						case ItemPosition_Equip_Neckless:
							pos=0;
							break;
						case ItemPosition_Equip_Weapon:
							pos=1;
							break;
						case ItemPosition_Equip_Bangle:
							pos=2;
							break;
						case ItemPosition_Equip_Bangle_Two:
							pos=3;
							break;
						case ItemPosition_Equip_Ring:
							pos=4;
							break;
						case ItemPosition_Equip_Ring_Two:
							pos=5;
							break;
						case ItemPosition_Equip_Stone:
							pos=6;
							break;
						case ItemPosition_Equip_Belt:
							pos=7;
							break;
						case ItemPosition_Equip_Shoes:
							pos=8;
							break;
						case ItemPosition_Equip_Cloth:
							pos=9;
							break;
						case ItemPosition_Equip_Medal:
							pos=10;
							break;
						case ItemPosition_Equip_Helmet:
							pos=11;
							break;
						default:
							break;
						}
						list.push_back(pos);
					}
				}

			}
		}
	}

	return list;
}

int AdditonMenu::checkSecond( int lvl )
{
	//检测魂石符合的数量
	int count=0;
	int reqstonelvl=0;
	int reqstonecnt=0;
	LuaData::getProp("gdStoneAttribute",lvl,"reqlvl",reqstonelvl);
	LuaData::getProp("gdStoneAttribute",lvl,"reqcnt",reqstonecnt);

	/*UserItems items ;
	if (m_bIsSelf)
	{
		items = GameData::s_user->getUserItemData()->userItems;
	}
	else
	{
		items = GameData::s_user->m_pOtherRole->m_pAllItemMap;
	}*/
	for (int i = ItemPosition_Equip_Neckless ;i>ItemPosition_Equip_Foot;i--)//最大
	{

		UserItem* p = NULL;
		if (m_bIsSelf)
		{
			p = GameData::s_user->getUserItemData()->getItemByPosition(i);
		}
		else
		{
			p = GameData::s_user->m_pOtherRole->m_pAllItemMap[i];
		}
		if (p)
		{
			for (int j=0;j<5;j++)
			{
				UserItem* pUserItem;
				if (m_bIsSelf)
				{
					pUserItem=GameData::s_user->m_pMainRole->m_pStoneArray[-1-i][j];
				}
				else
				{
					pUserItem=GameData::s_user->m_pOtherRole->m_pStoneArray[-1-i][j];
				}
				if (pUserItem)
				{
					int cnt_int=0;
					std::string name=pUserItem->name;
					const char *c=name.c_str();
					for(int i=0;c[i]!='\0';++i)
					{
						if(c[i]>='0'&& c[i]<='9') //如果是数字.
						{
							cnt_int*=10;
							cnt_int+=c[i]-'0';
						}
					}
					if (cnt_int>=reqstonelvl)
					{
						count++;
					}
				}
			}
		}
	}

	/*for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{		
		if (it->first<ItemPosition_stone_begin && it->first>=ItemPosition_stone_end && it->second->category==ItemCate_Stone)
		{
			
		}
	}*/
	return count;
}

int AdditonMenu::checkEnhanceSize()
{
	int cnt =12;		
	if( Lua::instance()->call("g_get_enhance_attribute_size", 0, 1) 
		&& Lua::instance()->pop(cnt))
	{
		return cnt;
	}
	return cnt;
}



