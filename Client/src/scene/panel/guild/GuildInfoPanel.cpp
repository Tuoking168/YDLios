#include "GuildInfoPanel.h"
#include "GuildPanel.h"
#include "MsgScene.h"
#include "QuestDefinition.h"

#include "userdata/netdata/GameRole.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/StaticData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/GhostManager.h"
#include "userdata/NPCFunctionData.h"

#include "ext/CCMenuItemFontEx.h"
#include "ext/GeneralMenu.h"

#include "event/EventProtocol.h"

#include "network/HandleMessage.h"

#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "ext/TouchCover.h"

#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/SceneHelper.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
 
#include "GuildChatPanel.h"
#include "GuildEventPanel.h"
#include "event/CPEventDispatcher.h"
#include "event/CPEventHelper.h"
#include "ModuleData.h"
#include "userdata/GuildData.h"
#include "PopAlertPanel.h"
#include "userdata/LayoutData.h"
#include "SceneDefinition.h"
#include "ext/TextField.h"
#include "scene/panel/shop/ShopPanel.h"
#include "ChatModule.h"
#include "GuildPanel.h"
#include "utils/StringUtils.h"
#include "DonateKeyboard.h"
#include "GuildDefinition.h"
#include "userdata/HeroData.h"
//-----------------------------------------------------------------------------------------------------------//


GuildInfoPanel::GuildInfoPanel():
	m_pMainMenu(NULL),
	mHeight(0),
	m_iCurrentQuestID(0),
	m_pInfo(NULL),
	m_pCurrentQuestSprite(NULL),
	m_PlacardSel(0),
	m_SpriteGuildWelfare(NULL),
	m_LabelGuildWelfare(NULL),
	m_ConvoyGo(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

GuildInfoPanel::~GuildInfoPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_FINISH, this);
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

GuildInfoPanel* GuildInfoPanel::create()
{
	GuildInfoPanel* pPanel = new GuildInfoPanel();
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


bool GuildInfoPanel::init( const char* filename )
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	initFrame();

	CCSprite* ptitle1=SystemData::getSpriteByPlist("guild.label.guildinfo");
	ptitle1->setPosition(SystemData::getLayoutPoint("guild.label.guildinfo"));
	addChild(ptitle1);
	CCLabelTTF* plabel1=SystemData::getLabelTTF("guild.label.guildinfo.text");
	plabel1->setColor(ccWHITE);
	plabel1->setFontSize(18);
	plabel1->setPosition(ccp(ptitle1->getContentSize().width/2,ptitle1->getContentSize().height/2));
	ptitle1->addChild(plabel1);

	CCSprite* ptitle2=SystemData::getSpriteByPlist("guild.label.myinfo");
	ptitle2->setPosition(SystemData::getLayoutPoint("guild.label.myinfo"));
	addChild(ptitle2);
	CCLabelTTF* plabel2=SystemData::getLabelTTF("guild.label.myinfo.text");
	plabel2->setColor(ccWHITE);
	plabel2->setFontSize(18);   
	plabel2->setPosition(ccp(ptitle1->getContentSize().width/2,ptitle1->getContentSize().height/2));
	ptitle2->addChild(plabel2);

	initLabels();

	//主要menu  
	m_pMainMenu = GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	m_pMainMenu->setAnchorPoint(CCPointZero); 
	addChild(m_pMainMenu);
	
	initActivity();

	initButtons();

	CCSize pPlacardSize = CCSizeMake(SystemData::getLayoutValue("guild.info.placard.w"),SystemData::getLayoutValue("guild.info.placard.h"));
	CCPoint pPlacardPoint = SystemData::getLayoutPoint("guild.info.placard");
	m_pTableView = CCTableViewEx::create(this,CCSizeMake(pPlacardSize.width,pPlacardSize.height),kCCScrollViewDirectionVertical,this,NULL);
	m_pTableView->setAnchorPoint(CCPointZero);	
	m_pTableView->setPosition(ccp(pPlacardPoint.x,pPlacardPoint.y));
	addChild(m_pTableView); 

	updateSwitchButtons(Placard_Private);

	loadGuildInfo();
	loadMyInfo();

	return true;
}

cocos2d::CCSize GuildInfoPanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(SystemData::getLayoutSize("guild.info.placard").width-20, 200);
}

cocos2d::extension::CCTableViewCell* GuildInfoPanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();
		CCSize cellSize = cellSizeForTable(table);
		const float side = 5.0f;
		
		m_LabelGuildPlacard = CCLabelTTF::create("Placrad","Arial",18);
		m_LabelGuildPlacard->setAnchorPoint(ccp(0,1));
		m_LabelGuildPlacard->setPosition(ccp(side,cellSize.height-side));
		m_LabelGuildPlacard->setHorizontalAlignment(kCCTextAlignmentLeft); 
		m_LabelGuildPlacard->setDimensions(CCSizeMake(cellSize.width-side*2,cellSize.height-side*2));
		m_LabelGuildPlacard->setColor(ccYELLOW);
		cell->addChild(m_LabelGuildPlacard);
	}

	loadPlacard(m_PlacardSel);
	
	return cell;
}

unsigned int GuildInfoPanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

void GuildInfoPanel::tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell)
{
	changePlacardView();
}

