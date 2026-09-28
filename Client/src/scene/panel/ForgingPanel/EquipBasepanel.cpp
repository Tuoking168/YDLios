#include "EquipBasepanel.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "scene/Game.h"
#include "scene/GameUI.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "ext/GeneralMenu.h"
#include "event/EventProtocol.h"
#include "scene/panel/EffectSprite.h"
#include "EffectDefinition.h"
#include "utils/RichTextUtils.h"
#include "controls/CPRichText.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"


EquipBasepanel::EquipBasepanel( void ):
	m_pUserItem(NULL),
	m_pMoney(NULL),
	m_pYuanBaoMoney(NULL),
	m_Postgt(CCPointZero),
	m_iHeight(0),
	m_iContentID(0),
	m_pYuanBao(NULL),
	m_bLock(false)
{

}

EquipBasepanel::~EquipBasepanel( void )
{

}

void EquipBasepanel::onEnter()
{
	BasePanel::onEnter();
	this->runAction(CCSequence::create(CCDelayTime::create(0.08f),CCCallFunc::create(this,callfunc_selector(EquipBasepanel::initContent)),NULL));
}


void EquipBasepanel::ItemCallBack( CCObject* pSender )
{
	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);
}

void EquipBasepanel::removeItem()
{
	if(m_pMenu)
	{
		m_pMenu->removeAllChildren();
	}
	if(m_pUserItem)
	{
		m_pUserItem=NULL;
	}
	if(m_pMoney)
	{
		m_pMoney->setString("");
	}
	if(m_pYuanBaoMoney)
	{
		m_pYuanBaoMoney->setString("");
	}
}

void EquipBasepanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		addItem(m_pUserItem);
	}
	else if (channel == EventProtocol::EVENT_ITEM_FAILED)
	{
		EffectSprite* pEffect=EffectSprite::create(Effect::effect_enhancefaild,1);
		pEffect->setPosition(gettgtPos());
		addChild(pEffect);
	}
	else if (channel == EventProtocol::EVENT_ITEM_SUCCESS)
	{
		EffectSprite* pEffect=EffectSprite::create(Effect::effect_enhancesuccess,1);
		pEffect->setPosition(gettgtPos());
		addChild(pEffect);
	}
}

void EquipBasepanel::MenuCallBack( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_LOCK:
			if (m_bLock)
			{
				m_bLock=false;
				m_pYuanBao->setVisible(false);
				m_pYuanBaoMoney->setVisible(false);
			}
			else
			{
				m_bLock=true;
				m_pYuanBao->setVisible(true);
				m_pYuanBaoMoney->setVisible(true);
			}
			m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(m_pUserItem,TAG_Reborn,m_bLock)).c_str());
			break;
		default:
			break;
		}
	}
}


//*------------------------------------------------------------------------------------------------------------------------------------//

void EquipBasepanel::settgtPos( CCPoint pos )
{
	m_Postgt = pos;
}

CCPoint EquipBasepanel::gettgtPos()
{
	return m_Postgt;
}

void EquipBasepanel::setContentID( int id )
{
	m_iContentID = id;
}

int EquipBasepanel::getContentID()
{
	return m_iContentID;
}
//-------------------------------------------------------------------------------------------------------------------------------//

cocos2d::CCSize EquipBasepanel::cellSizeForTable( cocos2d::extension::CCTableView *table )
{
	return CCSizeMake(420, m_iHeight);
}

cocos2d::extension::CCTableViewCell* EquipBasepanel::tableCellAtIndex( cocos2d::extension::CCTableView *table, unsigned int idx )
{
	CCTableViewCell *cell = NULL;
	if (!cell) 
	{
		cell = new CCTableViewCell();
		cell->autorelease();

		CCLayer* pLayer=CCLayer::create();
		pLayer->setAnchorPoint(CCPointZero);
		pLayer->setPosition(CCPointZero);
		cell->addChild(pLayer);

		std::string content;
		LuaData::getProp("gddescription",m_iContentID,"content",content);
		CPRichText* pLabel = RichTextUtils::getRichText(content.c_str(),16,SystemData::getLayoutValue("forging_bottommenu_size.w"),0);
		pLabel->setPosition(CCPointZero);
		pLabel->setAnchorPoint(CCPointZero);
		pLayer->addChild(pLabel);
		m_iHeight=pLabel->getContentSize().height;
	}
	return cell;
}

unsigned int EquipBasepanel::numberOfCellsInTableView( cocos2d::extension::CCTableView *table )
{
	return 1;
}

