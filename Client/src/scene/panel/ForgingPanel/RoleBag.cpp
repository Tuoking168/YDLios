#include "RoleBag.h"
#include "EntityDefinition.h"
#include "userdata/SystemData.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/HeroData.h"
#include "event/EventProtocol.h"

#include "ext/CCTabelViewEx.h"
#include "ext/CCMenuEx.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/RadioGroup.h"

#include "userdata/netdata/GameRole.h"
#include "scene/Game.h"
#include "scene/GameUI.h"

#include "ext/CCActionDestroy.h"
#include "scene/panel/ForgingPanel/ForgingMainPanel.h"
#include "scene/panel/ForgingPanel/MergeMainPanel.h"

#include "CommonFunction.h"
#include "ItemDefinition.h"


RoleBag::RoleBag( void ):
	m_iCurrentVisibleType(0)
{
	m_pItemArray=NULL;
	m_pCurrentItem=NULL;
}

RoleBag::~RoleBag( void )
{
	CC_SAFE_RELEASE(m_pItemArray);
	CC_SAFE_RELEASE(m_pCurrentItem);

}

CCMenuItemImage* RoleBag::getCurrentItem()
{
	return m_pCurrentItem;

}

void RoleBag::setCurrentItem(CCMenuItemImage* var)
{
	CC_SAFE_RELEASE(m_pCurrentItem);
	m_pCurrentItem=var;
	CC_SAFE_RETAIN(m_pCurrentItem);

}

CCArray* RoleBag::getItemArray()
{
	return m_pItemArray;

}

void RoleBag::setItemArray(CCArray* var)
{
	CC_SAFE_RELEASE(m_pItemArray);
	m_pItemArray=var;
	CC_SAFE_RETAIN(m_pItemArray);

}

RoleBag* RoleBag::create(int type,int itemtype)
{
	RoleBag* pPanel = new RoleBag();
	if(pPanel && pPanel->init(type , itemtype))
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

bool RoleBag::init( int type ,int itemtype)
{
	if (!CCLayer::init())
	{
		return false;
	}
	setTouchEnabled(true);

	m_iCurrentVisibleType=itemtype;
	m_iCurrentPage=1;
	m_iAllPage=3;
	m_OldPoint=CCPointZero;
	m_bIsSelectItem=false;
	m_izOrder=0;
	m_iCurrentTypeBag=type;

	setItemArray(CCArray::create());

	m_pMainMenu=GeneralMenu::create();
	m_pMainMenu->setPosition(CCPointZero);
	addChild(m_pMainMenu);

	m_pBagMenu=GeneralMenu::create();
	m_pBagMenu->setPosition(CCPointZero);
	addChild(m_pBagMenu);

	//updateBag(m_iCurrentPage);
	

	//左箭头
	CCMenuItemImage *pLeftButton=SystemData::getMenuItemImageByPlist("taskcontent_up");
	pLeftButton->runAction(CCRotateBy::create(0,-90));
	pLeftButton->setTag(TAG_LEFT);
	pLeftButton->setTarget(this,menu_selector(RoleBag::menuCallBack));
	pLeftButton->setPosition(SystemData::getLayoutPoint("forging_rightItem_left_pos"));
	m_pMainMenu->addChild(pLeftButton);

	//右箭头
	CCMenuItemImage *pRightButton=SystemData::getMenuItemImageByPlist("taskcontent_up");
	pRightButton->runAction(CCRotateBy::create(0,90));
	pRightButton->setTag(TAG_RIGHT);
	pRightButton->setTarget(this,menu_selector(RoleBag::menuCallBack));
	pRightButton->setPosition(SystemData::getLayoutPoint("forging_rightItem_right_pos"));
	m_pMainMenu->addChild(pRightButton);

	//页数
	CCString* pStr=CCString::createWithFormat("%d/%d",m_iCurrentPage,m_iAllPage);
	CCLabelTTF *pPage=CCLabelTTF::create(pStr->getCString(),"Consolas",16);
	pPage->setTag(TAG_PAGE);
	pPage->setColor(ccWHITE);
	pPage->setPosition(ccp((pRightButton->getPositionX()+pLeftButton->getPositionX())/2,pLeftButton->getPositionY()));
	m_pMainMenu->addChild(pPage);

	return true;
}

void RoleBag::menuCallBack( CCObject *pSender )
{
	CCLOG("RoleBag press down");
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_RIGHT:
		case TAG_LEFT:
			updatePage(tag);
			break;
		default:
// 			NotificationLua& nLua=NotificationLuaManager::Instance();
// 			nLua.showLog("no implement",Notification_RED);
			break;
		}
	}
}

void RoleBag::updateBag( int Page )
{
	m_pBagMenu->removeAllChildren();
	setItemArray(CCArray::create());
	//this->runAction(CCSequence::create(CCDelayTime::create(0.1f),CCCallFuncND::create(this, callfuncND_selector(RoleBag::addItem), (void*)Page),NULL));
	addItem(Page);
}

void RoleBag::updatePage( int tag )
{
	switch (tag)
	{
	case TAG_LEFT:
		if (m_iCurrentPage==1)
		{
			break;
		}
		else
		{
			m_iCurrentPage--;
		}
		break;
	case TAG_RIGHT:
		if (m_iCurrentPage==m_iAllPage)
		{
			break;
		}
		else
		{
			m_iCurrentPage++;
		}
		break;
	default:
		break;
	}
	//更新页码
	CCString* pStr=CCString::createWithFormat("%d/%d",m_iCurrentPage,m_iAllPage);
	((CCLabelTTF*)m_pMainMenu->getChildByTag(TAG_PAGE))->setString(pStr->getCString());

	//更新物品
	//updateBag(m_iCurrentPage);
	this->runAction(CCSequence::create(CCDelayTime::create(0.05f),CCCallFunc::create(this,callfunc_selector(RoleBag::addAllItem)),NULL));

}