void GuildInfoPanel::CloseSelf(CCObject* pSender)
{
	Game::getGameUI()->hidePanel(TAG_MAIN_PANEL);	
}

void GuildInfoPanel::handleEvent( int channel )
{	
	if(channel == EventProtocol::EVENT_TASK_RECEIVED)
	{
		//CCLog("Event Recieve");
	}
}

void GuildInfoPanel::initLabels()
{
	float spaceWidth = 110.0f;
	CCLabelTTF* tName = SystemData::getLabelTTF("guild.label.guildinfo.title.name");
	tName->setColor(ccWHITE);
	tName->setFontSize(18);     
	tName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tName);
	m_LabelGuildName = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildName->setPosition(ccp(tName->getPosition().x+spaceWidth,tName->getPosition().y));
	m_LabelGuildName->setColor(ccGREEN);  
	m_LabelGuildName->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildName);

	CCLabelTTF* tMaster = SystemData::getLabelTTF("guild.label.guildinfo.title.master");
	tMaster->setColor(ccWHITE);
	tMaster->setFontSize(18);   
	tMaster->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tMaster);
	m_LabelGuildMaster = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildMaster->setPosition(ccp(tMaster->getPosition().x+spaceWidth,tMaster->getPosition().y));
	m_LabelGuildMaster->setColor(ccGREEN);  
	m_LabelGuildMaster->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildMaster);

	CCLabelTTF* tRank = SystemData::getLabelTTF("guild.label.guildinfo.title.rank");
	tRank->setColor(ccWHITE);
	tRank->setFontSize(18);
	tRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tRank);
	m_LabelGuildRank = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildRank->setPosition(ccp(tRank->getPosition().x+spaceWidth,tRank->getPosition().y));
	m_LabelGuildRank->setColor(ccGREEN);  
	m_LabelGuildRank->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildRank);

	CCLabelTTF* tNum = SystemData::getLabelTTF("guild.label.guildinfo.title.num");
	tNum->setColor(ccWHITE);
	tNum->setFontSize(18);   
	tNum->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tNum);
	m_LabelGuildNum = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildNum->setPosition(ccp(tNum->getPosition().x+spaceWidth,tNum->getPosition().y)); 
	m_LabelGuildNum->setColor(ccGREEN);  
	m_LabelGuildNum->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildNum);

	CCLabelTTF* tMoney = SystemData::getLabelTTF("guild.label.guildinfo.title.money");
	tMoney->setColor(ccWHITE);
	tMoney->setFontSize(18);   
	tMoney->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tMoney);
	m_LabelGuildMoney = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildMoney->setPosition(ccp(tMoney->getPosition().x+spaceWidth,tMoney->getPosition().y));
	m_LabelGuildMoney->setColor(ccGREEN);  
	m_LabelGuildMoney->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildMoney);

	CCLabelTTF* tJob = SystemData::getLabelTTF("guild.label.guildinfo.title.job");
	tJob->setColor(ccWHITE);
	tJob->setFontSize(18);   
	tJob->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tJob);
	m_LabelGuildJob = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildJob->setPosition(ccp(tJob->getPosition().x + 100,tJob->getPosition().y));
	m_LabelGuildJob->setColor(ccGREEN);  
	m_LabelGuildJob->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildJob);

	CCLabelTTF* tNickname = SystemData::getLabelTTF("guild.label.guildinfo.title.nickname");
	tNickname->setColor(ccWHITE);
	tNickname->setFontSize(18);   
	tNickname->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tNickname);
	m_LabelGuildNickname = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildNickname->setPosition(ccp(tNickname->getPosition().x + 100,tNickname->getPosition().y));
	m_LabelGuildNickname->setColor(ccGREEN);  
	m_LabelGuildNickname->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildNickname);

	CCLabelTTF* tContribution = SystemData::getLabelTTF("guild.label.guildinfo.title.contribution");
	tContribution->setColor(ccWHITE);
	tContribution->setFontSize(18);   
	tContribution->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tContribution);
	m_LabelGuildContribution = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildContribution->setPosition(ccp(tContribution->getPosition().x + 100,tContribution->getPosition().y));
	m_LabelGuildContribution->setColor(ccGREEN);  
	m_LabelGuildContribution->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildContribution);

	CCLabelTTF* tWelfare = SystemData::getLabelTTF("guild.label.guildinfo.title.welfare");
	tWelfare->setColor(ccWHITE);
	tWelfare->setFontSize(18);   
	tWelfare->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(tWelfare);
	m_LabelGuildWelfare = CCLabelTTF::create("Loading","Arial",18);
	m_LabelGuildWelfare->setPosition(ccp(tWelfare->getPosition().x+100,tWelfare->getPosition().y));
	m_LabelGuildWelfare->setColor(ccGREEN);  
	m_LabelGuildWelfare->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildWelfare);

	m_LabelGuildPlacardCount =  SystemData::getLabelTTF("guild.label.guildinfo.title.placardcount");
	m_LabelGuildPlacardCount->setColor(ccWHITE);
	m_LabelGuildPlacardCount->setFontSize(15);   
	m_LabelGuildPlacardCount->setHorizontalAlignment(kCCTextAlignmentLeft); 
	addChild(m_LabelGuildPlacardCount); 
}

