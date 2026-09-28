#include "GuildCombatPanel.h"
#include "GuildPanel.h"
#include "GuildModule.h"
#include "EffectDefinition.h"
#include "WorldDefinition.h"

#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/StaticData.h"
#include "userdata/HeroData.h"
#include "userdata/WorldData.h"
#include "ext/CCMenuItemFontEx.h"
#include "ext/GeneralMenu.h"
#include "event/EventProtocol.h"

#include "network/HandleMessage.h"
#include "userdata/luadata/LuaData.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "ext/TouchCover.h"
#include "QuestDefinition.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "userdata/netdata/GhostManager.h"
#include "MsgScene.h"
#include "userdata/NPCFunctionData.h"
#include "scene/panel/EffectSprite.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/LayoutData.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "ModuleData.h"
#include "userdata/GuildData.h"
#include "utils/StringUtils.h"
#include "controls/CPComboBox.h"
#include "PopAlertPanel.h"

#include "module/ModuleData.h"
#include "userdata/LayoutData.h"
#include "res/CPAnimationManager.h"
#include "ActivityDefinition.h"
#include "userdata/ActivityData.h"
#include "element/AnimElement.h"
#include "element/ElementDefinition.h"
#include "controls/CPItemComponents.h"
#include "CCMenuItemFontEx.h"
#include "CCMenuItemFontColor.h"
#include "GuildDefinition.h"
#include "VIPModule.h"

//-----------------------------------------------------------------------------------------------------------//

GuildCombatPanel::GuildCombatPanel():
	m_pMainMenu(NULL)
	,m_iCurrentType(-1)
	,mHeight(0)
	,m_RewardGuild(NULL)
	,m_MasterGuild(NULL)
	,m_CombatTime(NULL)
	,m_DefGuild(NULL)
	,m_AtkGuild(NULL)
	,m_RewardItem(NULL)
	,m_EditJob(NULL)
{
	m_MasterReward.clear();
	m_MasterList.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
}

GuildCombatPanel::~GuildCombatPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
}

GuildCombatPanel* GuildCombatPanel::create()
{
	GuildCombatPanel* pPanel = new GuildCombatPanel();
	if(pPanel && pPanel->init(""))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("GuildPanel create failed!");
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL;
}


bool GuildCombatPanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCLog("_____2_______droid________%d,%d,%d,%s",
		ActivityData::getGCZData(Activity::GCZ_tmp_master_guild_id),
		ActivityData::getGCZData(Activity::GCZ_master_guild_id),
		ActivityData::getGCZData(Activity::GCZ_occupy_count),
		ActivityData::getGCZMasterName().c_str());

	m_iCurrentType=TAG_GUILDINFO;

	initFrame();
	initLabels();
	
	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero); 
	m_pMainMenu->setAnchorPoint(CCPointZero); 
	addChild(m_pMainMenu); 
	
	initButtons();  
	initRewards();
	if (WorldData::getWorldDataY(WorldDefination::city_own4days_reward) > 0)
		setReward(true);
	else
		setReward(false);
	/*
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(pLeftborder->getContentSize().width-15,pLeftborder->getContentSize().height-60),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(pLeftborder->getPositionX()+5,pLeftborder->getPositionY()+30));
	m_pTableView->setVerticalFillOrder(kCCTableViewFillTopDown);
	m_pMainMenu->addChild(m_pTableView);
	*/

	//if (GuildData::getMyGuildID()==ActivityData::getGCZData(Activity::GCZ_master_guild_id)
	//&&GuildData::getMyJob()<=GuildType::rank_second_master)
	//test
	if (GuildData::getMyJob()<=GuildType::post_second_master)
	{
		MsgGuildAllMemberInfoRequest* req = new MsgGuildAllMemberInfoRequest;
		HandleMessage::sendMessage(req);
	}

	if (GuildData::getMyGuildID() != 0)
	{
		MsgGuildGCZAttackListRequest *request = new MsgGuildGCZAttackListRequest();
		HandleMessage::sendMessage(request);
	}

	return true;
}

