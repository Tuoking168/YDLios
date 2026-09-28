#include "FloatPanel.h"
#include "scene/panel/functionPanel/PetPanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "UserData/HeroData.h"
#include "userdata/luadata/LuaData.h"
#include "userdata/netdata/Ghost.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/GhostManager.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/SceneManager.h"
#include "network/HandleMessage.h"
#include "event/EventProtocol.h"
#include "userdata/NPCFunctionData.h"
#include "script/LuaWrapper.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "EntityDefinition.h"
#include "MsgTrade.h"
#include "MsgPet.h"
#include "MsgGuild.h"
#include "userdata/UserPetData.h"
#include "event/CPEventHelper.h"
#include "controls/CPNodeHelper.h"
#include "userdata/teamdata/TeamMsgSender.h"
#include "userdata/teamdata/TeamData.h"
#include "TeamDefinition.h"
#include "shop/ShopPanel.h"
#include "logic/ItemOperator.h"
#include "userdata/FuncData.h"
#include "MsgPlayer.h"
#include "userdata/BoothData.h"
#include "scene/panel/MainPanel.h"
#include "scene/panel/functionPanel/BoothPanel.h"

HideSet FloatPanel::sHideSet;

FloatPanel::FloatPanel():
	m_pContent(NULL),
	m_pBtnMenu(NULL),
	m_pSelectMenu(NULL),
	mTarget(NULL),
	mHandleFunc(NULL),
	m_data1(0),
	m_data2(0)
{
	for (int i=0;i<TypeMax;i++)
	{
		block[i]=false;
	}
}

FloatPanel::~FloatPanel()
{

}

FloatPanel* FloatPanel::create(int type)
{
	FloatPanel* pPanel = new FloatPanel();
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

bool FloatPanel::needShow( int type )
{
	return (sHideSet.find(type) == sHideSet.end());
}

FloatPanel *FloatPanel::show( int type, const StrVector &strlist, CCNode *parent, SEL_FloatPanel func )
{
	if (parent)
	{
		if (needShow(type))
		{
			FloatPanel *panel = create(type);
			panel->setTipsContent(strlist);
			panel->setHandler(parent, func);
			parent->addChild(panel);
			return panel;
		}
		else
		{
			if (func)
			{
				(parent->*func)(Button_QD);
			}
		}	
	}
	return NULL;
}

bool FloatPanel::init(int type)//宠物面板
{
	if (!PartPanel::init())
	{
		return false;
	}
	m_iCurrentType=type;
	const int petPickState = HeroData::getProp(Entity::attr_pet_pick_state);
	if (m_iCurrentType==FloatPanelType::PET_MONEY)
	{
		if (petPickState&1)
		{
			block[0]=true;			
		}
	}
	else if (m_iCurrentType==FloatPanelType::PET_ITEM)
	{
		
	}

	CCSprite* pborder=SystemData::getSpriteByPlist("ui_float_menu_border");
	pborder->setAnchorPoint(CCPointZero);
	pborder->setPosition(CCPointZero);
	addChild(pborder);

	m_nWidth=pborder->getContentSize().width;
	m_nHeight=pborder->getContentSize().height;
	addCover();

	setContentSize(CCSizeMake(m_nWidth,m_nHeight));

	//显示标题
	std::string title;
	LuaData::getProp("gdTips",m_iCurrentType,"title",title);
	CCLabelTTF* pLabel=CCLabelTTF::create(title.c_str(),"微软雅黑",20);
	pLabel->setPosition(ccp(pborder->getContentSize().width/2, (pborder->getContentSize().height-25)));
	addChild(pLabel);

	//显示内容
	std::string content;	
	LuaData::getProp("gdTips",m_iCurrentType,"content",content);
	int fontsize = 20;
	if (m_iCurrentType==FloatPanelType::Pet_reborn_desc) fontsize = 16;
	m_pContent=CCLabelTTF::create(content.c_str(), "Arial", fontsize, CCSizeMake(340, 150), kCCTextAlignmentCenter);
	m_pContent->setAnchorPoint(ccp(0.5, 1));
	m_pContent->setPosition(ccp(pborder->getContentSize().width/2, (pborder->getContentSize().height-90)));
	addChild(m_pContent);

	//关闭按钮
	CCMenu* pMenu=CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero); 
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCMenuItemImage* pClose=SystemData::getMenuItemImageByPlist("ui_float_menu_close");
	pClose->setPosition(ccp(pborder->getContentSize().width-25,pborder->getContentSize().height-25));
	pClose->setTarget(this,menu_selector(FloatPanel::buttonCallBack));
	pClose->setTag(Button_Close);
	pMenu->addChild(pClose);

	initMain();

	const CCSize boardSize = pborder->getContentSize();
	setPositionX((SystemData::size_x - boardSize.width)/2);
	setPositionY((SystemData::size_y - boardSize.height)/2 + 15);

	return true;
}