void RoleBag::ItemCallBack( CCObject *pSender )
{
	CCMenuItemImage* icon=(CCMenuItemImage* )pSender;
	UserItem* pUserItem=(UserItem*)icon->getUserData();

	((ForgingMainPanel*)(this->getParent()->getParent()))->PostNotic(pUserItem);
}



bool RoleBag::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLOG("Touch Began");
	return true;
}

void RoleBag::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void RoleBag::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void RoleBag::update(float dt)
{
	CCObject *pObject;
	if (m_pCurrentItem)
	{
		if (!m_bIsSelectItem)
		{
			//m_bIsSelectItem=false;
			setCurrentItem(NULL);
		}			
	}	
	else
	{
		if (!m_bIsSelectItem)
		{
			CCARRAY_FOREACH(m_pItemArray,pObject)
			{
				CCMenuItemImage *pItem=(CCMenuItemImage*)pObject;
				if (pItem->isSelected())
				{
					m_bIsSelectItem=true;
					pItem->runAction(CCSequence::create(CCActionInterval::create(0.5),CCCallFuncO::create(this,callfuncO_selector(RoleBag::ItemIsSelect),pItem),NULL));
					break;
				} 
			}
		}
		
	}
	
}

void RoleBag::ItemIsSelect(CCObject *pSender)
{
	CCMenuItemImage* pItem=(CCMenuItemImage*)pSender;
	if (pItem->isSelected())
	{
		CCLOG("1");
		m_OldPoint=pItem->getPosition();
		m_izOrder=pItem->getZOrder();
		pItem->setZOrder(100);
		setCurrentItem(pItem);
	}
	else
	{
		CCLOG("2");
		m_bIsSelectItem=false;
		return;
	}
}

void RoleBag::onEnter()
{
	BasePanel::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(m_pBagMenu);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(m_pBagMenu,kCCMenuHandlerPriority,false);
	this->runAction(CCSequence::create(CCDelayTime::create(0.05f),CCCallFunc::create(this,callfunc_selector(RoleBag::addAllItem)),NULL));
}

void RoleBag::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(m_pBagMenu);
	BasePanel::onExit();
}

void RoleBag::initItem()
{
	m_pCurrentItem->setZOrder(m_izOrder);
	m_OldPoint=CCPointZero;
	m_izOrder=0;
	m_bIsSelectItem=false;
}

void RoleBag::addItem(int Page )
{
	int x=0;
	int y=0;
	int wanjiabeibaozonggezishuilang = HeroData::getProp(Entity::attr_bagslot);
	//背包格子
	for (int i=0;i<20;i++)
	{
		CCSprite *pItem=SystemData::getSpriteByPlist("ui.bag.slot.unlock");
		pItem->setPosition(ccp(SystemData::getLayoutPoint("forging_rightItem_pos").x+x*75,SystemData::getLayoutPoint("forging_rightItem_pos").y-y*67));			
		m_pBagMenu->addChild(pItem);
		int CanUse=0;
		if (wanjiabeibaozonggezishuilang>Page*20)
		{
			CanUse=20;
		}
		else
		{
			CanUse=wanjiabeibaozonggezishuilang-(Page-1)*20;
		}
		if (i<CanUse)//玩家有12个空格子
		{
			//加入玩家物品
			std::vector<UserItem*> equipItem;
			if (m_iCurrentTypeBag==TAG_SSZB)
			{
				//equipItem=CommonFunction::getSSItem(m_iCurrentVisibleType);
			}
			else if (m_iCurrentTypeBag==TAG_BBWP)
			{
				//equipItem=CommonFunction::getBBItem(m_iCurrentVisibleType);
			}
			else if (m_iCurrentTypeBag==TAG_CWWP)
			{
				//equipItem=CommonFunction::getCWItem(m_iCurrentVisibleType);
			}
			int n=0;
			for(std::vector<UserItem*>::iterator it = equipItem.begin(); it!=equipItem.end(); it++)
			{
				if ((n-(Page-1)*20)==i)
				{
					UserItem* userItem=(UserItem*)*it;
					CCMenuItemImage* icon=CommonFunction::getItemIcon(userItem);
					icon->setPosition(pItem->getPosition());
					icon->setTarget(this,menu_selector(RoleBag::ItemCallBack));
					
					m_pItemArray->addObject(icon);
					m_pBagMenu->addChild(icon);
				}					
				n++;
			}			
		}
		else
		{
			CCMenuItemImage *pItem=SystemData::getMenuItemImageByPlist("ui.bag.slot.lock");
			pItem->setPosition(ccp(SystemData::getLayoutPoint("forging_rightItem_pos").x+x*75,SystemData::getLayoutPoint("forging_rightItem_pos").y-y*67));
			pItem->setTarget(this,menu_selector(RoleBag::menuCallBack));
			m_pBagMenu->addChild(pItem);
		}		
		if (x==3)
		{
			y++;
			x=0;
		}
		else
		{
			x++;
		}

	}
}

void RoleBag::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_ITEM_UPDDATA)
	{
		//CCLog("Event Recieve");
		this->stopAllActions();
		this->runAction(CCSequence::create(CCDelayTime::create(0.02f),CCCallFunc::create(this,callfunc_selector(RoleBag::addAllItem)),NULL));
	}
}

void RoleBag::addAllItem()
{
	updateBag(m_iCurrentPage);
}