void GuildCombatPanel::comboCallBack(CCNode* pSender)
{
	CCLog("%s",__FUNCTION__);
	if(pSender)
	{
		int tag = pSender->getTag()-Combo_Start;
		if (tag==0)
		{

		}
		else if(tag==1)
		{		

		}
	}
}
void GuildCombatPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender); 
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Button_Preview)
		{
			int itemID = 0;
			StaticData::getCityMasterClothItemID(HeroData::getGender(), itemID);
			GuildClothesPreviewPanel* panel = GuildClothesPreviewPanel::create(itemID);
			panel->setAnchorPoint(CCPointZero);
			panel->setPosition(CCPointZero);
			addChild(panel);
		}
		else if(tag==Button_Rule)
		{		
			loadRuleView();
		}
		else if(tag==Button_Reward) 
		{		
			MsgGuildGCZGetJobRewardRequest* request = new MsgGuildGCZGetJobRewardRequest();
			HandleMessage::sendMessage(request);
		}
		else if(tag==Button_Query)
		{		
			loadQueryView();
		}
		else if(tag==Button_Edit_Job)
		{
			// 只有沙城城主才有权限打开沙城职位设置界面
			if (isSandCityMaster())
			{
				GuildJobSettingPanel* panel = GuildJobSettingPanel::create(0);
				panel->setAnchorPoint(CCPointZero);
				panel->setPosition(CCPointZero);
				addChild(panel);
			}
		}
		else if(tag==Alert_Askforcombat)
		{	
			PopAlertPanel* pAlert = dynamic_cast<PopAlertPanel*>(pSender);
			if (pAlert)
			{
				if (pAlert->isPressConfirm())
				{
					MsgGuildApplyGCZRequest* req = new MsgGuildApplyGCZRequest;
					HandleMessage::sendMessage(req);
				}
				else
				{
					//CCLayer* pShopPanel=ShopPanel::create();
					//Game::getGameUI()->addChild(pShopPanel);
					//CPEventHelper::openPanel("ShopPanel",ShopPanel::TAG_SHOP_COMMONLY_USED,40046,0,0);
					CPEventHelper::openPanel("ShopPanel");
				}
			}
		}
		else if (tag == Button_Occupy_Reward)
		{
			MsgGuildGczOccupyRewardRequest* request = new MsgGuildGczOccupyRewardRequest();
			HandleMessage::sendMessage(request);
		}
	}
	
}
void GuildCombatPanel::applyGCZ( CCObject* pSender )
{
	PopAlertPanel* alert = PopAlertPanel::create();
	alert->setConfirmTitle(SystemData::getLayoutString("popalert.info.askforcombat.yes"));
	alert->setCancelTitle(SystemData::getLayoutString("popalert.info.askforcombat.no"));
	alert->setConfirmTarget(this,menu_selector(GuildCombatPanel::MenuCallBack));
	alert->setCancelTarget(this,menu_selector(GuildCombatPanel::MenuCallBack));
	alert->setTag(Alert_Askforcombat);
	addChild(alert);

	CCLabelTTF* label1 = SystemData::getLabelTTF("popalert.info.askforcombat.notice");
	label1->setColor(ccRED);
	label1->setFontSize(18);    
	label1->setHorizontalAlignment(kCCTextAlignmentCenter);
	label1->setAnchorPoint(ccp(0.5,1));
	label1->setPosition(ccp(400,300));
	alert->addChild(label1);

	CCLabelTTF* label2 = SystemData::getLabelTTF("popalert.info.askforcombat.alert");
	label2->setColor(ccYELLOW);
	label2->setFontSize(18);    
	label2->setHorizontalAlignment(kCCTextAlignmentCenter);
	label2->setAnchorPoint(ccp(0.5,1));
	label2->setPosition(ccp(400,260));
	alert->addChild(label2);
}
void GuildCombatPanel::loadQueryView()
{
	PopAlertPanel* alert = PopAlertPanel::create(PopAlertPanel::Type_Small,1); 
	alert->setConfirmTarget(this,menu_selector(GuildCombatPanel::applyGCZ));
	alert->setConfirmTitle(SystemData::getLayoutString("popalert.button.askforcombat"));
	alert->showLine(true); 
	addChild(alert); 
	
	CCLabelTTF* plabel1=SystemData::getLabelTTF("guild.combat.alert.label.tomorrow");
	plabel1->setColor(ccYELLOW);
	plabel1->setFontSize(18);
	//plabel1->setAnchorPoint(CCPointZero);
	//plabel1->setHorizontalAlignment(kCCTextAlignmentLeft);
	alert->addChild(plabel1);

	std::string str = LayoutData::getString(CPModuleName::GUILD, "gczNotOpen");
	CCLabelTTF *nextCombatTime = CCLabelTTF::create(str.c_str(), "Consolas", 18);
	nextCombatTime->setPosition(ccp(plabel1->getPositionX() + plabel1->getContentSize().width,
		plabel1->getPositionY()));
	nextCombatTime->setColor(ccGREEN);
	//nextCombatTime->setFontSize(18);
	nextCombatTime->setAnchorPoint(ccp(0.0f, 0.5f));
	//nextCombatTime->setHorizontalAlignment(kCCTextAlignmentLeft);
	alert->addChild(nextCombatTime);

	CCLabelTTF* plabel2=SystemData::getLabelTTF("guild.combat.alert.label.sign");
	plabel2->setColor(ccYELLOW);
	plabel2->setFontSize(18);
	alert->addChild(plabel2);

	CCSize pPlacardSize = CCSizeMake(238,145);
	CCPoint pPlacardPoint = ccp(300,155);
	CCSize itemSize = CCSizeMake(238,30);
	CPItemComponents* m_SwitchMenu = CPItemComponents::create(pPlacardSize, new CPLayoutList(CCSizeZero,true));
	m_SwitchMenu->setPosition(pPlacardPoint);
	m_SwitchMenu->setAnchorPoint(CCPointZero);
	alert->addChild(m_SwitchMenu);

	for (int i=0;i<GuildData::getGCZAttackGuildCnt();i++)  
	{  
		CCNode *node = CCNode::create();
		node->setContentSize(itemSize);
		m_SwitchMenu->addItem(node);
		
		CCLabelTTF* label = CCLabelTTF::create(GuildData::getGCZAttackGuildName(i).c_str(),"Arial",18);
		label->setAnchorPoint(ccp(0,0));
		node->addChild(label);
		label->setColor(ccYELLOW);
	} 
}
void GuildCombatPanel::loadRuleView()
{
	PopAlertPanel* alert = PopAlertPanel::create(PopAlertPanel::Type_Big,1);
	alert->setConfirmTitle(SystemData::getLayoutString("operate.tips.yes"));
	alert->setTitle(SystemData::getLayoutString("popalert.info.rule.title"));
	addChild(alert);

	CCSize size = CCSizeMake(500,240);//SystemData::getLayoutSize("openactivity.alert.label.content"); 
	CPRichText* pText=NPCFunctionData::getBigContent(SystemData::getLayoutValue("popalert.info.bigcontent.rule"),size.width,size.height); 
	pText->setAnchorPoint(ccp(0.5,0.5));
	pText->setPosition(ccp(alert->getContentSize().width/2,alert->getContentSize().height/2));//setPosition(SystemData::getLayoutPoint("openactivity.alert.label.content")); 
	alert->addChild(pText);
}
cocos2d::CCSize GuildCombatPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("taskcontent_leftmenu_size").width-20, mHeight);
}

cocos2d::extension::CCTableViewCell* GuildCombatPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCMenuEx* pMenu = CCMenuEx::create(NULL,NULL);
		pMenu->setAnchorPoint(CCPointZero);
		pMenu->setPosition(CCPointZero);
		cell->addChild(pMenu);

	}
	return cell;
}

