#include "CommonPanel.h"
#include "CharacterPanel.h"
#include "BagPanel.h"
#include "AttributePanel.h"
#include "scene/GameUI.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "ext/TouchCover.h"
#include "ext/GeneralMenu.h"
#include "ext/CCActionDestroy.h"
#include "ext/CCMenuItemTextImage.h"
#include "userdata/luadata/LayerDataLua.h"
#include "SkillPanel.h"
#include "SoulStonePanel.h"
#include "HorsePanel.h"
#include "HorseAttributePanel.h"
#include "PetPanel.h"
#include "PetAttributePanel.h"
#include "MsgItem.h"
#include "network/HandleMessage.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/MainPanel.h"
#include "scene/panel/guide/GuideHelper.h"
#include "event/CPEventHelper.h"
#include "scene/panel/FloatPanel.h"
#include "scene/panel/FloatPanelType.h"
#include "res/AudioLoader.h"
#include "userdata/NPCFunctionData.h"
#include "DesignationPanel.h"


CommonPanel::CommonPanel()
{
	leftCurrentPanel = NULL;
	rightCurrentPanel = NULL;
	m_iCurrentLeftTop=-1;
	m_iCurrentRightTop=-1;
	m_pChoiceMenuRight=NULL;
}


CommonPanel::~CommonPanel()
{

}

void CommonPanel::onEnter()
{
	CCLayer::onEnter();
	setTouchEnabled(true);
	EventDispatcher::sharedEventDispather()->addListener(this);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CommonPanel::postMsg),NOTIFICATION_POSTMSG,NULL);
}

void CommonPanel::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NOTIFICATION_POSTMSG);
 	EventDispatcher::sharedEventDispather()->removeListener(this);
	CCLayer::onExit();
}

CommonPanel* CommonPanel::create(int left , int right )
{
	CommonPanel* commonPanel = new CommonPanel();
	if(commonPanel && commonPanel->init(left))
	{
		commonPanel->autorelease();
		return commonPanel;
	}	
	if (commonPanel)
	{
		delete commonPanel;
	}
	return NULL;
}