void FloatPanel::initMain()
{
	CCLabelTTF* pLabel=CCLabelTTF::create("XXXXXXXXXX","微软雅黑",20);

	m_pBtnMenu=GeneralMenu::create();
	m_pSelectMenu=GeneralMenu::create();
	m_pSelectMenu->setAnchorPoint(CCPointZero);
	m_pSelectMenu->setPosition(CCPointZero);
	addChild(m_pSelectMenu);
	CCArray* pArray=initSelectButton();
	CCObject* pObject;
	int x=0,y=0;
	CCARRAY_FOREACH(pArray,pObject)
	{
		CCMenuItemImage* pItem=(CCMenuItemImage*)pObject;
		m_pSelectMenu->addChild(pItem);
	}
	int btncout=0;
	LuaData::getProp_size("gdTips",m_iCurrentType,"button",btncout);
	if (btncout!=0)
	{
		m_pBtnMenu=initButton(btncout);		
		m_pBtnMenu->setAnchorPoint(CCPointZero);
		m_pBtnMenu->setPosition(CCPointZero);
		addChild(m_pBtnMenu); 
	}
}

CCArray* FloatPanel::initSelectButton()
{
	int btncout=0;
	LuaData::getProp_size("gdTips",m_iCurrentType,"select",btncout);
	CCArray* pArray=CCArray::create();
	for(int i=0;i<btncout;i++)
	{
		std::string btnname;
		LuaData::getProp_tips("gdTips",m_iCurrentType,"select",i+1,"str",btnname);
		CCMenuItemImage* pBlock=SystemData::getMenuItemImageByPlist("ui_float_menu_block");
		CCSprite* pisBlock=SystemData::getSpriteByPlist("ui_float_menu_isblock");
		pisBlock->setPosition(CCPointZero);
		pisBlock->setAnchorPoint(CCPointZero);
		pisBlock->setTag(10);
		pBlock->addChild(pisBlock);
		if (!block[i])
		{
			pisBlock->setVisible(false);
		}

		if (btncout==1)
		{
			pBlock->setPosition(SystemData::getLayoutPoint("ui_float_block_pos"));
		}
		else
		{
			pBlock->setPosition(ccp(SystemData::getLayoutPoint("ui_float_block1_pos").x+(i%2)*130,SystemData::getLayoutPoint("ui_float_block1_pos").y-(i/2)*50));
		}
		CCLabelTTF* pLabel=CCLabelTTF::create(AToU8(btnname.c_str()),"微软雅黑",20);
		pLabel->setAnchorPoint(CCPointZero);
		pLabel->setPosition(ccp(50,0));
		pBlock->addChild(pLabel);
		pBlock->setTarget(this,menu_selector(FloatPanel::blockCallBack));
		pBlock->setTag(i);
		pArray->addObject(pBlock);
	}
	return pArray;
}

void FloatPanel::blockCallBack( CCObject* pSender )
{
	CCMenuItemImage* pNode = dynamic_cast<CCMenuItemImage*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		if (block[tag])
		{
			pNode->getChildByTag(10)->setVisible(false);			
			block[tag]=false;
		}
		else
		{
			pNode->getChildByTag(10)->setVisible(true);
			block[tag]=true;
		}
	}
}