unsigned int GuildCombatPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void GuildCombatPanel::initMasterInfo()
{
	time_t now = ActivityData::getWorldTime();
	struct tm *local = localtime(&now);

	for (int i = 1; i <= 5; ++i)
	{
		CCLabelTTF* mTitle = SystemData::getLabelTTF("guild.combat.label.name" + StringUtils::toString(i));
		mTitle->setColor(ccWHITE);
		mTitle->setFontSize(18);
		mTitle->setAnchorPoint(CCPointZero);
		mTitle->setHorizontalAlignment(kCCTextAlignmentLeft); 
		addChild(mTitle);

		
		CCLabelTTF* mName = SystemData::getLabelTTF("popalert.info.mastername.null");
		mName->setColor(ccYELLOW);
		mName->setFontSize(18);
		mName->setTag(i+Job_Start);
		mName->setAnchorPoint(ccp(0,0.5));
		mName->setHorizontalAlignment(kCCTextAlignmentLeft); 
		mName->setPosition(SystemData::getLayoutPoint("guild.combat.label.combobox" + StringUtils::toString(i)));
		mName->setPositionX(mName->getPositionX()-80);
		
		std::string realName = WorldData::getWorldDataS(WorldDefination::prop_gcz_job_master + i - 1);
		if (!realName.empty() && realName != "0" && local->tm_wday != 4)
			mName->setString(realName.c_str());
		else
			mName->setString("");
		
		addChild(mName);
		/*
		CPComboBox* mComboBox = LayoutData::getComboBox(CPModuleName::COMMON, "normal");
		mComboBox->setScale(0.7);
		mComboBox->setChangeHandler(this,callfuncN_selector(GuildCombatPanel::comboCallBack));
		CCPoint pos = SystemData::getLayoutPoint("guild.combat.label.combobox" + StringUtils::toString(i));
		mComboBox->setPosition(pos); 
		mComboBox->setTag(Combo_Start+i);
		addChild(mComboBox);
		for (int j = 0; j <= 4; j++)
		{
			const std::string &key = "Target" + StringUtils::toString(j);
			mComboBox->addLabelItem(key);
		}
		m_MasterList.push_back(mComboBox);
		*/
		/*
		CCLabelTTF* mLabel = SystemData::getLabelTTF("guild.combat.label.reward" + StringUtils::toString(i));
		mLabel->setColor(ccWHITE);
		mLabel->setFontSize(14); 
		mLabel->setAnchorPoint(CCPointZero); 
		mLabel->setHorizontalAlignment(kCCTextAlignmentLeft); 
		addChild(mLabel); 
		m_MasterReward.push_back(mLabel);
		*/
	}
	CCSize size = CCSizeMake(150,125);//SystemData::getLayoutSize("openactivity.alert.label.content"); 
	CPRichText* pText=NPCFunctionData::getBigContent(SystemData::getLayoutValue("popalert.info.bigcontent.rewardinfo"),size.width,size.height); 
	pText->setAnchorPoint(ccp(0.5,0.5)); 
	pText->setPosition(ccp(610,320));//setPosition(SystemData::getLayoutPoint("openactivity.alert.label.content")); 
	addChild(pText);
}

void GuildCombatPanel::refreshMasterInfo()
{
	for (int i = 1; i <= 5; ++i)
	{
		CCNode *node = this->getChildByTag(Job_Start + i);
		if (!node)
			continue;

		CCLabelTTF* name = dynamic_cast<CCLabelTTF*>(node);
		if (!name)
			continue;

		std::string realName = WorldData::getWorldDataS(WorldDefination::prop_gcz_job_master + i - 1);
		if (realName.empty())
			realName = SystemData::getLayoutString("popalert.info.mastername.null");

		name->setString(realName.c_str());
	}
}

/*
void GuildCombatPanel::refreshGCZAttackList()
{
	m_GCZAttackList.clear();

	SubModuleData::init(CPModuleName::GUILD, CPGuildData::GCZ_ATTACK_GUILD_LIST);
	int size = 0;
	SubModuleData::getSize(size);
	for (int i = 0; i < size; ++i)
	{
		std::string guildName;
		SubModuleData::getString(i, CPGuildData::GUILD_NAME, guildName);
		m_GCZAttackList.push_back(guildName);
	}


}
*/

void GuildCombatPanel::initFrame()
{
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",SystemData::getLayoutValue("guild.bg.w"),SystemData::getLayoutValue("guild.bg.h"));
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(SystemData::getLayoutPoint("guild.bg"));
	addChild(bg);
	//城主时装
	CCScale9Sprite *pClothes=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.combat.frame.clothes.w"),SystemData::getLayoutValue("guild.combat.frame.clothes.h"));
	pClothes->setAnchorPoint(CCPointZero);
	pClothes->setPosition(SystemData::getLayoutPoint("guild.combat.frame.clothes"));    
	addChild(pClothes); 
	//城主信息 
	CCScale9Sprite *pMaster=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.combat.frame.master.w"),SystemData::getLayoutValue("guild.combat.frame.master.h"));
	pMaster->setAnchorPoint(CCPointZero);
	pMaster->setPosition(SystemData::getLayoutPoint("guild.combat.frame.master"));  
	addChild(pMaster);

	//奖励
	CCScale9Sprite *pReward=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.combat.frame.reward.w"),SystemData::getLayoutValue("guild.combat.frame.reward.h"));
	pReward->setAnchorPoint(CCPointZero);  
	pReward->setPosition(SystemData::getLayoutPoint("guild.combat.frame.reward")); 
	addChild(pReward);	
	
	//攻城战信息
	CCScale9Sprite *pInfo=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.combat.frame.info.w"),SystemData::getLayoutValue("guild.combat.frame.info.h"));
	pInfo->setAnchorPoint(CCPointZero);  
	pInfo->setPosition(SystemData::getLayoutPoint("guild.combat.frame.info")); 
	addChild(pInfo);
	
	CCSprite *clothesImg = LayoutData::getSprite(CPModuleName::GUILD, "combatShiZhuang");
	addChild(clothesImg);
	
	CCSprite *weaponImg = LayoutData::getSprite(CPModuleName::GUILD, "combatHuanWu");
	addChild(weaponImg);

	for (int i=0;i<1;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
		CCPoint point = SystemData::getLayoutPoint("guild.combat.sprite.item"+StringUtils::toString(i));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point);
		addChild(sprite);
	}
}

