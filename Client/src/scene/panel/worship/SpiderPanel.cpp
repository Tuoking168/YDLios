#include "SpiderPanel.h"
#include "userdata/SystemData.h"
#include "ext/GeneralMenu.h"
#include "scene/panel/functionPanel/BagPanel.h"
#include "scene/panel/functionPanel/BagCellPanel.h"
#include "userdata/activitydata/SpiderData.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "event/EventProtocol.h"
#include "event/EventDispatcher.h"
#include "ext/CCActionDestroy.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/netdata/GameRole.h"
#include "event/CPEventHelper.h"

const CCPoint startPos=ccp(46,375);
const int width=75;
const int height=68;

SpiderPanel::SpiderPanel()
{

}

SpiderPanel::~SpiderPanel()
{

}

/**
 * SpiderPanel::init() 初始化函数
 * 功能：初始化蜘蛛活动面板的UI布局，包括左右子面板、标题栏和关闭按钮
 * 返回: bool - 初始化是否成功
 */
bool SpiderPanel::init()
{
	// 1. 设置面板的高度和宽度（基于520x1200的设计分辨率）
	m_nHeight = 480;  // 注释：对应480的换算值
	m_nWidth = 800;  // 注释：对应800全屏的换算值
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));
	// 2. 添加覆盖层（半透明黑色遮罩）
	addCover();
	
	// 3. 创建并添加左侧和右侧子面板
	// 左侧面板：可能包含活动说明、任务列表等内容
	SpiderLeftPanel* pleft = SpiderLeftPanel::create();
	addChild(pleft);
	
	// 右侧面板：可能包含蜘蛛活动的主要交互界面
	SpiderRightPanel* pright = SpiderRightPanel::create();
	addChild(pright);
	
	// 注意：这里没有设置子面板的位置，可能在create()函数内部或后续代码中设置
	
	// 4. 创建并添加标题栏背景
	// 从plist资源获取九宫格精灵作为标题栏背景
	CCScale9Sprite* ptitlebkg = SystemData::getScale9SpriteByPlist("activity_spider_titlebkg");
	ptitlebkg->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	addChild(ptitlebkg);
	// 注意：这里没有设置标题栏位置
	
	// 5. 创建并添加标题文本
	// 从系统数据获取标题文本资源
	CCLabelTTF* pTitle = SystemData::getLabelTTF("activity_spider_titlelabel");
	pTitle->setColor(ccWHITE);    // 设置文本颜色为白色
	pTitle->setFontSize(22);      // 设置字体大小为22
	// 设置标题位置在标题栏背景的中心
	pTitle->setPosition(ccp(
		ptitlebkg->getContentSize().width / 2,    // 水平居中
		ptitlebkg->getContentSize().height / 2    // 垂直居中
	));
	ptitlebkg->addChild(pTitle);  // 添加到标题栏背景
	
	// 6. 创建菜单容器（用于放置按钮）
	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	pMenu->setPosition(CCPointZero);      // 设置位置为(0,0)
	addChild(pMenu);                      // 添加到当前面板
	
	// 7. 创建并添加关闭按钮
	// 从plist资源获取关闭按钮图片
	CCMenuItemImage* pclose = SystemData::getMenuItemImageByPlist("activity_spider_close");
	pclose->setTarget(this, menu_selector(SpiderPanel::closecallback));  // 设置点击回调函数
	pMenu->addChild(pclose);  // 添加到菜单容器
	// 注意：这里没有设置关闭按钮的位置
	
	// 8. 初始化成功，返回true
	return true;
	
	// 注意：此函数缺少以下元素的位置设置：
	// 1. 左右子面板的位置
	// 2. 标题栏背景的位置
	// 3. 关闭按钮的位置
	// 这些位置可能在布局数据中定义，但此处未显式设置
}

void SpiderPanel::closecallback( CCObject* pSender )
{/*
	spiderdata::rmvallItem();
	this->removeFromParent();*/
	this->runAction(CCSequence::create(CCCallFunc::create(this,callfunc_selector(SpiderPanel::removeItem)),CCActionInstantRemoveFromParent::create(),NULL));
}

void SpiderPanel::removeItem()
{
	spiderdata::rmvallItem();
}


//-------------------------------------------------------------------------------------------------------//

SpiderLeftPanel::SpiderLeftPanel():
	m_pCurReq2(NULL),
	m_pCurReq1(NULL),
	m_bLock(false),
	m_pItemMenu(NULL),
	m_pCurReqItemCnt(NULL),
	m_pYuanBaoMoney(NULL),
	m_pYuanBao(NULL)
{

}