void GuildInfoPanel::initActivity()
{
	std::vector<std::string> activityName;
	activityName.push_back("guild.info.activity.chat");
	activityName.push_back("guild.info.activity.event");
	activityName.push_back("guild.info.activity.building");
	activityName.push_back("guild.info.activity.convoy");
	activityName.push_back("guild.info.activity.askforcombat");
	activityName.push_back("guild.info.activity.querycombat");
	int activityTag[6]={Activity_Chat,
		Activity_Event,
		Activity_Building,
		Activity_Convoy,
		Activity_Askforcombat,
		Activity_Querycombat};
	vector<std::string>::iterator iter; 
	int i = 0;
	for (iter=activityName.begin();iter!=activityName.end();iter++,i++)  
    {  
		CCMenuItemImage* button = SystemData::getMenuItemImageByPlist(*iter); 
		button->setTag(activityTag[i]);  
		button->setTarget(this,menu_selector(GuildInfoPanel::MenuCallBack));
		m_pMainMenu->addChild(button); 
	}

	CCMenu *convoyMenu = CCMenu::create();
	convoyMenu->setPosition(CCPointZero);
	m_pMainMenu->addChild(convoyMenu);

	m_ConvoyGo = SystemData::getMenuItemImageByPlist("guild.info.activity.convoy.go"); 
	m_ConvoyGo->setTag(Activity_ConvoyGo);
	m_ConvoyGo->setScale(0.8f);
	m_ConvoyGo->setTarget(this,menu_selector(GuildInfoPanel::MenuCallBack));
	convoyMenu->addChild(m_ConvoyGo);
	showConvoy(false);
}