void GuildCombatPanel::initLabels()
{
	const float combatInfoTile = 85.0f;

	time_t now = ActivityData::getWorldTime();
	struct tm *local = localtime(&now);

	CCScale9Sprite* ptitle1=SystemData::getScale9SpriteByPlist("guild.combat.label.clothes");//SystemData::getSprite("guild.combat.label.clothes");
	//ptitle1->setPosition(SystemData::getLayoutPoint("guild.combat.label.clothes"));
	addChild(ptitle1);
	CCLabelTTF* plabel1=SystemData::getLabelTTF("guild.combat.label.clothes.text");
	plabel1->setColor(ccYELLOW);
	plabel1->setFontSize(18);
	plabel1->setPosition(ccp(ptitle1->getContentSize().width/2,ptitle1->getContentSize().height/2));
	ptitle1->addChild(plabel1);

	CCScale9Sprite* ptitle2=SystemData::getScale9SpriteByPlist("guild.combat.label.master");
	//ptitle2->setPosition(SystemData::getLayoutPoint("guild.combat.label.master"));
	addChild(ptitle2);
	CCLabelTTF* plabel2=SystemData::getLabelTTF("guild.combat.label.master.text");
	plabel2->setColor(ccYELLOW);
	plabel2->setFontSize(18);
	plabel2->setPosition(ccp(ptitle2->getContentSize().width/2,ptitle2->getContentSize().height/2));
	ptitle2->addChild(plabel2);
	
	CCScale9Sprite* ptitle3=SystemData::getScale9SpriteByPlist("guild.combat.label.reward");
	//ptitle3->setPosition(SystemData::getLayoutPoint("guild.combat.label.reward"));
	addChild(ptitle3);
	CCLabelTTF* plabel3=SystemData::getLabelTTF("guild.combat.label.reward.text");
	plabel3->setColor(ccYELLOW);
	plabel3->setFontSize(18);
	plabel3->setPosition(ccp(ptitle3->getContentSize().width/2,ptitle3->getContentSize().height/2));
	ptitle3->addChild(plabel3);

	CCScale9Sprite* ptitle4=SystemData::getScale9SpriteByPlist("guild.combat.label.info"); 
	//ptitle4->setPosition(SystemData::getLayoutPoint("guild.combat.label.info")); 
	addChild(ptitle4); 
	CCLabelTTF* plabel4=SystemData::getLabelTTF("guild.combat.label.info.text"); 
	plabel4->setColor(ccYELLOW);
	plabel4->setFontSize(18);
	plabel4->setPosition(ccp(ptitle4->getContentSize().width/2,ptitle4->getContentSize().height/2));
	ptitle4->addChild(plabel4);

	CCLabelTTF* masterguild = SystemData::getLabelTTF("guild.combat.label.masterguild");
	masterguild->setColor(ccWHITE);
	masterguild->setFontSize(18);
	masterguild->setAnchorPoint(CCPointZero);
	masterguild->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(masterguild);
	m_MasterGuild = SystemData::getLabelTTF("guild.combat.label.masterguild");
	m_MasterGuild->setPosition(ccp(masterguild->getPositionX()+combatInfoTile,masterguild->getPositionY()));
	m_MasterGuild->setColor(ccYELLOW);
	m_MasterGuild->setFontSize(18);
	m_MasterGuild->setAnchorPoint(CCPointZero);
	m_MasterGuild->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_MasterGuild);
	std::string masterName = WorldData::getWorldDataS(WorldDefination::city_master_guild);
	if (masterName.empty() || masterName == "0" || local->tm_wday == 4)	// ActivityData::getGCZMasterName()方法在不存在时返回字符串"0"
	{
		//masterName = SystemData::getLayoutString("popalert.info.mastername.null");
		masterName.clear();
	}
	m_MasterGuild->setString(masterName.c_str());

	m_RewardItem = SystemData::getLabelTTF("guild.combat.label.rewarditem");
	m_RewardItem->setColor(ccWHITE);
	m_RewardItem->setFontSize(18);
	m_RewardItem->setAnchorPoint(CCPointZero);
	m_RewardItem->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_RewardItem);
	CCLabelTTF* rewardguild = SystemData::getLabelTTF("guild.combat.label.rewardguild");
	rewardguild->setColor(ccWHITE);
	rewardguild->setFontSize(18);
	rewardguild->setAnchorPoint(CCPointZero);
	rewardguild->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(rewardguild);
	m_RewardGuild = SystemData::getLabelTTF("guild.combat.label.rewardguild");
	m_RewardGuild->setPosition(ccp(rewardguild->getPositionX()+combatInfoTile,rewardguild->getPositionY()));
	m_RewardGuild->setColor(ccWHITE);
	m_RewardGuild->setFontSize(18);
	m_RewardGuild->setAnchorPoint(CCPointZero);
	m_RewardGuild->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_RewardGuild);
	std::string occupyDay = StringUtils::toString(WorldData::getWorldDataZ(WorldDefination::city_master_guild))
		+ SystemData::getLayoutString("guild.combat.label.rewardguild.day");
	m_RewardGuild->setString(occupyDay.c_str());

	CCLabelTTF *gainer = LayoutData::getLabelTTF(CPModuleName::GUILD, "bdGczOccupyRewardGainer");
	addChild(gainer);

	const std::string str = gainer->getString() + WorldData::getWorldDataS(WorldDefination::city_own4days_reward);
	gainer->setString(str.c_str());

	CCLabelTTF* iteminfo = SystemData::getLabelTTF("guild.combat.label.iteminfo");
	iteminfo->setColor(ccGREEN);
	iteminfo->setFontSize(12); 
	iteminfo->setAnchorPoint(CCPointZero);
	iteminfo->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(iteminfo);
	
	CCLabelTTF* combattime = SystemData::getLabelTTF("guild.combat.label.combattime");
	combattime->setColor(ccWHITE);
	combattime->setFontSize(18);
	combattime->setAnchorPoint(CCPointZero);
	combattime->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(combattime);
	m_CombatTime = SystemData::getLabelTTF("guild.combat.label.combattime");
	m_CombatTime->setPosition(ccp(combattime->getPositionX()+combatInfoTile,combattime->getPositionY()));
	m_CombatTime->setColor(ccGREEN);
	m_CombatTime->setFontSize(18);
	m_CombatTime->setAnchorPoint(CCPointZero);
	m_CombatTime->setHorizontalAlignment(kCCTextAlignmentLeft);

	
	std::string combatTimeStr;
	if (local->tm_wday == 4)
	{
		combatTimeStr = LayoutData::getString(CPModuleName::GUILD, "gczNotOpen");
	}
	else
	{
		combatTimeStr = LayoutData::getString(CPModuleName::GUILD, "gczTime");
	}
	m_CombatTime->setString(combatTimeStr.c_str());
	addChild(m_CombatTime);

	CCLabelTTF* defguild = SystemData::getLabelTTF("guild.combat.label.defguild"); 
	defguild->setColor(ccWHITE);
	defguild->setFontSize(18);
	defguild->setAnchorPoint(CCPointZero);
	defguild->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(defguild);
	m_DefGuild = SystemData::getLabelTTF("guild.combat.label.defguild");
	m_DefGuild->setPosition(ccp(defguild->getPositionX()+combatInfoTile,defguild->getPositionY()));
	m_DefGuild->setColor(ccGREEN);
	m_DefGuild->setFontSize(18);
	m_DefGuild->setAnchorPoint(CCPointZero);
	m_DefGuild->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_DefGuild);
	m_DefGuild->setString(masterName.c_str());
	/*
	CCLabelTTF* atkguild = SystemData::getLabelTTF("guild.combat.label.atkguild");
	atkguild->setColor(ccWHITE);
	atkguild->setFontSize(18);
	atkguild->setAnchorPoint(CCPointZero);
	atkguild->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(atkguild);
	*/
	/*
	m_AtkGuild = SystemData::getLabelTTF("guild.combat.label.atkguild");
	m_AtkGuild->setPosition(ccp(atkguild->getPositionX()+combatInfoTile,atkguild->getPositionY()));
	m_AtkGuild->setColor(ccGREEN);
	m_AtkGuild->setFontSize(18);
	m_AtkGuild->setAnchorPoint(CCPointZero);
	m_AtkGuild->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_AtkGuild);
	*/
	//master job
	initMasterInfo();

	//CCSize pPlacardSize = CCSizeMake(138,55);
	//CCPoint pPlacardPoint = ccp(550,50);
	//CCSize itemSize = CCSizeMake(238,30);
	//CPItemComponents* m_SwitchMenu = CPItemComponents::create(pPlacardSize, new CPLayoutList(CCSizeZero,true));
	//m_SwitchMenu->setPosition(pPlacardPoint);
	//m_SwitchMenu->setAnchorPoint(CCPointZero);
	//addChild(m_SwitchMenu);

	////for (OptionsList::iterator iter=m_OptionsList.begin();iter!=m_OptionsList.end();iter++,i++)  
	//for (int i=0;i<GuildData::getGCZLastAttackGuildCnt();i++)  
	//{  
	//	CCNode *node = CCNode::create();
	//	node->setContentSize(itemSize);
	//	m_SwitchMenu->addItem(node);

	//	CCLabelTTF* label = CCLabelTTF::create(GuildData::getGCZLastAttackGuildName(i).c_str(),"Arial",18);
	//	label->setAnchorPoint(ccp(0,0));
	//	node->addChild(label);
	//	label->setColor(ccYELLOW);
	//} 
	/*
	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.browse.title.rank");
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRank);

	CCLabelTTF* tName = SystemData::getLabelTTF("guild.browse.title.name");
	tName->setColor(ccWHITE);
	tName->setFontSize(18);     
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tName);

	CCLabelTTF* tMaster = SystemData::getLabelTTF("guild.browse.title.master");
	tMaster->setColor(ccWHITE);
	tMaster->setFontSize(18);   
	tMaster->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tMaster);

	CCLabelTTF* tNum = SystemData::getLabelTTF("guild.browse.title.num");
	tNum->setColor(ccWHITE);
	tNum->setFontSize(18);   
	tNum->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tNum);

	CCLabelTTF* tRelation = SystemData::getLabelTTF("guild.browse.title.relation");
	tRelation->setColor(ccWHITE);
	tRelation->setFontSize(18);   
	tRelation->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRelation);

	CCLabelTTF* tStatus = SystemData::getLabelTTF("guild.browse.title.status");
	tStatus->setColor(ccWHITE);
	tStatus->setFontSize(18);   
	tStatus->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tStatus);
	*/
}