GeneralMenu* FloatPanel::initButton(int type)
{
	GeneralMenu* pMenu=GeneralMenu::create();
	if (type==1)
	{
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("ui_float_button",100,42);
		CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("ui_float_button.sel",100,42);
		CCMenuItemSprite* pButton=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(FloatPanel::buttonCallBack));
		pButton->setPosition(ccp(SystemData::getLayoutPoint("ui_float_block_pos").x+60,SystemData::getLayoutPoint("ui_float_block_pos").y-60));
		pButton->setTag(Button_QD);
		std::string btnname;
		LuaData::getProp_tips("gdTips",m_iCurrentType,"button",1,"name",btnname);
		CCLabelTTF* pLabel=CCLabelTTF::create(AToU8(btnname.c_str()),"微软雅黑",18);
		pLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
		pMenu->addChild(pButton);
		pButton->addChild(pLabel);
	}
	else if (type==2)
	{
		for (int i=0;i<2;i++)
		{
			const CCPoint &pt = ccp(SystemData::getLayoutPoint("ui_float_block1_pos").x - 30 + i * 300, SystemData::getLayoutPoint("ui_float_block1_pos").y - 60);
			CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("ui_float_button",100,42);
			CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("ui_float_button.sel",100,42);
			CCMenuItemSprite* pButton=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(FloatPanel::buttonCallBack));
			pButton->setPosition(pt);
			pButton->setTag(i);
			std::string btnname;
			LuaData::getProp_tips("gdTips",m_iCurrentType,"button",i+1,"name",btnname);
			CCLabelTTF* pLabel=CCLabelTTF::create(AToU8(btnname.c_str()),"微软雅黑",18);
			pLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
			pMenu->addChild(pButton);
			pButton->addChild(pLabel);
		}
	}
	return pMenu;
}