void GuildInfoPanel::initButtons()
{
	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("guild.info.button",60,35);
	CCScale9Sprite* pSel1=SystemData::getScale9SpriteByPlist("guild.info.button.sel",60,35);
	CCMenuItemSprite *pDonate =CCMenuItemSprite::create(p1,pSel1,NULL,this,menu_selector(GuildInfoPanel::MenuCallBack));
	if(pDonate)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.info.button.donate.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pDonate->setTag(Button_Donate);
		pDonate->setPosition(SystemData::getLayoutPoint("guild.info.button.donate"));
		pLabel->setPosition(pDonate->getPosition());
		m_pMainMenu->addChild(pDonate);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("guild.info.button",105,35);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("guild.info.button.sel",105,35);
	CCMenuItemSprite *pLeave =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(GuildInfoPanel::MenuCallBack));
	if(pLeave)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.info.button.leave.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pLeave->setTag(Button_Leave);
		pLeave->setPosition(SystemData::getLayoutPoint("guild.info.button.leave"));
		pLabel->setPosition(pLeave->getPosition());
		m_pMainMenu->addChild(pLeave);
		m_pMainMenu->addChild(pLabel);
	}

	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("guild.info.button",105,35);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("guild.info.button.sel",105,35);
	CCMenuItemSprite *pGet =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(GuildInfoPanel::MenuCallBack));
	if(pGet)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.info.button.get.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccWHITE);
		pGet->setTag(Button_GetReward);
		pGet->setPosition(SystemData::getLayoutPoint("guild.info.button.get"));
		pLabel->setPosition(pGet->getPosition());
		m_pMainMenu->addChild(pGet);
		m_pMainMenu->addChild(pLabel);
	}


}
void GuildInfoPanel::initFrame()
{
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("guild.bigmenuback",SystemData::getLayoutValue("guild.bg.w"),SystemData::getLayoutValue("guild.bg.h"));
	bg->setAnchorPoint(CCPointZero);
	bg->setPosition(SystemData::getLayoutPoint("guild.bg"));
	addChild(bg);
	//行会信息
	CCScale9Sprite *infoview=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.info.infoview.w"),SystemData::getLayoutValue("guild.info.infoview.h"));
	infoview->setAnchorPoint(CCPointZero);
	infoview->setPosition(SystemData::getLayoutPoint("guild.info.infoview"));
	addChild(infoview);
	//我的信息
	CCScale9Sprite *myinfoview=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.info.myinfo.w"),SystemData::getLayoutValue("guild.info.myinfo.h"));
	myinfoview->setAnchorPoint(CCPointZero);
	myinfoview->setPosition(SystemData::getLayoutPoint("guild.info.myinfo"));
	addChild(myinfoview);
	//右侧大框
	CCScale9Sprite *pRightborder=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.info.rightbg.w"),SystemData::getLayoutValue("guild.info.rightbg.h"));
	pRightborder->setAnchorPoint(CCPointZero);  
	pRightborder->setPosition(SystemData::getLayoutPoint("guild.info.rightbg")); 
	addChild(pRightborder);	
	//公告
	CCScale9Sprite *pPlacard=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.info.placard.w"),SystemData::getLayoutValue("guild.info.placard.h"));
	pPlacard->setAnchorPoint(CCPointZero);  
	pPlacard->setPosition(SystemData::getLayoutPoint("guild.info.placard")); 
	addChild(pPlacard);	
	//帮派活动
	CCScale9Sprite *pActivity=SystemData::getScale9SpriteByPlist("guild.menuback",SystemData::getLayoutValue("guild.info.activity.w"),SystemData::getLayoutValue("guild.info.activity.h"));
	pActivity->setAnchorPoint(CCPointZero);  
	pActivity->setPosition(SystemData::getLayoutPoint("guild.info.activity"));       
	addChild(pActivity);	
}
void GuildInfoPanel::showConvoy(bool isShow)
{
	if (!m_ConvoyGo)
		return;
	m_ConvoyGo->setVisible(isShow);
}
void GuildInfoPanel::loadGuildInfo()
{
	std::string s_LabelGuildRank = StringUtils::toString(GuildData::getMyGuildRank());
	std::string s_LabelGuildNum = StringUtils::toString(GuildData::getMyGuildMemberCount());
	std::string s_LabelGuildMoney = StringUtils::toString(GuildData::getGuildProp(GuildType::guild_money));

	m_LabelGuildName->setString(GuildData::getMyGuildName().c_str());
	m_LabelGuildMaster->setString(GuildData::getMyGuildMasterName().c_str());
	m_LabelGuildRank->setString(s_LabelGuildRank.c_str());
	m_LabelGuildNum->setString(s_LabelGuildNum.c_str());
	m_LabelGuildMoney->setString(s_LabelGuildMoney.c_str());
}
void GuildInfoPanel::loadPlacard(int tag)
{
	std::string s_LabelGuildPlacard;
	std::string s_LabelGuildPlacardCount;
	if (tag==Placard_Private)
	{
		s_LabelGuildPlacard = GuildData::getGuildStringProp(GuildType::guild_private_notice);
	}
	else
	{
		s_LabelGuildPlacard = GuildData::getGuildStringProp(GuildType::guild_public_notice);
	}

	const int count = s_LabelGuildPlacard.length();
	s_LabelGuildPlacardCount = StringUtils::toString(count)
		+ "/"
		+ StringUtils::toString(SystemData::getLayoutValue("guild.info.label.placard.inputframe.maxlength"));
	
	m_LabelGuildPlacard->setString(s_LabelGuildPlacard.c_str());
	m_LabelGuildPlacardCount->setString(s_LabelGuildPlacardCount.c_str());
}
void GuildInfoPanel::loadMyInfo()
{
	int job = HeroData::getProp(Entity::attr_guild_post);
	std::string s_LabelGuildContribution = StringUtils::toString(HeroData::getProp(Entity::attr_guild_contribution));

	std::string s_LabelGuildWelfare;

	m_LabelGuildJob->setString(GuildData::getDefaultNickname(job).c_str()); 
	m_LabelGuildNickname->setString(GuildData::getGuildNickname(job).c_str());

	m_LabelGuildContribution->setString(s_LabelGuildContribution.c_str());
	if (GuildData::getJobRewardCount(job)>0)
	{
		s_LabelGuildWelfare = "x"+StringUtils::toString(GuildData::getJobRewardCount(job));

		if (m_SpriteGuildWelfare)
		{
			m_SpriteGuildWelfare->removeFromParentAndCleanup(true);
			m_SpriteGuildWelfare = NULL; 
		}

		const int rewardItemSid = GuildData::getJobReward(job);
		if (rewardItemSid > 0)
		{
			m_SpriteGuildWelfare = LayoutData::getItemIcon(rewardItemSid);
			m_SpriteGuildWelfare->setScale(0.5);
			m_SpriteGuildWelfare->setPosition(SystemData::getLayoutPoint("guild.label.guildinfo.sprite.welfare"));
			addChild(m_SpriteGuildWelfare);        
		}
	}
	else
	{
		s_LabelGuildWelfare = SystemData::getLayoutString("guild.info.myinfo.welfare.null");
	}
	m_LabelGuildWelfare->setString(s_LabelGuildWelfare.c_str());

}

void GuildInfoPanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (tag==Activity_Chat)
		{
			//CPEventHelper::setEventIntData(CPEventName::UI_OPEN, CPEventData::VALUE_2, ChatDefinition::type_guild);
			CPEventHelper::openPanel("ChatPanel", ChatDefinition::type_guild, 0, 0, 0);
		}
		else if (tag==Activity_Event)
		{
			CPEventHelper::uiNotify("GuildInfoPanel", "", Error::FeaturesNotYetOpen);
			return;

			GuildEventPanel* panel = GuildEventPanel::create();
			addChild(panel);
		}
		else if(tag==Activity_Building)
		{	
			CPEventHelper::openPanel("GuildBuildingPanel");
		}
		else if(tag==Activity_Convoy)
		{	
			showConvoy(!m_ConvoyGo->isVisible());
		}
		else if(tag==Activity_ConvoyGo)
		{
			int npcID = 0;
			StaticData::getGuildConvoyNPC(npcID);
			if (npcID > 0)
			{
				SceneHelper::teleportToNPCRequest(npcID);
			}
		}
		else if(tag==Activity_Askforcombat)
		{		
			PopAlertPanel* alert = PopAlertPanel::create();
			alert->setConfirmTitle(SystemData::getLayoutString("popalert.info.askforcombat.yes"));
			alert->setCancelTitle(SystemData::getLayoutString("popalert.info.askforcombat.no"));
			alert->setConfirmTarget(this,menu_selector(GuildInfoPanel::MenuCallBack));
			alert->setCancelTarget(this,menu_selector(GuildInfoPanel::MenuCallBack));
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
		else if(tag==Activity_Querycombat)
		{		
			CPEventHelper::uiNotify("SwitchGuildCombat", "", 0);
		}
		else if(tag==Button_Donate)
		{		
			GuildDonatePanel* panel = GuildDonatePanel::create();
			addChild(panel);
		}
		else if(tag==Button_Leave)
		{		
			PopAlertPanel* alert = PopAlertPanel::create();
			alert->setString(SystemData::getLayoutString("popalert.info.leave.alert"));
			alert->setConfirmTarget(this,menu_selector(GuildInfoPanel::MenuCallBack));
			alert->setTag(Alert_Leave_Confirm);
			addChild(alert);
		}
		else if(tag==Button_GetReward)
		{		
			MsgGuildRewardRequest* req = new MsgGuildRewardRequest();
			HandleMessage::sendMessage(req);
		}
		else if(tag==Placard_Private)
		{		
			updateSwitchButtons(Placard_Private);
		}
		else if(tag==Placard_Public)
		{		
			updateSwitchButtons(Placard_Public);
		}
		else if(tag==Alert_Leave_Confirm)
		{		
			MsgLeaveGuildRequest* req = new MsgLeaveGuildRequest();
			HandleMessage::sendMessage(req);
		}
		else if(tag==Alert_Change_Placard)
		{
			CCEditBox* textfield = (CCEditBox*)pNode->getChildByTag(Alert_Change_Placard);
			if (!textfield)
			{
				return;
			}
			
			if (m_PlacardSel==Placard_Private)
			{
				MsgGuildPlacardChangeRequest* placard = new MsgGuildPlacardChangeRequest();
				placard->placard = textfield->getText();
				HandleMessage::sendMessage(placard);
			}
			else
			{
				MsgGuildPublicNoticeChangeRequest* placard = new MsgGuildPublicNoticeChangeRequest();
				placard->publicnotice = textfield->getText();
				HandleMessage::sendMessage(placard);
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
					CPEventHelper::openPanel("ShopPanel");
				}
			}
		}

	}
}
void GuildInfoPanel::changePlacardView()
{
	CCSize alertSize = SystemData::getLayoutSize("popalert.normal");
	PopAlertPanel* alert = PopAlertPanel::create();
	alert->setConfirmTarget(this,menu_selector(GuildInfoPanel::MenuCallBack));
	alert->setTag(Alert_Change_Placard);
	addChild(alert);

	CCEditBox *ret = NULL;
	CCScale9Sprite *scaleSprite = CCScale9Sprite::createWithSpriteFrameName(SystemData::getLayoutString("guild.info.label.placard.inputframe").c_str());
	if (!scaleSprite)
	{
		scaleSprite = CCScale9Sprite::create(SystemData::getLayoutString("guild.info.label.placard.inputframe").c_str());
	}
	if (scaleSprite)
	{
		ret = CCEditBox::create(SystemData::getLayoutSize("guild.info.label.placard.inputframe"), scaleSprite);
		ret->setMaxLength(SystemData::getLayoutValue("guild.info.label.placard.inputframe.maxlength"));
		ret->setPlaceHolder(SystemData::getLayoutString("guild.info.label.placard.inputframe.placeholder").c_str());
		ret->setFontName(SystemData::getLayoutString("guild.info.label.placard.inputframe.font").c_str());
		ret->setPlaceholderFontName(SystemData::getLayoutString("guild.info.label.placard.inputframe.font").c_str());
		ret->setFontSize(SystemData::getLayoutValue("guild.info.label.placard.inputframe.fontsize"));
		ret->setPlaceholderFontSize(SystemData::getLayoutValue("guild.info.label.placard.inputframe.fontsize"));
		ret->setAnchorPoint(ccp(0.5,0.5));
		ret->setPosition(SystemData::getLayoutPoint("guild.info.label.placard.inputframe"));
		ret->setTouchPriority(kCCMenuHandlerPriority);
		ret->setTag(Alert_Change_Placard); 
		alert->addChild(ret);

		if (m_PlacardSel == Placard_Private)
		{
			ret->setText(GuildData::getGuildStringProp(GuildType::guild_private_notice).c_str());
		}
		else
		{
			ret->setText(GuildData::getGuildStringProp(GuildType::guild_public_notice).c_str());
		}
	}
}
void GuildInfoPanel::updateSwitchButtons(int tag)
{
	m_PlacardSel = tag;

	CCScale9Sprite* p4 = NULL;
	if (tag!=Placard_Private)
	{
		p4=SystemData::getScale9SpriteByPlist("guild.info.placard.button",105,45);
	}
	else
	{
		p4=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",105,45);
	}
	CCScale9Sprite* pSel4=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",105,45);
	CCMenuItemSprite *pPlacard =CCMenuItemSprite::create(p4,pSel4,NULL,this,menu_selector(GuildInfoPanel::MenuCallBack));
	if(pPlacard)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.info.button.placard.text");
		pLabel->setFontSize(18); 
		pLabel->setColor(ccGREEN);
		pPlacard->setTag(Placard_Private);
		pPlacard->setPosition(SystemData::getLayoutPoint("guild.info.button.placard"));
		pLabel->setPosition(pPlacard->getPosition());
		pPlacard->setRotation(90);
		m_pMainMenu->addChild(pPlacard);
		m_pMainMenu->addChild(pLabel);  
	}

	CCScale9Sprite* p5 = NULL;
	if (tag!=Placard_Public)
	{
		p5=SystemData::getScale9SpriteByPlist("guild.info.placard.button",105,45);
	}
	else
	{
		p5=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",105,45);
	}
	CCScale9Sprite* pSel5=SystemData::getScale9SpriteByPlist("guild.info.placard.button.sel",105,45);
	CCMenuItemSprite *pPublicnotice =CCMenuItemSprite::create(p5,pSel5,NULL,this,menu_selector(GuildInfoPanel::MenuCallBack)); 
	if(pPublicnotice)
	{
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.info.button.publicnotice.text");
		pLabel->setFontSize(18);
		pLabel->setColor(ccGREEN);
		pPublicnotice->setTag(Placard_Public);
		pPublicnotice->setPosition(SystemData::getLayoutPoint("guild.info.button.publicnotice"));
		pLabel->setPosition(pPublicnotice->getPosition());
		pPublicnotice->setRotation(90);
		m_pMainMenu->addChild(pPublicnotice);
		m_pMainMenu->addChild(pLabel);
	}

	if (m_pTableView)
	{
		m_pTableView->reloadData();
	}
}
void GuildInfoPanel::onCPEvent(const std::string &eventName)
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_FINISH)
	{
		if (source == "HandleMessageMyGuildInfoNotify"||source == "HandleMessageGuildMoneyUpdateNotify")
		{
			loadGuildInfo();
		}
		else if(source == "HandleMessageGuildMemberInfoByPidResponse")
		{
			loadMyInfo(); 
		}
		else if(source == "HandleMessageGuildPlacardNotify"||source == "HandleMessageGuildPublicNoticeNotify")
		{
			loadPlacard(m_PlacardSel);
		}
		else if(source == "HandleMessageLeaveGuildResponse")
		{
			if (CPEventHelper::isRequestSuccess())
			{
				CPEventHelper::uiNotify("SwitchGuildBrowse", "", 0);
			}
		}
		
	}
	else if (eventName == CPEventName::MSG_CHANGE)
	{
		if(source == "HandleMessageSyncGuildExDataNotify")
		{
			int dataType = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			CCLog("_droid_____________type = %d",dataType);
			switch (dataType)
			{
			case GuildType::guild_money:
				{
					loadGuildInfo();
					break;
				}
			default:
				break;
			}
		}
		else if(source == "HandleMessageSyncGuildExStringDataNotify")
		{
			int dataType = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			CCLog("_droid_____________type = %d",dataType);
			switch (dataType)
			{
			case GuildType::guild_private_notice:
				{
					loadPlacard(m_PlacardSel);
					break;
				}
			case GuildType::guild_public_notice:
				{
					loadPlacard(m_PlacardSel);
					break;
				}
			default:
				break;
			}
		}
		else if(source == "HandleMessageUpdPlayerPropsDataNotify")
		{
			int dataType = CPEventHelper::getEventIntData(CPEventData::VALUE_2);
			CCLog("_droid_____________type = %d",dataType);
			switch (dataType)
			{
			case Entity::attr_guild_contribution:
				{
					loadMyInfo();
					break;
				}
			default:
				break;
			}
		}
	}
}