void GuildCombatPanel::initButtons()
{
	CCSize s1 = SystemData::getLayoutSize("guild.combat.button.preview");
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.combat.button.frame",s1.width,s1.height);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.combat.button.frame.sel",s1.width,s1.height);
	CCMenuItemSprite *preview =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildCombatPanel::MenuCallBack));//行会信息按钮
	if(preview)
	{ 
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.combat.button.preview.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		preview->setTag(Button_Preview);
		preview->setPosition(SystemData::getLayoutPoint("guild.combat.button.preview"));
		pLabel->setPosition(preview->getPosition());
		m_pMainMenu->addChild(preview);
		m_pMainMenu->addChild(pLabel);
	}

	CCSize s2 = SystemData::getLayoutSize("guild.combat.button.rule");
	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.combat.button.frame",s2.width,s2.height);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.combat.button.frame.sel",s2.width,s2.height);
	CCMenuItemSprite *rule =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(GuildCombatPanel::MenuCallBack));//行会信息按钮
	if(rule)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.combat.button.rule.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		rule->setTag(Button_Rule);
		rule->setPosition(SystemData::getLayoutPoint("guild.combat.button.rule"));
		pLabel->setPosition(rule->getPosition());
		m_pMainMenu->addChild(rule);
		m_pMainMenu->addChild(pLabel);
	}

	CCSize s3 = SystemData::getLayoutSize("guild.combat.button.reward");
	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.combat.button.frame",s3.width,s3.height);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.combat.button.frame.sel",s3.width,s3.height);
	CCMenuItemSprite *reward =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(GuildCombatPanel::MenuCallBack));
	if(reward)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.combat.button.reward.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		reward->setTag(Button_Reward);
		reward->setPosition(SystemData::getLayoutPoint("guild.combat.button.reward"));
		pLabel->setPosition(reward->getPosition());
		m_pMainMenu->addChild(reward);
		m_pMainMenu->addChild(pLabel);

		if (!canGetSandCityReward())
		{
			reward->setVisible(false);
			pLabel->setVisible(false);
		}
	}

	CCSize s4 = SystemData::getLayoutSize("guild.combat.button.query");
	CCScale9Sprite* p4=SystemData::getScale9SpriteByPlist("guild.combat.button.frame",s4.width,s4.height);
	CCScale9Sprite* pSel4=SystemData::getScale9SpriteByPlist("guild.combat.button.frame.sel",s4.width,s4.height);
	CCMenuItemSprite *query =CCMenuItemSprite::create(p4,pSel4,NULL,this,menu_selector(GuildCombatPanel::MenuCallBack));
	if(query)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.combat.button.query.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		query->setTag(Button_Query);
		query->setPosition(SystemData::getLayoutPoint("guild.combat.button.query"));
		pLabel->setPosition(query->getPosition());
		m_pMainMenu->addChild(query);
		m_pMainMenu->addChild(pLabel);
		time_t now = time(NULL);
		struct tm *local = localtime(&now);
		if (local->tm_wday != 4)
			query->setEnabled(false);
	}

	CCSize s5 = SystemData::getLayoutSize("guild.combat.button.edit");
	CCScale9Sprite* p5=SystemData::getScale9SpriteByPlist("guild.combat.button.frame",s5.width,s5.height);
	CCScale9Sprite* pSel5=SystemData::getScale9SpriteByPlist("guild.combat.button.frame.sel",s5.width,s5.height);
	m_EditJob =CCMenuItemSprite::create(p5,pSel5,NULL,this,menu_selector(GuildCombatPanel::MenuCallBack));
	if(m_EditJob)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.combat.button.edit.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		m_EditJob->setTag(Button_Edit_Job); 
		m_EditJob->setPosition(SystemData::getLayoutPoint("guild.combat.button.edit")); 
		//pLabel->setPosition(m_EditJob->getPosition());
		pLabel->setPosition(ccp(s5.width/2,s5.height/2));
		pLabel->setAnchorPoint(ccp(0.5,0.5));
		m_pMainMenu->addChild(m_EditJob);
		m_EditJob->addChild(pLabel);
		if (!isSandCityMaster())
		{
			m_EditJob->setVisible(false);
			pLabel->setVisible(false);
		}
	}

	CCMenuItemSprite* occupyReward = LayoutData::getMenuItemLabelImage(CPModuleName::GUILD, "getGczOccupyReward");
	if (occupyReward)
	{
		occupyReward->setTag(Button_Occupy_Reward);
		occupyReward->setTarget(this, menu_selector(GuildCombatPanel::MenuCallBack));
		m_pMainMenu->addChild(occupyReward);
	}
}

