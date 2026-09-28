#include "DogSkillPanel.h"
#include "MsgScene.h"
#include "MsgPlayer.h"
#include "MsgItem.h"
#include "MsgPet.h"
#include "MsgTest.h"
#include "FloatPanel.h"
#include "EntityDefinition.h"
#include "MainUIModule.h"

#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/HeroData.h"
#include "userdata/netdata/GameRole.h"

#include "network/HandleMessage.h"
#include "scene/panel/shop/NpcShopComp.h"
#include "scene/PanelFactory.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"



DogSkillPanel::DogSkillPanel():
	m_isStop(true)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

DogSkillPanel* DogSkillPanel::create()
{
	DogSkillPanel* pPanel = new DogSkillPanel();
	if(pPanel && pPanel->init())
	{
		CCLog("Successfully create DogSkillPanel!");
		pPanel->autorelease();

		return pPanel;
	}
	else
	{
		CCLog("Failed to create DogSkill panel!!");
	}
	return NULL;
}

DogSkillPanel::~DogSkillPanel()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

bool DogSkillPanel::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	
	refreshButtons();

	return true; 
}
void DogSkillPanel::menuCallback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case Button_Update:
			{
				std::vector<std::string> strlist;
				std::string gold="3";
				strlist.push_back(gold);
				Game::getGameUI()->showFloatPanel(FloatPanelType::DOG_UPDATE,strlist);
			}
			break;
		case Button_Call:
			{
				MsgDogOptionRequest* req = new MsgDogOptionRequest;
				req->option = Entity::option_call;
				HandleMessage::sendMessage(req);	
			}
			break;
		case Button_Stop:
			{
				MsgDogOptionRequest* req = new MsgDogOptionRequest;
				req->option = Entity::option_defense;
				HandleMessage::sendMessage(req);	

				this->removeAllChildrenWithCleanup(true);
				refreshButtons();
			}
			break;
		case Button_Attack:
			{
				MsgDogOptionRequest* req = new MsgDogOptionRequest;
				req->option = Entity::option_attack; 
				HandleMessage::sendMessage(req);	

				this->removeAllChildrenWithCleanup(true);  
				//m_isStop = true; 
				refreshButtons();  
			}
			break;
		default:
			break;
		}
	}
}

void DogSkillPanel::onCPEvent( const std::string &eventName )
{
	const std::string &source = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if(source == "DogUpdate")
		{
			MsgDogOptionRequest* req = new MsgDogOptionRequest;
			req->option = Entity::option_upgrade;
			HandleMessage::sendMessage(req);
		}
	}
}


void DogSkillPanel::refreshButtons()
{
	int mode = HeroData::getProp(Entity::attr_dog_mode);
	m_isStop = (mode==Entity::edogm_Normal)?true:false;

	m_pMainMenu = CCMenu::create();
	addChild(m_pMainMenu);

	CCMenuItemImage* pUpdate = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, "dogSkillUpdate");
	if(pUpdate)
	{
		pUpdate->setTarget(this,menu_selector(DogSkillPanel::menuCallback));
		pUpdate->setTag(Button_Update);
		m_pMainMenu->addChild(pUpdate);
	}
	CCMenuItemImage* pCall = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, "dogSkillCall");
	if(pCall)
	{
		pCall->setTarget(this,menu_selector(DogSkillPanel::menuCallback));
		pCall->setTag(Button_Call);
		m_pMainMenu->addChild(pCall);
	}
	if (m_isStop)
	{
		CCMenuItemImage* pStop = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, "dogSkillStop");
		if(pStop)
		{
			pStop->setTarget(this,menu_selector(DogSkillPanel::menuCallback));
			pStop->setTag(Button_Stop);
			m_pMainMenu->addChild(pStop);
		}
	}
	else
	{
		CCMenuItemImage* pAttack = LayoutData::getMenuItemImg(CPModuleName::MAIN_UI, "dogSkillAttack");
		if(pAttack)
		{
			pAttack->setTarget(this,menu_selector(DogSkillPanel::menuCallback));
			pAttack->setTag(Button_Attack);
			m_pMainMenu->addChild(pAttack);
		}
	}
}