bool CommonPanel::init(int tag)
{
	if (!CCLayer::init())
	{
		return false;
	}
	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="MainPanel")
	{
		int data2=CPEventHelper::getEventIntData(CPEventData::VALUE_3);

		tag=data2;
	}
	
	// init menu
	choiceMenuLeft = RadioGroup::create();
	choiceMenuLeft->setPosition(CCPointZero);
	addChild(choiceMenuLeft);


	int leftMenuTag[leftMax]={AVATAR, WRAITHSTONE, PET, PETBAG, HORSE};
	std::string left_menu_name[leftMax]={"ui.rolename","ui.jewelname","ui.petname","ui.bagself.petbagname","ui.horsename"};
	int m_MaxCellCount=leftMax;
	if (!GuideHelper::canOpenFunction(FunctionName::CHONG_WU))
	{
		int n=0;
		for (int i=0;i<leftMax;i++)
		{
			if (leftMenuTag[i]==PET)
			{
				n=i;
				break;
			}
		}
		int temp=leftMenuTag[n];
		for (int i=n;i<leftMax-1;i++)
		{
			leftMenuTag[i]=leftMenuTag[i+1];
		}
		leftMenuTag[leftMax-1]=temp;

		std::string tempstr=left_menu_name[n];
		for (int i=n;i<leftMax-1;i++)
		{
			left_menu_name[i]=left_menu_name[i+1];
		}
		left_menu_name[leftMax-1]=tempstr;

		m_MaxCellCount--;

		n=0;
		for (int i=0;i<leftMax;i++)
		{
			if (leftMenuTag[i]==PETBAG)
			{
				n=i;
				break;
			}
		}
		temp=leftMenuTag[n];
		for (int i=n;i<leftMax-1;i++)
		{
			leftMenuTag[i]=leftMenuTag[i+1];
		}
		leftMenuTag[leftMax-1]=temp;

		tempstr=left_menu_name[n];
		for (int i=n;i<leftMax-1;i++)
		{
			left_menu_name[i]=left_menu_name[i+1];
		}
		left_menu_name[leftMax-1]=tempstr;

		m_MaxCellCount--;
	}
	if (!GuideHelper::canOpenFunction(FunctionName::HUN_SHI))
	{
		int n=0;
		for (int i=0;i<leftMax;i++)
		{
			if (leftMenuTag[i]==WRAITHSTONE)
			{
				n=i;
				break;
			}
		}
		int temp=leftMenuTag[n];
		for (int i=n;i<leftMax-1;i++)
		{
			leftMenuTag[i]=leftMenuTag[i+1];
		}
		leftMenuTag[leftMax-1]=temp;

		std::string tempstr=left_menu_name[n];
		for (int i=n;i<leftMax-1;i++)
		{
			left_menu_name[i]=left_menu_name[i+1];
		}
		left_menu_name[leftMax-1]=tempstr;

		m_MaxCellCount--;
	}
	if (!GuideHelper::canOpenFunction(FunctionName::ZUO_QI))
	{
		int n=0;
		for (int i=0;i<leftMax;i++)
		{
			if (leftMenuTag[i]==HORSE)
			{
				n=i;
				break;
			}
		}
		int temp=leftMenuTag[n];
		for (int i=n;i<leftMax-1;i++)
		{
			leftMenuTag[i]=leftMenuTag[i+1];
		}
		leftMenuTag[leftMax-1]=temp;

		std::string tempstr=left_menu_name[n];
		for (int i=n;i<leftMax-1;i++)
		{
			left_menu_name[i]=left_menu_name[i+1];
		}
		left_menu_name[leftMax-1]=tempstr;

		m_MaxCellCount--;
	}

	int mWidth=0;
	for (int i=0; i<m_MaxCellCount; ++i)
	{
		std::string selectButtonRes = "ui_func.anniu";
		std::string selectedButtonRes = "ui_func.anniu.sel";
		
		CCLabelTTF* plabel=CCLabelTTF::create(SystemData::getLayoutString(left_menu_name[i]).c_str(),"微软雅黑",19);
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist(selectButtonRes,plabel->getContentSize().width+20,SystemData::getLayoutValue("ui_func.anniu.h"));
		CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist(selectedButtonRes,plabel->getContentSize().width+20,SystemData::getLayoutValue("ui_func.anniu.h"));
		CCMenuItemSprite* pTitle=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(CommonPanel::callBack));
		if(pTitle)
		{
			pTitle->setAnchorPoint(ccp(0,1));
			pTitle->setTag(leftMenuTag[i]);
			pTitle->setPosition(ccp(SystemData::getLayoutPoint("ui.bagself.leftmenu").x+mWidth,SystemData::getLayoutPoint("ui.bagself.leftmenu").y));
			choiceMenuLeft->addChild(pTitle);
			plabel->setPosition(ccp(pTitle->getContentSize().width/2, pTitle->getContentSize().height/2));
			pTitle->addChild(plabel);
		}
		mWidth+=p1->getContentSize().width;

	}
	

	initChildPanel(tag);

	 // 添加：隐藏坐骑按钮（延迟执行确保菜单已创建）
    /*this->scheduleOnce(schedule_selector(CommonPanel::hideHorseButtons), 0.01f);
	return true;*/

}

void CommonPanel::addCover(float width, float height)
{
	CCRect inner = CCRectZero;
	CCRect outer = CCRectMake(0,0,width,height);
	TouchCover* pCover = TouchCover::create(inner,outer);
	pCover->setAnchorPoint(CCPointZero);
	pCover->setPosition(CCPointZero);
	addChild(pCover);
}


void CommonPanel::callBack( CCObject* pSender )
{

	CCNode* sender = dynamic_cast<CCNode*>(pSender);
    if (!sender) return;
    
    int tag = sender->getTag();
    
    // 添加坐骑功能拦截 - 在原有逻辑之前
    //if (tag == HORSE) {
    //    CCLog("坐骑功能已屏蔽");
    //    return; // 直接返回，不执行后续原有逻辑
    //}
	CCMenuItemSprite* pMenu = dynamic_cast<CCMenuItemSprite*>(pSender);
	if(pMenu)
	{
		int tag = pMenu->getTag();
		selectTop(tag);
		if (tag >= AVATAR && tag < COMMON_TITLE_LEFT_END )
		{
			initRightTop(tag);
		}
	}
}