void FloatPanel::buttonCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		const int tag=pNode->getTag();

		//
		if (mTarget && mHandleFunc)
		{
			(mTarget->*mHandleFunc)(tag);
		}
		//
		if (tag==Button_QD)
		{
			if (block[0])
			{
				sHideSet.insert(m_iCurrentType);
			}
			else
			{
				sHideSet.erase(m_iCurrentType);
			}
		
			const int petPickState = HeroData::getProp(Entity::attr_pet_pick_state);
			//发送消息或者设置
			if (m_iCurrentType==FloatPanelType::PET_MONEY)
			{
				CPEventHelper::openPanel("MainPanel",8,1,0,0);
			}
			else if (m_iCurrentType==FloatPanelType::PET_ITEM)
			{
				CPEventHelper::openPanel("MainPanel",8,1,0,0);
			}
			else if (m_iCurrentType==FloatPanelType::TradeTips_Apply)
			{
/*				CPEventHelper::dispatcher(CPEventName::MSG_CHANGE, "TradeTipsApply", "");*/
				MsgItemTradeOperationReply* msg=new MsgItemTradeOperationReply;
				msg->traderesult = TradeState::Trade_Agree;
				msg->targeteid = GameData::s_user -> m_pMainRole->m_iTargeteid;
				HandleMessage::sendMessage(msg);
			}
			else if (m_iCurrentType==FloatPanelType::TradeTips_Over)
			{
/*				CPEventHelper::dispatcher(CPEventName::MSG_CHANGE, "TradeTipsOver", "");	*/
				// 终止交易
				MsgItemTradeRefuse* msg=new MsgItemTradeRefuse;
				HandleMessage::sendMessage(msg);	
			}
			else if (m_iCurrentType==FloatPanelType::PET_LowBooth )
			{
				UserPet* UserPet=GameData::s_user->getUserPetData()->getCurrentPet();
				if (UserPet)
				{
					GameData::s_user->m_pMainRole->m_bMyBooth = true;
					BoothData::SetBoothPetIid( UserPet->iid );
					CPEventHelper::openPanel("MainPanel",TAG_Booth_Panel,Booth_Sell,0,0);
					//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TURNTO_BTJM);	
				}
			}
			else if (m_iCurrentType==FloatPanelType::PET_HighBooth )
			{
				UserPet* UserPet=GameData::s_user->getUserPetData()->getCurrentPet();
				if (UserPet)
				{
					GameData::s_user->m_pMainRole->m_bMyBooth = true;
					BoothData::SetBoothPetIid( UserPet->iid );
					CPEventHelper::openPanel("MainPanel",TAG_Booth_Panel,Booth_Sell,1,0);
					//CPEventHelper::openPanel("MainPanel",TAG_Merge_Panel,TAG_LZ,TAG_LingZhu,0);
					//EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_TURNTO_BTJM_H);	
				}

			}
			else if (m_iCurrentType==FloatPanelType::DOG_UPDATE)
			{
				CPEventHelper::dispatcher(CPEventName::MSG_CHANGE, "DogUpdate", "");			
			}
			else if(m_iCurrentType==FloatPanelType::RELIVE_SITU)
			{
				CPEventHelper::dispatcher(CPEventName::MSG_CHANGE, "ReliveSITU", "");
			}
			else if(m_iCurrentType==FloatPanelType::Item_shoesUse)
			{
				if (block[0])
				{
					GameData::s_user->m_pMainRole->m_bBuyShoesTips=true;
					NPCFunctionData::useShoes(m_data1,m_data2);
				}
				else
				{
					//跳转到商城界面
					//CCLog("turn to shop panel");
					//CPEventHelper::openPanel("ShopPanel",ShopPanel::TAG_SHOP_COMMONLY_USED,40046,0,0);
					//打开便捷购买界面
					int price = 0;
					int reqsid = SystemData::getLayoutValue("飞鞋");
					LuaData::getProp(LuaData::ITEM,reqsid,"shopprice",price);
					if (price==0)
					{
						price =1;
					}
					Game::getGameUI()->showNumberKeyBoard(1,5,price,reqsid);
				}
			}
			else if (m_iCurrentType==FloatPanelType::Use_zhuizongling)
			{
				CPEventHelper::openPanel("ShopPanel",ShopPanel::TAG_SHOP_COMMONLY_USED,40132,0,0);
// 				int price = 0;
// 				int reqsid = SystemData::getLayoutValue("zhuizongling_sid");
// 				LuaData::getProp(LuaData::ITEM,reqsid,"shopprice",price);
// 				if (price==0)
// 				{
// 					price =1;
// 				}
// 				Game::getGameUI()->showNumberKeyBoard(price,5,price,reqsid);
			}
			else if(m_iCurrentType == FloatPanelType::Pet_onekeyup)
			{
				CPEventHelper::dispatcher(CPEventName::MSG_CHANGE, "PetOneKeyUp", "");
			}
			else if(m_iCurrentType == FloatPanelType::Pet_FeedHonor)
			{
				if (block[0])
				{
					GameData::s_user->getUserPetData()->honortips=true;
				}
			}
			else if(m_iCurrentType==FloatPanelType::Pet_FeedVcoin)
			{
				if (block[0])
				{
					GameData::s_user->getUserPetData()->vcointips=true;
				}
			}
			else if(m_iCurrentType==FloatPanelType::Relive_Item_NotEnough)
			{
				CPEventHelper::openPanel("RechargePanel");
			}
			else if(m_iCurrentType==FloatPanelType::Gold_NotEnough)
			{
				CPEventHelper::openPanel("RechargePanel");
			}
			else if(m_iCurrentType==FloatPanelType::Team_invite || m_iCurrentType==FloatPanelType::Team_application ||m_iCurrentType==FloatPanelType::Team_hasteam)
			{
				TeamMsgSender::MakeDecision(TeamData::mTeamOperation.opid,TeamDefinition::tmr_accept);
			}
			else if (m_iCurrentType==FloatPanelType::Buy_ItemSure)
			{
				ItemOperator::useItem(m_data1,0,m_data2);
			}
			else if (m_iCurrentType==FloatPanelType::Guild_Leave)
			{
				MsgLeaveGuildRequest* req = new MsgLeaveGuildRequest();
				HandleMessage::sendMessage(req);
			}
			else if (m_iCurrentType==FloatPanelType::Guild_ChangeMaster)
			{

			}
			else if (m_iCurrentType==FloatPanelType::Guild_Kick)
			{

			}
			else if (m_iCurrentType==FloatPanelType::Guild_Invite)
			{
				MsgGuildInviteResultRequestEx* req = new MsgGuildInviteResultRequestEx;
				req->pid = m_data1;
				req->gid = m_data2;
				req->decide = 1;
				HandleMessage::sendMessage(req);
			}
			else if (m_iCurrentType==FloatPanelType::Team_Call)
			{
				FuncData::sendFuncMsgWithID(1,1);
			}
			else if (m_iCurrentType==FloatPanelType::Item_NotEndure)
			{
				NPCFunctionData::repairItem();
			}
			else if (m_iCurrentType==FloatPanelType::Reborn_Tips)
			{
				int npcid = SystemData::getLayoutValue("白须老人");
				GameData::s_user->m_pGhostManager->gotoGhostPos(npcid,"npcs",GHOST_TYPE_NPC);
				Game::getGameUI()->showFlyShoes(npcid);
			}
			else if (m_iCurrentType==FloatPanelType::Guild_Call)
			{
				FuncData::sendFuncMsgWithID(9,FuncData::getdatax(9),1);
			}
			hide();
		}
		else if (tag==Button_QX)
		{
			if (m_iCurrentType==FloatPanelType::TradeTips_Apply)
			{
				MsgItemTradeOperationReply* msg=new MsgItemTradeOperationReply;
				msg->traderesult = TradeState::Trade_Refuse;
				msg->targeteid = GameData::s_user->m_pMainRole->m_iTargeteid;
				HandleMessage::sendMessage(msg);	
			}
			else if(m_iCurrentType==FloatPanelType::RELIVE_SITU)
			{
				MsgReviveEntityRequest* req = new MsgReviveEntityRequest;	
				req->eid=GameData::s_user->m_pMainRole->mID;
				req->type=Entity::revive_safe;
				HandleMessage::sendMessage(req);
			}
			else if(m_iCurrentType==FloatPanelType::Team_invite || m_iCurrentType==FloatPanelType::Team_application ||m_iCurrentType==FloatPanelType::Team_hasteam)
			{
				TeamMsgSender::MakeDecision(TeamData::mTeamOperation.opid,TeamDefinition::tmr_refuse);
			}
			else if (m_iCurrentType==FloatPanelType::Team_Call)
			{
				FuncData::sendFuncMsg(0);
			}
			else if (m_iCurrentType==FloatPanelType::Item_NotEndure)
			{
				NPCFunctionData::findreapairNPC();
			}
			hide();
		}
		else if (tag==Button_Close)
		{
			hide();
		}
	}
}