void GuildCombatPanel::setReward(bool isReward)
{
	if (isReward)
	{
		CCSprite* isReward = SystemData::getSpriteByPlist("guild.combat.sprite.hasreward");
		addChild(isReward);
	}
}
void GuildCombatPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageCreateGuildResponse")
		{

		}
		else if(source == "HandleMessageGuildsInfoResponse")
		{
			
		}
		else if(source == "HandleMessageGuildAllMemberInfoResponse")
		{
			if (m_EditJob)
			{
				m_EditJob->setVisible(true);
			}
		}
		else if (source == "HandleMessageGuildGCZSetJobResponse")
		{
			refreshMasterInfo();
		}
	}
}

void GuildCombatPanel::initRewards()
{
	for (int i=0;i<1;i++)
	{
		CCPoint point = SystemData::getLayoutPoint("guild.combat.sprite.item"+StringUtils::toString(i));
		int sid = SystemData::getLayoutValue("guild.combat.sprite.item"+StringUtils::toString(i)+".sid");
		int cnt = SystemData::getLayoutValue("guild.combat.sprite.item"+StringUtils::toString(i)+".cnt");
		if (sid>0&&cnt>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid);
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIcon(item);
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(GuildCombatPanel::itemCallBack));
			m_pMainMenu->addChild(pItem);

			CCSprite* pSprite=EffectSprite::create(Effect::effect_xiyou_libao);
			pSprite->setPosition(pItem->getPosition());
			m_pMainMenu->addChild(pSprite);
		} 
	}
}
void GuildCombatPanel::showTooltip(CCMenuItem* pImage)
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

void GuildCombatPanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		showTooltip(pImage);
	}
}

bool GuildCombatPanel::isSandCityMaster()
{
	int sandCityGuildId = WorldData::getWorldDataX(WorldDefination::city_master_guild);

	if (sandCityGuildId != 0 && GuildData::getMyGuildID() == sandCityGuildId
		&& HeroData::getPID() == GuildData::getMyGuildMasterID())
		return true;

	return false;
}

bool GuildCombatPanel::canGetSandCityReward()
{
	int sandCityGuildId = WorldData::getWorldDataX(WorldDefination::city_master_guild);

	if (sandCityGuildId != 0 && GuildData::getMyGuildID() == sandCityGuildId)
	{
		int pid = HeroData::getPID();
		for (int i = WorldDefination::prop_gcz_job_master;
			i <= WorldDefination::prop_gcz_job_manager; ++i)
		{
			if (WorldData::getWorldDataX(i) == pid
				&& WorldData::getWorldDataY(i) == 0)
				return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////
GuildClothesPreviewPanel::GuildClothesPreviewPanel()
	:m_pMainMenu(NULL)
	,m_selIndex(-1)
	,m_background(NULL)
{

}

GuildClothesPreviewPanel::~GuildClothesPreviewPanel()
{

}

GuildClothesPreviewPanel* GuildClothesPreviewPanel::create(int tag)
{
	GuildClothesPreviewPanel* pPanel = new GuildClothesPreviewPanel();
	if(pPanel && pPanel->init(tag))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("GuildClothesPreviewPanel create failed!");
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL; 
}

bool GuildClothesPreviewPanel::init( int tag)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_selIndex = tag;

	this->setZOrder(999);

	m_nHeight = SystemData::size_y+1000;
	m_nWidth = SystemData::size_x+1000;

	addCover(ccp(-1000,-1000));

	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_background->addChild(m_pMainMenu);

	initLabels();
	initButtons();

	return true;
}

void GuildClothesPreviewPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		closeSelf();		
	}
}