////////////////////////////////////////////////////////////////////////////////
int m_DonateSid[4]={30033,30034,30062,30171};
GuildDonatePanel::GuildDonatePanel()
	:m_pMainMenu(NULL)
	,m_selIndex(-1)
	,m_background(NULL)
	,m_GuildGold(NULL)
{
	m_DonateCnt.clear();
}

GuildDonatePanel::~GuildDonatePanel()
{
	m_DonateCnt.clear();
}

GuildDonatePanel* GuildDonatePanel::create()
{
	GuildDonatePanel* pPanel = new GuildDonatePanel();
	if(pPanel && pPanel->init())
	{
		pPanel->autorelease();
		return pPanel;
	}
	else
	{
		CCLog("GuildDonatePanel create failed!");
	}
	if (pPanel)
	{
		delete pPanel;
	}
	return NULL; 
}


bool GuildDonatePanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//test
	MsgGuildDonateRequest* req = new MsgGuildDonateRequest;
	req->sid=30033;
	req->cnt=1;
	//HandleMessage::sendMessage(req);

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
	initItems();

	return true;
}

void GuildDonatePanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Button_Close:
			{
				
			}
			break;
		case Button_DonateItem:
			{
				for(map<int,int>::iterator it=m_DonateCnt.begin();it!=m_DonateCnt.end();++it)
				{
					if (it->second<=0)
					{
						continue;
					}
					MsgGuildDonateRequest* req = new MsgGuildDonateRequest;
					req->sid=it->first;
					req->cnt=it->second;
					HandleMessage::sendMessage(req);
				}
			}
			break;
		case Button_Donate50:
			{
				MsgGuildDonateRequest* req = new MsgGuildDonateRequest;
				req->sid=3;
				req->cnt=50;
				HandleMessage::sendMessage(req);
			}
			break;
		case Button_Donate500:
			{
				MsgGuildDonateRequest* req = new MsgGuildDonateRequest;
				req->sid=3;
				req->cnt=500;
				HandleMessage::sendMessage(req);
			}
			break;
		default:
			break;
		}
		closeSelf();
	}
}