void CommonPanel::hideHorseButtons(float dt) {
    // 隐藏左侧坐骑按钮
    if (choiceMenuLeft) {
        CCNode* horseBtn = choiceMenuLeft->getChildByTag(HORSE);
        if (horseBtn) {
            horseBtn->setVisible(false);
            
            // 修正：Cocos2d-x 中按钮禁用方式
            if (horseBtn->isRunning()) {
                // 如果是菜单项，将其从父节点移除
                horseBtn->removeFromParentAndCleanup(true);
            }
        }
    }
    
    // 隐藏右侧坐骑技能按钮
    if (m_pChoiceMenuRight) {
        CCNode* horseSkillBtn = m_pChoiceMenuRight->getChildByTag(HORSESKILL);
        if (horseSkillBtn) {
            horseSkillBtn->setVisible(false);
            if (horseSkillBtn->isRunning()) {
                horseSkillBtn->removeFromParentAndCleanup(true);
            }
        }
    }
}



void CommonPanel::rightTopCallBack( CCObject* pSender )
{
	CCMenuItemSprite* pMenu = dynamic_cast<CCMenuItemSprite*>(pSender);
	if(pMenu)
	{
		int tag = pMenu->getTag();
		selectTop(tag);
	}
}

/**
 * 初始化子面板
 * 
 * @param left 左侧选中的菜单项标识
 * @return bool 总是返回true
 * 
 * 功能说明：
 * 1. 根据传入的左侧菜单标识，设置左侧菜单的选择状态
 * 2. 初始化右侧顶部面板内容
 * 
 * 菜单项对应关系：
 * - AVATAR: 头像/角色面板
 * - WRAITHSTONE: 魂石面板
 * - PET: 宠物面板
 * - PETBAG: 宠物背包面板
 * - HORSE: 坐骑面板
 */