void GuildClothesPreviewPanel::closeSelf()
{
	this->removeFromParentAndCleanup(true);
}

void GuildClothesPreviewPanel::initFrame()
{
	CCSize bgSize = SystemData::getLayoutSize("guild.combat.frame.item.preview");
	CCPoint bgPoint = SystemData::getLayoutPoint("guild.combat.frame.item.preview");
	m_background=SystemData::getScale9SpriteByPlist("guild.combat.frame.item.preview",bgSize.width,bgSize.height);
	m_background->setPosition(bgPoint);  
	addChild(m_background);

	AnimElement *anim = AnimElement::create(0, CPElement::Type::player, UserData::SEX_FEMALE);
	anim->setCloth(m_selIndex);
	anim->setScale(2);
	anim->setAnchorPoint(ccp(0.5,0.5));
	anim->setPosition(ccp(675, 600));
	m_background->addChild(anim);
}

void GuildClothesPreviewPanel::initLabels()
{

}

void GuildClothesPreviewPanel::initButtons()
{
	
}
bool GuildClothesPreviewPanel::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	closeSelf();
	return true;
}

////////////////////////////////////////////////////////////////////////////////
GuildJobSettingPanel::GuildJobSettingPanel()
	:m_pMainMenu(NULL)
	,m_selIndex(-1)
	,m_background(NULL)
	,m_SwitchMenu(NULL)
	,m_SwitchJob(NULL)
{
	m_JobList.clear();
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

GuildJobSettingPanel::~GuildJobSettingPanel()
{
	m_JobList.clear();
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

GuildJobSettingPanel* GuildJobSettingPanel::create(int tag)
{
	GuildJobSettingPanel* pPanel = new GuildJobSettingPanel();
	if(pPanel && pPanel->init(tag))
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("GuildClothesPreviewPanel create failed!");
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL; 
}


bool GuildJobSettingPanel::init( int tag)
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_selIndex = tag;

	this->setZOrder(999);

	m_nHeight = SystemData::size_y+1000;
	m_nWidth = SystemData::size_x+1000;

	addCover(ccp(-1000,-1000));

	initFrame();

	//主要menu
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero);
	m_background->addChild(m_pMainMenu);

	initLabels();
	initButtons();

	return true;
}

void GuildJobSettingPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (!pNode)
		return;
	int tag = pNode->getTag();
	switch (tag)
	{
	case Button_Close:
		closeSelf();
		break;
	case Button_Confirm:
		{
			for (unsigned int i = 0; i < m_JobsPid.size(); ++i)
			{
				if (m_JobsPid[i] == 0)
					continue;

				MsgGuildGCZSetJobRequestEx *request = new MsgGuildGCZSetJobRequestEx();
				request->job = WorldDefination::prop_gcz_job_deputy + i;
				request->pid = m_JobsPid[i];
				HandleMessage::sendMessage(request);
				closeSelf();
			}
		}
		break;
	default:
		closeSelf();
		break;
	}
}

void GuildJobSettingPanel::closeSelf()
{
	this->removeFromParentAndCleanup(true);
}

void GuildJobSettingPanel::initFrame()
{
	m_background = SystemData::getSpriteByPlist("openactivity.alert.frame.background");
	m_background->setAnchorPoint(ccp(0.5,0.5));  
	addChild(m_background);

	CCSize bgSize1 = CCSizeMake(540,90);
	CCPoint bgPoint1 = ccp(281.5,233);
	CCScale9Sprite *bg1=SystemData::getScale9SpriteByPlist("openactivity.alert.frame.scalebg",bgSize1.width,bgSize1.height);
	bg1->setAnchorPoint(ccp(0.5,0));
	bg1->setPosition(bgPoint1); 
	m_background->addChild(bg1);

	CCSize bgSize2 = CCSizeMake(540,160);
	CCPoint bgPoint2 = ccp(281.5,68);
	CCScale9Sprite *bg2=SystemData::getScale9SpriteByPlist("openactivity.alert.frame.scalebg",bgSize2.width,bgSize2.height);
	bg2->setAnchorPoint(ccp(0.5,0));
	bg2->setPosition(bgPoint2); 
	m_background->addChild(bg2);
	
	const CCSize switchSize = CCSizeMake(540-20, 80);
	CCPoint switchPoint = ccp(11.5+270, 68+10+200);
	CCSize layoutSize = CCSizeMake(520/2, 40);
	m_SwitchJob = CPItemComponents::create(switchSize, new CPLayoutGrid(2, layoutSize, true));
	m_SwitchJob->setPosition(switchPoint);
	m_background->addChild(m_SwitchJob);
	for (int i = 0; i < 4; i++)
	{
		CCMenuItem *btn = getJobView(i);
		btn->setTarget(this, menu_selector(GuildJobSettingPanel::onSelectjob));
		m_SwitchJob->addItem(btn);
		btn->setTag(i);
		if (i==m_selIndex)
		{
			m_SwitchJob->setCurrentIndex(m_selIndex);
		}
	}
	
	m_JobsPid.resize(m_JobList.size());

	CCSize pPlacardSize = CCSizeMake(540-20,160-20);
	CCPoint pPlacardPoint = ccp(11.5+10,68+10);
	CCSize itemSize = CCSizeMake(520/3,30);
	
	m_SwitchMenu = CPItemComponents::create(pPlacardSize, new CPLayoutGrid(3, itemSize, true));
	m_SwitchMenu->setPosition(pPlacardPoint);
	m_SwitchMenu->setAnchorPoint(CCPointZero);
	m_background->addChild(m_SwitchMenu);

	refreshMemberList();
}
CCMenuItem * GuildJobSettingPanel::getJobView( int index )
{
	const CCSize &size = LayoutData::getSize(CPModuleName::VIP, "normalRechargeListItem");
	CCSprite *norm = LayoutData::getSprite(CPModuleName::VIP, "rechargeValueCheckedBoard");
	CCSprite *sel = LayoutData::getSprite(CPModuleName::VIP, "rechargeValueCheckedBoard");
	CCSprite *flag = LayoutData::getSprite(CPModuleName::VIP, "rechargeValueCheckedFlag");
	sel->addChild(flag);
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	ret->setContentSize(size);

	CCLabelTTF *label = SystemData::getLabelTTF("guild.combat.alert.label.name"+StringUtils::toString(index));
	label->setFontSize(18); 
	label->setColor(ccYELLOW);
	label->setAnchorPoint(CCPointZero);
	label->setHorizontalAlignment(kCCTextAlignmentLeft);
	ret->addChild(label);
	//label->setString((SystemData::getLayoutString("guild.combat.alert.label.name"+StringUtils::toString(index))+"1234234").c_str());
	m_JobList.push_back(label);
	return ret;
} 
void GuildJobSettingPanel::initLabels()
{
	/*
	CCSize size = SystemData::getLayoutSize("openactivity.alert.label.content"); 
	CPRichText* pText=NPCFunctionData::getBigContent(ActivityDataHelper::getOpenActivityInfo(m_selIndex+1),size.width,size.height); 
	pText->setAnchorPoint(ccp(0.5,0.5));
	pText->setPosition(SystemData::getLayoutPoint("openactivity.alert.label.content")); 
	addChild(pText);

	CCLabelTTF* label1 = SystemData::getLabelTTF("openactivity.alert.label.page");
	label1->setHorizontalAlignment(kCCTextAlignmentCenter); 
	addChild(label1);
	label1->setString(ActivityDataHelper::getOpenActivityTitle(m_selIndex+1).c_str());
	*/
}