SpiderLeftPanel::~SpiderLeftPanel()
{

}

bool SpiderLeftPanel::init()
{
	CCScale9Sprite* pbkg1=SystemData::getScale9SpriteByPlist("activity_spider_bkg",SystemData::getLayoutValue("activity_spider_bkg_left.w"),SystemData::getLayoutValue("activity_spider_bkg_left.h"));
	pbkg1->setPosition(SystemData::getLayoutPoint("activity_spider_bkg_left"));
	pbkg1->setAnchorPoint(CCPointZero);
	addChild(pbkg1);

	CCScale9Sprite* pbkg=SystemData::getScale9SpriteByPlist("activity_spider_bkg",SystemData::getLayoutValue("activity_spider_bkg_left.w"),SystemData::getLayoutValue("activity_spider_bkg_left.h"));
	pbkg->setPosition(SystemData::getLayoutPoint("activity_spider_bkg_left"));
	pbkg->setAnchorPoint(CCPointZero);
	addChild(pbkg);


	GeneralMenu* pMenu=GeneralMenu::create();
	pMenu->setAnchorPoint(CCPointZero);
	pMenu->setPosition(CCPointZero);
	pbkg->addChild(pMenu);

	CCMenuItemImage* pLeftBtn=SystemData::getScale9MenuItemImageByPlist("activity_spider_button");
	pLeftBtn->setTag(Btn_Left);
	pLeftBtn->setPosition(SystemData::getLayoutPoint("activity_spider_button_left"));
	pLeftBtn->setTarget(this,menu_selector(SpiderLeftPanel::menucallback));
	pMenu->addChild(pLeftBtn);
	CCLabelTTF* pLeftLabel=SystemData::getLabelTTF("activity_spider_button_left_text");
	pLeftLabel->setColor(ccWHITE);
	pLeftLabel->setFontSize(20);
	pLeftLabel->setPosition(pLeftBtn->getPosition());
	pMenu->addChild(pLeftLabel);

	CCMenuItemImage* pRightBtn=SystemData::getScale9MenuItemImageByPlist("activity_spider_button");
	pRightBtn->setTag(Btn_Right);
	pRightBtn->setPosition(SystemData::getLayoutPoint("activity_spider_button_right"));
	pRightBtn->setTarget(this,menu_selector(SpiderLeftPanel::menucallback));
	pMenu->addChild(pRightBtn);
	CCLabelTTF* pRightLabel=SystemData::getLabelTTF("activity_spider_button_right_text");
	pRightLabel->setColor(ccWHITE);
	pRightLabel->setFontSize(20);
	pRightLabel->setPosition(pRightBtn->getPosition());
	pMenu->addChild(pRightLabel);

	CCLabelTTF* plabel=SystemData::getLabelTTF("activity_spider_conertext");
	plabel->setFontSize(15);
	plabel->setAnchorPoint(ccp(0,0.5));
	plabel->setColor(ccYELLOW);
	plabel->setPosition(SystemData::getLayoutPoint("activity_spider_conertext"));
	pMenu->addChild(plabel);

	m_pCurReqItemCnt=CCLabelTTF::create("","",15);
	m_pCurReqItemCnt->setColor(ccYELLOW);
	m_pCurReqItemCnt->setAnchorPoint(ccp(0,0.5));
	m_pCurReqItemCnt->setPosition(ccp(plabel->getPositionX()+plabel->getContentSize().width+5,plabel->getPositionY()));
	pMenu->addChild(m_pCurReqItemCnt);

	int count=0;
	UserItems items = GameData::s_user->getUserItemData()->userItems;
	for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
	{
		UserItem* pItem=(UserItem*)it->second;
		if (pItem->sid==SystemData::getLayoutValue("斑斓石"))
		{
			count+=pItem->count;
		}
	}
	m_pCurReqItemCnt->setString(SystemData::intToString(count).c_str());


	m_pYuanBao=SystemData::getLabelTTF("activity_spider_button_CLSYYB");//需要金币
	m_pYuanBao->setAnchorPoint(ccp(0,0.5));
	m_pYuanBao->setFontSize(15);	
	m_pYuanBao->setColor(ccYELLOW);
	m_pYuanBao->setPosition(SystemData::getLayoutPoint("activity_spider_button_CLSYYB"));
	pMenu->addChild(m_pYuanBao);
	m_pYuanBaoMoney=SystemData::getLabelTTF("XXXXX");
	m_pYuanBaoMoney->setAnchorPoint(ccp(0,0.5));
	m_pYuanBaoMoney->setFontSize(15);	
	m_pYuanBaoMoney->setColor(ccYELLOW);
	m_pYuanBaoMoney->setPosition(ccp(m_pYuanBao->getPositionX()+m_pYuanBao->getContentSize().width+5,m_pYuanBao->getPositionY()));
	pMenu->addChild(m_pYuanBaoMoney);
	m_pYuanBao->setVisible(false);
	m_pYuanBaoMoney->setVisible(false);
	m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(NULL,Type_Spider,0)).c_str());


	m_pCurReq2=CCLabelTTF::create("","",20);
	m_pCurReq2->setColor(ccYELLOW);
	m_pCurReq2->setPosition(SystemData::getLayoutPoint("activity_spider_textlabel2"));
	pMenu->addChild(m_pCurReq2);
	 
	CCMenuItemImage *plock=SystemData::getMenuItemImageByPlist("forging_xiaokuang");
	plock->setTarget(this,menu_selector(SpiderLeftPanel::menucallback));
	plock->setTag(TAG_LOCK);
	plock->setPosition(SystemData::getLayoutPoint("activity_spider_selectbtn"));
	pMenu->addChild(plock);
	CCLabelTTF* pLabel=SystemData::getLabelTTF("activity_spider_selecttext");
	pLabel->setColor(ccYELLOW);
	pLabel->setAnchorPoint(ccp(0,0.5));
	pLabel->setPosition(ccp(plock->getPositionX()+5,plock->getPositionY()));
	pLabel->setFontSize(15);
	pMenu->addChild(pLabel);

	//摆上空格子
	for (int i=0;i<5;i++)
	{
		for (int j=0;j<4;j++)
		{
			CCSprite* pItem=SystemData::getSpriteByPlist("ui.bag.slot.unlock");
			pItem->setPosition(ccp(startPos.x+i*width,startPos.y-j*height));
			pMenu->addChild(pItem);
		}
	}

	//计算几个斑斓石
	/*CCString* pStr1=CCString::createWithFormat(SystemData::getLayoutString("activity_spider_textlabel1").c_str(),CommonFunction::getCurSpiderReq());
	m_pCurReq1->setString(pStr1->getCString());*/
	CCString* pStr2=CCString::createWithFormat(SystemData::getLayoutString("activity_spider_textlabel2").c_str(),CommonFunction::getCurSpiderReq());
	m_pCurReq2->setString(pStr2->getCString());

	m_pItemMenu=GeneralMenu::create();
	m_pItemMenu->setAnchorPoint(CCPointZero);
	m_pItemMenu->setPosition(CCPointZero);
	pbkg->addChild(m_pItemMenu);

	updateItemMenu();

	return true;
}

void SpiderLeftPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int rvt=0;
		int tag = pNode->getTag();
		switch (tag)
		{
		case TAG_LOCK:
			if (m_bLock)
			{
				if (pNode->getChildByTag(100))
				{
					pNode->removeChildByTag(100);
				}
				m_bLock=false;
				m_pYuanBao->setVisible(false);
				m_pYuanBaoMoney->setVisible(false);
			}
			else
			{
				CCSprite *gouxuan=SystemData::getSpriteByPlist("forging_gouxuan");
				gouxuan->setPosition(ccp(pNode->getContentSize().width/2,pNode->getContentSize().height/2));
				gouxuan->setTag(100);
				pNode->addChild(gouxuan);
				m_bLock=true;
				m_pYuanBao->setVisible(true);
				m_pYuanBaoMoney->setVisible(true);
			}
			break;
		case Btn_Left:
			if (spiderdata::zmjz_list.size()>0)
			{
				spiderdata::m_bisdouble=false;
				int rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(NULL,Type_Spider,m_bLock,0,0,0);
				if (rvt==Error::Success)
				{
					CommonFunction::sendmsgSpider( 0, m_bLock);
				}
				else
				{
					CPEventHelper::uiNotify("","",rvt);
				}
			}
			break;
		case Btn_Right:
			if (spiderdata::zmjz_list.size()>0)
			{
				spiderdata::m_bisdouble=true;
				int rvt=CommonFunction::CheckIsEnoughReqOrMoneyOrOther(NULL,Type_Spider,m_bLock,0,0,0);
				if (rvt==Error::Success)
				{
					CommonFunction::sendmsgSpider( 1, m_bLock);
				}
				else
				{
					CPEventHelper::uiNotify("","",rvt);
				}
			}
			break;
		}
	}
}