void GuildDonatePanel::closeSelf()
{
	this->removeFromParentAndCleanup(true);
}

void GuildDonatePanel::initFrame()
{
	m_background = SystemData::getSpriteByPlist("openactivity.alert.frame.background");
	m_background->setAnchorPoint(ccp(0.5,0.5));  
	addChild(m_background);

	CCSize bgSize = SystemData::getLayoutSize("openactivity.alert.frame.scalebg");
	CCPoint bgPoint = ccp(281.5,195);
	CCScale9Sprite *bg=SystemData::getScale9SpriteByPlist("openactivity.alert.frame.scalebg",bgSize.width,bgSize.height);
	bg->setAnchorPoint(ccp(0.5,0.5));
	bg->setPosition(bgPoint); 
	m_background->addChild(bg);

	for (int i=0;i<4;i++)
	{
		CCSprite* sprite = SystemData::getSpriteByPlist("activity.sprite.item.frame");
		CCPoint point = SystemData::getLayoutPoint("guild.info.alert.sprite.item"+StringUtils::toString(i));
		sprite->setAnchorPoint(CCPointZero);
		sprite->setPosition(point);
		m_background->addChild(sprite);
	}
}

void GuildDonatePanel::initLabels()
{
	CCLabelTTF* m_Title =  SystemData::getLabelTTF("popalert.normal.label.title"); 
	m_Title->setColor(ccYELLOW);
	m_Title->setFontSize(22);    
	m_Title->setHorizontalAlignment(kCCTextAlignmentCenter);
	m_Title->setDimensions(CCSizeMake(SystemData::getLayoutValue("popalert.normal.label.title.w"),SystemData::getLayoutValue("popalert.normal.label.title.h")));
	m_Title->setAnchorPoint(ccp(0.5,1));
	m_Title->setPosition(ccp(m_background->getContentSize().width/2,m_background->getContentSize().height-10));
	m_background->addChild(m_Title);
	m_Title->setString(SystemData::getLayoutString("guild.info.alert.title.donate").c_str()); 

	CCSize size = CCSizeMake(500,75);
	CCPoint pos = ccp(281.5,280);
	CPRichText* pText=NPCFunctionData::getBigContent(SystemData::getLayoutValue("guild.info.alert.donate.info"),size.width,size.height); 
	pText->setAnchorPoint(ccp(0.5,0.5));
	pText->setPosition(pos);
	m_background->addChild(pText);

	m_GuildGold = SystemData::getLabelTTF("guild.info.alert.label.total");
	m_GuildGold->setColor(ccWHITE);
	m_GuildGold->setFontSize(20);     
	m_GuildGold->setAnchorPoint(CCPointZero);
	m_GuildGold->setHorizontalAlignment(kCCTextAlignmentLeft); 
	m_background->addChild(m_GuildGold);
}