bool CommonPanel::initChildPanel(int left)
{
	// 1. 设置左侧菜单选中状态
	switch (left)
	{
		case AVATAR:      // 头像/角色面板
			choiceMenuLeft->setSelectItem(AVATAR);
			break;
		case WRAITHSTONE: // 魂石面板
			choiceMenuLeft->setSelectItem(WRAITHSTONE);
			break;
		case PET:         // 宠物面板
			choiceMenuLeft->setSelectItem(PET);
			break;
		case PETBAG:      // 宠物背包面板
			choiceMenuLeft->setSelectItem(PETBAG);
			break;
		case HORSE:       // 坐骑面板
			choiceMenuLeft->setSelectItem(HORSE);
			break;
	}
	
	// 2. 初始化右侧顶部面板
	initRightTop(left);
	
	return true;
}
void CommonPanel::selectTop( int tag )
{
	switch(tag)
	{
	case AVATAR:
		{
			if(leftCurrentPanel)
			{
				leftCurrentPanel->removeFromParentAndCleanup(true);
			}
			CharacterPanel* characterPanel = CharacterPanel::create();
			characterPanel->setTag(AVATAR);
			addChild(characterPanel);
			leftCurrentPanel = characterPanel;
			m_iCurrentLeftTop=AVATAR;
		}
		break;
	case WRAITHSTONE:
		{
			if(leftCurrentPanel)
			{
				leftCurrentPanel->removeFromParentAndCleanup(true);
			}
			SoulStonePanel* soulstonePanel = SoulStonePanel::create();
			soulstonePanel->setTag(WRAITHSTONE);
			addChild(soulstonePanel);
			leftCurrentPanel = soulstonePanel;
			m_iCurrentLeftTop=WRAITHSTONE;
		}
		break;
	case HORSE:
		{
			if (leftCurrentPanel)
			{
				leftCurrentPanel->removeFromParentAndCleanup(true);
			}

			HorsePanel* horsePanel = HorsePanel::create();
			horsePanel->setTag(HORSE);
			addChild(horsePanel);
			leftCurrentPanel = horsePanel;
			m_iCurrentLeftTop=HORSE;
		}
		break;
	case PET:
		{
			if(GuideHelper::canOpenFunction(FunctionName::CHONG_WU))
			{
				if(leftCurrentPanel)
				{
					leftCurrentPanel->removeFromParentAndCleanup(true);
				}
				PetPanel* petPanel = PetPanel::create();
				petPanel->setTag(PET);
				addChild(petPanel);
				leftCurrentPanel = petPanel;		
				m_iCurrentLeftTop=PET;
			}
		}
		break;
	case WAREHOUSE:
		{
			if(rightCurrentPanel)
			{
				rightCurrentPanel->removeFromParentAndCleanup(true);
			}
			BagPanel* housebagPanel = BagPanel::create(5,4,SystemData::getLayoutValue("MaxHouseBagSlot"),House_Bag,Bag_Type_Self);
			housebagPanel->setPosition(SystemData::getLayoutPoint("mian_rightmenu_pos"));
			housebagPanel->setTag(WAREHOUSE);
			addChild(housebagPanel);
			rightCurrentPanel = housebagPanel;
			m_iCurrentRightTop=WAREHOUSE;
		}
		break;
	case ATTRIBUTE:
		{
			if(rightCurrentPanel)
			{
				rightCurrentPanel->removeFromParentAndCleanup(true);
			}
			AttributePanel* attributePanel = AttributePanel::create();
			attributePanel->setTag(ATTRIBUTE);
			attributePanel->setPosition(SystemData::getLayoutPoint("mian_rightmenu_pos"));
			addChild(attributePanel);			
			rightCurrentPanel = attributePanel;
		}
		break;
	case BAG:
		{
			if(rightCurrentPanel)
			{
				rightCurrentPanel->removeFromParentAndCleanup(true);
			}
			int type=0;
			int selftype=0;
			switch (m_iCurrentLeftTop)
			{
			case AVATAR:
				type=Bag_Type_Role;
				selftype=Self_Bag;
				break;
			case WRAITHSTONE:
				type=Bag_Type_Stone;
				selftype=Stone_Bag;
				break;
			case PETBAG:
				type=Bag_Type_Pet;
				selftype=Self_Bag;
				break;
			default:
				break;
			}
			BagPanel* bagPanel = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPlayerBagSlot"),selftype,type);
			bagPanel->setPosition(SystemData::getLayoutPoint("mian_rightmenu_pos"));
			addChild(bagPanel,0);
			m_iCurrentRightTop=BAG;
			rightCurrentPanel = bagPanel;
		}
		break;
	case SKILL:
		{
			if(rightCurrentPanel)
			{
				rightCurrentPanel->removeFromParentAndCleanup(true);
			}
			SkillPanel* skillpanel = SkillPanel::create();
			skillpanel->setPosition(SystemData::getLayoutPoint("mian_rightmenu_pos"));
			addChild(skillpanel);			
			rightCurrentPanel = skillpanel;
			m_iCurrentRightTop=SKILL;
		}
		break;
	case PETBAG:
		{
			if(GuideHelper::canOpenFunction(FunctionName::CHONG_WU))
			{
				if(leftCurrentPanel)
				{
					leftCurrentPanel->removeFromParentAndCleanup(true);
				}
				BagPanel* petbagpanel = BagPanel::create(5,5,SystemData::getLayoutValue("MaxPetBagSlot"),Pet_Bag,Bag_Type_Self,1);
				petbagpanel->setPosition(SystemData::getLayoutPoint("mian_leftmenu_pos"));
				petbagpanel->setTag(PETBAG);
				addChild(petbagpanel);
				leftCurrentPanel = petbagpanel;
				m_iCurrentLeftTop=PETBAG;
			}
		}
		break;
	case PETSKILL:
		{
			if(GuideHelper::canOpenFunction(FunctionName::CHONG_WU))
			{
				if(rightCurrentPanel)
				{
					rightCurrentPanel->removeFromParentAndCleanup(true);
				}
				PetAttributePanel* petattributepanel = PetAttributePanel::create();
				petattributepanel->setPosition(SystemData::getLayoutPoint("mian_rightmenu_pos"));
				petattributepanel->setTag(PETSKILL);
				addChild(petattributepanel);
				rightCurrentPanel = petattributepanel;
				m_iCurrentRightTop=PETSKILL;
			}
		}
		break;
	case HORSESKILL:
		{
			if(rightCurrentPanel)
			{
				rightCurrentPanel->removeFromParentAndCleanup(true);
			}
			HorseAttributePanel* horseattributepanel = HorseAttributePanel::create();
			horseattributepanel->setPosition(SystemData::getLayoutPoint("mian_rightmenu_pos"));
			horseattributepanel->setTag(HORSESKILL);
			addChild(horseattributepanel);
			rightCurrentPanel = horseattributepanel;
			m_iCurrentRightTop=HORSESKILL;

		}
		break;
	default:
		break;
	}
}