void SpiderLeftPanel::updateItemMenu()
{
	CCArray *children = m_pItemMenu->getChildren();
	if (children && children->count() > 0)
	{
		//m_menusItem[i]->removeAllChildren();
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

	// 重新放入物品
	int n=0;
	std::vector<UserItem*>::iterator it=spiderdata::zmjz_list.begin();
	for (it;it!=spiderdata::zmjz_list.end();it++)
	{
		insertItem(*it,n);
		n++;
	}
}

void SpiderLeftPanel::insertItem( UserItem* p, int n )
{
	int i=0;
	int j=0;
	i=n%5;
	j=n/5;
	CCMenuItemImage* pItem=CommonFunction::getItemIcon(p);
	pItem->setTarget(this,menu_selector( SpiderLeftPanel::itemcallback));
	pItem->setPosition(ccp(startPos.x+i*width,startPos.y-j*height));
	m_pItemMenu->addChild(pItem);
}

void SpiderLeftPanel::handleEvent( int channel )
{
	if(channel == EventProtocol::EVENT_SPIDER_ITEM_CHANGE)
	{
		updateItemMenu();

		/*CCString* pStr1=CCString::createWithFormat(SystemData::getLayoutString("activity_spider_textlabel1").c_str(),CommonFunction::getCurSpiderReq());
		m_pCurReq1->setString(pStr1->getCString());*/
		CCString* pStr2=CCString::createWithFormat(SystemData::getLayoutString("activity_spider_textlabel2").c_str(),CommonFunction::getCurSpiderReq());
		m_pCurReq2->setString(pStr2->getCString());

		m_pYuanBaoMoney->setString(SystemData::intToString(CommonFunction::getReqVcoin(NULL,Type_Spider,0)).c_str());
	}
	else if (channel == EventProtocol::EVENT_SPIDER_ITEM_OVER)
	{
		spiderdata::rmvallItem();
		int count=0;
		UserItems items = GameData::s_user->getUserItemData()->userItems;
		for(std::map<short,UserItem*>::iterator it = items.begin(); it!=items.end(); it++)
		{
			UserItem* pItem=(UserItem*)it->second;
			if (pItem->sid==SystemData::getLayoutValue("斑斓石"))
			{
				count+=pItem->count;
			}
		}
		m_pCurReqItemCnt->setString(SystemData::intToString(count).c_str());
		
		EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SPIDER_ITEM_CHANGE);
	}
}

void SpiderLeftPanel::itemcallback( CCObject* pSender )
{
	/*CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	Game::getGameUI()->showTipsPanel(pItem,TAG_Tips_QX);*/

	CCMenuItemImage* pImage=(CCMenuItemImage*)pSender;
	UserItem* pItem=(UserItem*)pImage->getUserData();
	spiderdata::rmvItem( pItem );
	EventDispatcher::sharedEventDispather()->dispatchEvent(EventProtocol::EVENT_SPIDER_ITEM_CHANGE);
}

//-------------------------------------------------------------------------------------------------------------------//

SpiderRightPanel::SpiderRightPanel()
{

}

SpiderRightPanel::~SpiderRightPanel()
{

}

bool SpiderRightPanel::init()
{
	CCScale9Sprite* pbkg1=SystemData::getScale9SpriteByPlist("activity_spider_bkg",SystemData::getLayoutValue("activity_spider_bkg_right.w"),SystemData::getLayoutValue("activity_spider_bkg_right.h"));
	pbkg1->setPosition(SystemData::getLayoutPoint("activity_spider_bkg_right"));
	pbkg1->setAnchorPoint(CCPointZero);
	addChild(pbkg1);

	CCScale9Sprite* pbkg=SystemData::getScale9SpriteByPlist("activity_spider_bkg",SystemData::getLayoutValue("activity_spider_bkg_right.w"),SystemData::getLayoutValue("activity_spider_bkg_right.h"));
	pbkg->setPosition(SystemData::getLayoutPoint("activity_spider_bkg_right"));
	pbkg->setAnchorPoint(CCPointZero);
	addChild(pbkg);
	
	CCLabelTTF* pLabel=SystemData::getLabelTTF("activity_spider_rightmenu_text");
	pLabel->setColor(ccWHITE);
	pLabel->setFontSize(18);
	pLabel->setPosition(SystemData::getLayoutPoint("activity_spider_rightmenu_text"));
	pbkg->addChild(pLabel);

	BagCellPanel* pPanel=BagCellPanel::create(5,4,80,Spider_Bag,Bag_Type_Spider);
	pPanel->setAnchorPoint(CCPointZero);
	pPanel->setPosition(ccp(453,-45));
	addChild(pPanel);
	return true;
}