void GuildJobSettingPanel::initButtons()
{
	
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.placard.button",100,45);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",100,45); 
	CCMenuItemSprite *button =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildJobSettingPanel::MenuCallBack));
	if(button)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("openactivity.alert.button.ok.label"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button->setTag(Button_Confirm);
		button->setPosition(ccp(m_background->getContentSize().width/2,40));
		pLabel->setPosition(button->getPosition()); 
		m_pMainMenu->addChild(button); 
		m_pMainMenu->addChild(pLabel); 
	}
	
	CCMenuItemImage* button2 = SystemData::getMenuItemImageByPlist("openactivity.alert.button.close");
	button2->setTarget(this,menu_selector(GuildJobSettingPanel::MenuCallBack));
	button2->setAnchorPoint(ccp(1,1));
	button2->setPosition(m_background->getContentSize().width,m_background->getContentSize().height);
	button2->setTag(Button_Close);
	m_pMainMenu->addChild(button2);
	
}
void GuildJobSettingPanel::onSelectjob( CCObject *target )
{
	CCNode* pNode = dynamic_cast<CCNode*>(target); 
	if(pNode)
	{
		int tag = pNode->getTag();
		m_selIndex = tag;
	}
}

void GuildJobSettingPanel::onSelectMember(CCObject *target)
{
	CCNode* pNode = dynamic_cast<CCNode*>(target); 
	if(pNode)
	{
		int tag = pNode->getTag();
		
		if (m_selIndex < m_JobList.size() && m_selIndex >= 0)
		{
			CCLabelTTF* label = m_JobList[m_selIndex];
			if (label)
			{
				std::string str = SystemData::getLayoutString("guild.combat.alert.label.name"+StringUtils::toString(m_selIndex));
				std::string name = m_MemberList[tag].name;
				if (name.empty())
				{
					name = SystemData::getLayoutString("popalert.info.mastername.null");
				}
				label->setString((str+name).c_str());
				m_JobsPid[m_selIndex] = m_MemberList[tag].pid;
				keepOnly(m_selIndex);
			}
		}

	}
}

void GuildJobSettingPanel::keepOnly(int index)
{
	int size = m_JobsPid.size();
	for (int i = 0; i < size; ++i)
	{
		if (i == index)
			continue;

		if (m_JobsPid[i] == m_JobsPid[index])
		{
			m_JobsPid[i] = 0;
			CCLabelTTF* label = m_JobList[i];
			if (label == NULL)
				continue;

			std::string str = SystemData::getLayoutString("guild.combat.alert.label.name"+StringUtils::toString(i));
			label->setString(str.c_str());
		}
	}
}

void GuildJobSettingPanel::refreshMemberPanel()
{
	m_SwitchMenu->removeAllItems();
	CCSize itemSize = CCSizeMake(520/3, 30);

	for (unsigned int i = 0; i < m_MemberList.size(); ++i)
	{
		CCNode *node = CCNode::create();

		m_SwitchMenu->addItem(node);
		node->setContentSize(itemSize);
		CCMenu *menu = CCMenu::create();
		menu->setPosition(CCPointZero);
		node->addChild(menu);

		CCMenuItemFont *btn = CCMenuItemFont::create(GuildData::getGuildMemberName(i).c_str(),
			this, menu_selector(GuildJobSettingPanel::onSelectMember));
		btn->setFontSize(20); 
		btn->setFontSizeObj(20); 
		btn->setAnchorPoint(ccp(0, 1));
		btn->setPosition(ccp(0, itemSize.height));
		menu->addChild(btn, 0, i);
		btn->setColor(ccYELLOW);
		btn->setTag(i);
		btn->setString(m_MemberList[i].name.c_str());
	}
}

void GuildJobSettingPanel::refreshMemberList()
{
	m_MemberList.clear();

	int size = GuildData::getGuildMemberCnt();
	for (int i = 0; i < size; ++i)
	{
		// 会长自己无需出现在列表中
		if (GuildData::getGuildMemberNickname(i) == GuildType::post_master)
			continue;

		GuildMemberInfo tmp;
 		tmp.pid = GuildData::getGuildMemberPID(i);
 		tmp.name = GuildData::getGuildMemberName(i);
 		tmp.level = GuildData::getGuildMemberLevel(i);
 		tmp.job = GuildData::getGuildMemberJob(i);
 		tmp.post = GuildData::getGuildMemberNickname(i);
 		tmp.contribution = GuildData::getGuildMemberContribution(i);
 		tmp.todaycontribution = GuildData::getGuildMemberTodayContribution(i);
 		m_MemberList.push_back(tmp);
	}

	refreshMemberPanel();
}

void GuildJobSettingPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE
		&& (source == "HandleMessageGuildMemberChangeNotify"
			|| source == "HandleMessageDeleteGuildMemberResponse"))
	{
		refreshMemberList();
	}
}