void CommonPanel::postMsg(CCObject* pSender)
{
	UserItem* pUserItem=(UserItem*)pSender;
	if (pUserItem)
	{
		int canuse=0;
		LuaData::getProp("gdItems",pUserItem->sid,"canuse",canuse);
		if (pUserItem->category==ItemCate_Stone && m_iCurrentLeftTop!=WRAITHSTONE)
		{
			if (GuideHelper::canOpenFunction(FunctionName::HUN_SHI))
			{
				((MainPanel*)(this->getParent()->getParent()))->addPanel(TAG_Role_Panel,WRAITHSTONE); 
			}
			else
			{
				CPEventHelper::uiNotify("","",Error::NotOpenNewFunc);
			}
			return;
		}
		if (pUserItem->category==ItemCate_Extension && pUserItem->type==ItemType_ComfirmBuy)
		{
			CCString *pStr1=CCString::createWithFormat(SystemData::getLayoutString("Buy_Vcoin_").c_str(),pUserItem->sid);
			CCString *pStr2=CCString::createWithFormat(SystemData::getLayoutString("Buy_ItemName_").c_str(),pUserItem->sid);
			std::vector<std::string> strvec;
			strvec.push_back(SystemData::getLayoutString(pStr1->getCString()));
			strvec.push_back(SystemData::getLayoutString(pStr2->getCString()));
			Game::getGameUI()->showFloatPanel(FloatPanelType::Buy_ItemSure,strvec);
			((FloatPanel*)(Game::getGameUI()->m_panels[TAG_FLOAT_PANEL]))->setData(pUserItem->iid,1); 
			return;
		}
		if (canuse==0 )
		{
			MsgItemOperationRequestUse* req = new MsgItemOperationRequestUse;
			req->iid = pUserItem->iid;
			req->eid = GameData::s_user->getUserItemData()->getEquipPutOnPosition(pUserItem);
			if (m_iCurrentLeftTop==WRAITHSTONE)
			{
				if (pUserItem->category==ItemCate_Stone)
				{
					req->eid=((SoulStoneMainPanel* )leftCurrentPanel->getChildByTag(100))->m_iNearPos;
				}		
			}
			if (pUserItem->category==ItemCate_Stone)
			{
				AudioLoader::play(Sound::Effect::hunshixiangqian);	
			}
			else if (pUserItem->category==ItemCate_Equip && pUserItem->type==ItemType_Equip_Weapon)
			{
				AudioLoader::play(Sound::Effect::genghuanwuqi);	
			}
			else if (pUserItem->category==ItemCate_Equip && pUserItem->type!=ItemType_Equip_Weapon)
			{
				AudioLoader::play(Sound::Effect::genghuanfangjv);	
			}
			req->cnt = 1;
			HandleMessage::sendMessage(req);
		}
		else
		{
			NPCFunctionData::doFuncScript(3,pUserItem->sid,0,0);
			//((MainPanel*)(this->getParent()->getParent()))->showOtherPanel(canuse);			
		}
	}
}