void FloatPanel::setTipsContent( const StrVector &strlist )
{
	std::string content;	
	LuaData::getProp("gdTips",m_iCurrentType,"content",content);
	CCString* pStr=NULL;
	std::vector<string>::const_iterator it=strlist.begin();
	switch (strlist.size())
	{
	case 1:
		pStr=CCString::createWithFormat(content.c_str(),(*it).c_str());
		break;
	case 2:
		pStr=CCString::createWithFormat(content.c_str(),(*it).c_str(),(*(it+1)).c_str());
		break;
	case 3:
		pStr=CCString::createWithFormat(content.c_str(),(*it).c_str(),(*(it+1)).c_str(),(*(it+2)).c_str());
		break;
	case 4:
		pStr=CCString::createWithFormat(content.c_str(),(*it).c_str(),(*(it+1)).c_str(),(*(it+2)).c_str(),(*(it+3)).c_str());
		break;
	default:
		pStr=CCString::create(content.c_str());
		break;
	}
	m_pContent->setString(pStr->getCString());
}

void FloatPanel::setAlignment( CCTextAlignment align )
{
	if (m_pContent)
	{
		m_pContent->setHorizontalAlignment(align);
	}
}

void FloatPanel::setbtnVisible( bool flag )
{
	if (m_pBtnMenu)
	{
		m_pBtnMenu->setVisible(flag);
		m_pBtnMenu->setTouchEnabled(flag);
	}
}

void FloatPanel::setselectVisible( bool flag )
{
	if (m_pSelectMenu)
	{
		m_pSelectMenu->setVisible(flag);
		m_pSelectMenu->setTouchEnabled(flag);
	}
}

void FloatPanel::setHandler( CCObject *target, SEL_FloatPanel func )
{
	mTarget = target;
	mHandleFunc = func;
}

void FloatPanel::onEnter()
{
	PartPanel::onEnter();
}

void FloatPanel::onExit()
{
	runAction(CPNodeHelper::getScaleToSmall());
	PartPanel::onExit();
}

void FloatPanel::setData( int data1,int data2 )
{
	m_data1=data1;
	m_data2=data2;
}

void FloatPanel::hide()
{
	this->removeFromParent();
	GameUI *panel = Game::getGameUI();
	if (panel)
	{
		panel->hidePanel(TAG_FLOAT_PANEL);
	}
}