void GuildDonatePanel::initButtons()
{
	CCMenuItemImage* button1 = SystemData::getMenuItemImageByPlist("openactivity.alert.button.close");
	button1->setTarget(this,menu_selector(GuildDonatePanel::MenuCallBack));
	button1->setTag(Button_Close);
	button1->setAnchorPoint(ccp(1,1));
	button1->setPosition(m_background->getContentSize().width,m_background->getContentSize().height);
	m_pMainMenu->addChild(button1);

	CCSize size2 = SystemData::getLayoutSize("guild.info.alert.button.donateitem");
	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("activity.button.frame",size2.width,size2.height);
	CCScale9Sprite* pSel2=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",size2.width,size2.height); 
	CCMenuItemSprite *button2 =CCMenuItemSprite::create(p2,pSel2,NULL,this,menu_selector(GuildDonatePanel::MenuCallBack));
	if(button2)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.info.alert.button.donateitem.text"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button2->setTag(Button_DonateItem);        
		button2->setPosition(SystemData::getLayoutPoint("guild.info.alert.button.donateitem"));
		pLabel->setPosition(button2->getPosition()); 
		m_pMainMenu->addChild(button2); 
		m_pMainMenu->addChild(pLabel); 
	}
	CCSize size3 = SystemData::getLayoutSize("guild.info.alert.button.donate50");
	CCScale9Sprite* p3=SystemData::getScale9SpriteByPlist("activity.button.frame",size3.width,size3.height);
	CCScale9Sprite* pSel3=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",size3.width,size3.height); 
	CCMenuItemSprite *button3 =CCMenuItemSprite::create(p3,pSel3,NULL,this,menu_selector(GuildDonatePanel::MenuCallBack));
	if(button3)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.info.alert.button.donate50.text"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button3->setTag(Button_Donate50);        
		button3->setPosition(SystemData::getLayoutPoint("guild.info.alert.button.donate50"));
		pLabel->setPosition(button3->getPosition());  
		m_pMainMenu->addChild(button3);  
		m_pMainMenu->addChild(pLabel); 
	}
	CCSize size4 = SystemData::getLayoutSize("guild.info.alert.button.donate500");
	CCScale9Sprite* p4=SystemData::getScale9SpriteByPlist("activity.button.frame",size4.width,size4.height);
	CCScale9Sprite* pSel4=SystemData::getScale9SpriteByPlist("activity.button.frame.sel",size4.width,size4.height); 
	CCMenuItemSprite *button4 =CCMenuItemSprite::create(p4,pSel4,NULL,this,menu_selector(GuildDonatePanel::MenuCallBack));
	if(button4)
	{  
		CCLabelTTF *pLabel=SystemData::getLabelTTF("guild.info.alert.button.donate500.text"); 
		pLabel->setFontSize(18); 
		pLabel->setColor(ccWHITE);
		button4->setTag(Button_Donate500);        
		button4->setPosition(SystemData::getLayoutPoint("guild.info.alert.button.donate500"));
		pLabel->setPosition(button4->getPosition());  
		m_pMainMenu->addChild(button4); 
		m_pMainMenu->addChild(pLabel); 
	}
}
void GuildDonatePanel::initItems()
{
	for (int i=0;i<4;i++)
	{

		CCPoint point = SystemData::getLayoutPoint("guild.info.alert.sprite.item"+StringUtils::toString(i));
		
		int sid = m_DonateSid[i];
		int cnt = GameData::s_user->getUserItemData()->getItemCntBySid(sid);
		m_DonateCnt[sid]=cnt;
		if (sid>0)
		{ 
			UserItem* item = CommonFunction::createNewItem(sid); 
			item->count = cnt;
			CCMenuItemImage* pItem=CommonFunction::getItemIcon(item);
			pItem->setTag(i+Item_Cnt_Button_Start); 
			pItem->setPosition(ccp(point.x+33,point.y+33));
			pItem->setTarget(this,menu_selector(GuildDonatePanel::itemCallBack));
			m_pMainMenu->addChild(pItem);

			CCLabelTTF* labelName = SystemData::getLabelTTF("guild.info.alert.label.item");
			labelName->setColor(ccYELLOW);
			labelName->setFontSize(15);     
			labelName->setAnchorPoint(CCPointZero);
			labelName->setPosition(ccp(point.x,point.y-25));
			labelName->setHorizontalAlignment(kCCTextAlignmentCenter); 
			m_pMainMenu->addChild(labelName);
			labelName->setString(item->name.c_str());
		} 
		
		CCLabelTTF* label = SystemData::getLabelTTF("guild.info.alert.label.item");
		label->setColor(ccWHITE);
		label->setFontSize(15);     
		label->setAnchorPoint(CCPointZero);
		label->setPosition(ccp(point.x-25,point.y-50));
		label->setHorizontalAlignment(kCCTextAlignmentLeft); 
		label->setTag(i+Item_Cnt_Label_Start);
		m_pMainMenu->addChild(label);

		std::string str = SystemData::getLayoutString("guild.info.alert.label.item");
		str = str+StringUtils::toString(cnt);
		label->setString(str.c_str());

		updateTotalGold();
	}
}

void GuildDonatePanel::itemCallBack(CCObject* pSender)
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	if (pImage)
	{
		UserItem* userItem = (UserItem*)pImage->getUserData();
		m_selIndex = pImage->getTag()-Item_Cnt_Button_Start;
		
		DonateKeyBoard* keyboard = DonateKeyBoard::create(m_DonateCnt[userItem->sid],userItem->count);
		keyboard->setPosition(SystemData::getLayoutPoint("shop.point.keyboard"));
		keyboard->setChangeHandler(this,menu_selector(GuildDonatePanel::keyBoardChangedCallBack));
		addChild(keyboard);
	}
}
void GuildDonatePanel::keyBoardChangedCallBack(CCObject* pSender)
{
	DonateKeyBoard* keyboard = (DonateKeyBoard*)pSender;
	if (keyboard)
	{
		int curNum = keyboard->getCurNum();
		if (m_selIndex<0)
			return;
		CCLabelTTF* label = (CCLabelTTF*)m_pMainMenu->getChildByTag(m_selIndex+Item_Cnt_Label_Start);
		if (label)
		{
			std::string str = SystemData::getLayoutString("guild.info.alert.label.item");
			str = str+StringUtils::toString(curNum);
			label->setString(str.c_str());
			m_DonateCnt[m_DonateSid[m_selIndex]]=curNum;

			updateTotalGold();
		}
		
	}
}
void GuildDonatePanel::updateTotalGold()
{
	if (m_GuildGold)
	{
		int totalGold = 0;
		for(map<int,int>::iterator it=m_DonateCnt.begin();it!=m_DonateCnt.end();++it)
		{
			totalGold+=getGold(it->first,it->second);
		}
		std::string str = SystemData::getLayoutString("guild.info.alert.label.total");
		str = str+StringUtils::toString(totalGold);
		m_GuildGold->setString(str.c_str());
	}
}
int GuildDonatePanel::getGold(int sid,int cnt)
{
	int gold = 0;
	switch (sid)
	{
	case 30033:
		{
			gold=10000*cnt;
			break;
		}
	case 30034:
		{
			gold=50000*cnt;
			break;
		}
	case 30062:
		{
			gold=100000*cnt;
			break;
		}
	case 30171:
		{
			gold=500000*cnt;
			break;
		}
	default:
		break;
	}
	return gold;
}