void CommonPanel::initRightTop( int tag )
{
	//init右边top
	if (m_pChoiceMenuRight)
	{
		removeChild(m_pChoiceMenuRight);
	}

	RadioGroup* pright= RadioGroup::create();
	pright->setPosition(CCPointZero);

	int rightMenuTag[4];
	std::string right_menu_name[4];
	int sizen=0;
	switch(tag)
	{
	case AVATAR:
		rightMenuTag[0]=ATTRIBUTE;
		rightMenuTag[1]=BAG;
		rightMenuTag[2]=SKILL;
		rightMenuTag[3]=WAREHOUSE;
		right_menu_name[0]="ui.bagself.attributename";
		right_menu_name[1]="ui.bagself.bagname";
		right_menu_name[2]="ui.bagself.skillname";
		right_menu_name[3]="ui.treasurename";
		sizen=4;
		if (!GuideHelper::canOpenFunction(FunctionName::JI_NENG))
		{
			rightMenuTag[0]=ATTRIBUTE;
			rightMenuTag[1]=BAG;
			rightMenuTag[2]=WAREHOUSE;
			right_menu_name[0]="ui.bagself.attributename";
			right_menu_name[1]="ui.bagself.bagname";
			right_menu_name[2]="ui.treasurename";
			sizen=3;
		}
		break;
	case WRAITHSTONE:
		rightMenuTag[0]=BAG;
		right_menu_name[0]="ui.bagself.bagname";
		sizen=1;
		break;
	case PET:
		rightMenuTag[0]=PETSKILL;
		right_menu_name[0]="ui.bagself.petskillname";
		sizen=1;
		break;
	case HORSE:
		rightMenuTag[0]=HORSESKILL;
		right_menu_name[0]="ui.bagself.horseskillname";
		sizen=1;
		break;
	case PETBAG:
		rightMenuTag[0]=BAG;
		right_menu_name[0]="ui.bagself.bagname";
		sizen=1;
		break;
	}
	
	int mWidth=0;
	for (int i=0; i<sizen; ++i)
	{
		CCLabelTTF* plabel=CCLabelTTF::create(SystemData::getLayoutString(right_menu_name[i]).c_str(),"微软雅黑",19);
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("ui_func.anniu",plabel->getContentSize().width+20,SystemData::getLayoutValue("ui_func.anniu.h"));
		CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("ui_func.anniu.sel",plabel->getContentSize().width+20,SystemData::getLayoutValue("ui_func.anniu.h"));
		CCMenuItemSprite* pTitle=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(CommonPanel::rightTopCallBack));
		
		if(pTitle)
		{
			pTitle->setAnchorPoint(ccp(0,1));
			pTitle->setTag(rightMenuTag[i]);
			pTitle->setPosition(ccp(SystemData::getLayoutPoint("ui.bagself.rightmenu").x+mWidth,SystemData::getLayoutPoint("ui.bagself.rightmenu").y));
			pright->addChild(pTitle);
			plabel->setPosition(ccp(pTitle->getContentSize().width/2, pTitle->getContentSize().height/2));
			pTitle->addChild(plabel);
		}
		mWidth+=p1->getContentSize().width;
	}
	m_pChoiceMenuRight = pright;
	addChild(m_pChoiceMenuRight);

	//默认选定top
	switch(tag)
	{
	case AVATAR:
		m_pChoiceMenuRight->setSelectItem(BAG);
		m_iCurrentRightTop=BAG;
		break;
	case WRAITHSTONE:
		m_pChoiceMenuRight->setSelectItem(BAG);
		m_iCurrentRightTop=BAG;
		break;
	case HORSE:
		m_pChoiceMenuRight->setSelectItem(HORSESKILL);
		break;
	case PET:
		m_pChoiceMenuRight->setSelectItem(PETSKILL);
		//m_iCurrentRightTop=PETSKILL;
		break;
	case PETBAG:
		m_pChoiceMenuRight->setSelectItem(BAG);
		m_iCurrentRightTop=BAG;
		break;
	}

	std::string panelname=CPEventHelper::getEventStringData(CPEventData::VALUE_1);
	if (panelname=="MainPanel")
	{
		int data3=CPEventHelper::getEventIntData(CPEventData::VALUE_4);
		if (data3 >= ATTRIBUTE && data3 < COMMON_TITLE_RIGHT_END)
		{
			m_pChoiceMenuRight->setSelectItem(data3);
		}
	}

	//selectTop(m_iCurrentRightTop);
}
