#include "NPCbagPanel.h"
#include "userdata/GameData.h"
#include "userdata/UserData.h"
#include "userdata/SystemData.h"
#include "userdata/netdata/GameRole.h"
#include "userdata/netdata/NetItem.h"

#include "network/HandleMessage.h"
#include "MsgItem.h"
#include "scene/GameUI.h"
#include "event/EventProtocol.h"
#include "ext/CCMenuItemTextImage.h"
#include "ext/CCMenuEx.h"
#include "scene/panel/functionPanel/ItemTooltip.h"
#include "script/LuaWrapper.h"
#include "scene/panel/ForgingPanel/CommonFunction.h"
#include "userdata/UserPetData.h"
#include "scene/panel/shop/NumberKeyboard.h"
#include "EntityDefinition.h"
#include "MsgScene.h"
#include "userdata/luadata/LuaData.h"
#include "scene/panel/FloatPanel.h"
#include "userdata/netdata/GhostManager.h"
#include "MsgTrade.h"
#include "userdata/HeroData.h"

const short PAGE_ONE = 0;
const short PAGE_NUM = 12;

const int ItemOneLine = 6;
const int ItemSize = 74;
const int RectSize = 76;

const int TAG_PUTOFF_PACK = 1003;
const int TAG_SPLIT_PACK = 1004;

const int TAG_NEXT_PAGE = 1005;
const int TAG_PRE_PAGE = 1006;

static const float DOUBLE_CLICK_TIME = 0.2f;


#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

NPCbagPanel::NPCbagPanel():
	m_pRightMenu(NULL),
	m_pBtnMenu(NULL),
	m_leftBag(NULL)
{

}


NPCbagPanel::~NPCbagPanel()
{
}
/*

NPCbagPanel* NPCbagPanel::create()
{
	NPCbagPanel* bagPanel = new NPCbagPanel();
	if(bagPanel && bagPanel->init())
	{
		return bagPanel;
	}

	if (bagPanel)
	{
		delete bagPanel;
	}
	return NULL;
}*/

/**
 * NPCbagPanel 初始化函数
 * 功能：初始化NPC背包面板，包括背景、按钮菜单、标签和关闭按钮等UI元素
 * 返回: bool - 初始化是否成功
 */
bool NPCbagPanel::init()/////////////////////////////////////////npc仓库ui
{
	// 1. 首先调用父类CCLayer的初始化
	if (!CCLayer::init())
	{
		return false; // 父类初始化失败，直接返回false
	}
	float panelX = 200.0f;  // 整个面板的X坐标
	float panelY = 60.0f;  // 整个面板的Y坐标
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	// 2. 设置面板的宽度和高度（基于1200x520的设计分辨率）
	m_nWidth = 800;  // 注释：对应800全屏的换算值
	m_nHeight = 480;  // 注释：对应480的换算值       

	// 3. 创建并添加背景
	// 从plist资源获取九宫格精灵作为背景
	CCScale9Sprite* pbkg = SystemData::getScale9SpriteByPlist("ui_NPCbag_bkg", m_nWidth, m_nHeight);
	pbkg->setPosition(CCPointZero);       // 设置位置为左下角(0,0)
	pbkg->setAnchorPoint(CCPointZero);    // 设置锚点为左下角
	addChild(pbkg);

	// 4. 添加覆盖层（通常为半透明黑色遮罩）
	addCover();

	// 5. 创建按钮菜单容器
	m_pBtnMenu = GeneralMenu::create();  // 创建通用菜单
	m_pBtnMenu->setPosition(CCPointZero);
	m_pBtnMenu->setAnchorPoint(CCPointZero);
	addChild(m_pBtnMenu);

	// 6. 创建并添加左侧标签按钮（静态按钮，无点击回调）
	// 获取左侧标签文本
	CCLabelTTF* plabel1 = SystemData::getLabelTTF("ui_NPCbag_left_text");
	plabel1->setColor(ccWHITE);          // 设置文本颜色为白色
	plabel1->setFontSize(18);            // 设置字体大小为18

	// 创建左侧按钮的正常和选中状态精灵
	// 宽度 = 文本宽度 + 20像素边距，高度从布局配置获取
	CCScale9Sprite* p1 = SystemData::getScale9SpriteByPlist("ui_NPCbag_title", 
		plabel1->getContentSize().width + 20, 
		SystemData::getLayoutValue("ui_func.anniu.h"));
	CCScale9Sprite* p2 = SystemData::getScale9SpriteByPlist("ui_NPCbag_title.sel", 
		plabel1->getContentSize().width + 20, 
		SystemData::getLayoutValue("ui_func.anniu.h"));

	// 创建菜单项精灵（正常状态p2，选中状态p1，无回调函数）
	CCMenuItemSprite* pleftSprite = CCMenuItemSprite::create(p2, p1, NULL, this, NULL);
	pleftSprite->setAnchorPoint(ccp(0, 1));  // 设置锚点为左上角
	pleftSprite->setPosition(SystemData::getLayoutPoint("ui_NPCbag_title1_pos"));  // 从布局获取位置
	m_pBtnMenu->addChild(pleftSprite);

	// 设置文本位置在按钮中心
	plabel1->setColor(ccWHITE);
	plabel1->setPosition(ccp(
		pleftSprite->getPositionX() + pleftSprite->getContentSize().width / 2,
			pleftSprite->getPositionY() - pleftSprite->getContentSize().height / 2
	));
	m_pBtnMenu->addChild(plabel1);

	// 7. 创建并添加右侧第一个标签按钮（角色背包按钮）
	// 获取右侧第一个标签文本
	CCLabelTTF* plabel2 = SystemData::getLabelTTF("ui_NPCbag_right_text1");
	plabel2->setColor(ccWHITE);
	plabel2->setFontSize(18);

	// 创建右侧第一个按钮的正常和选中状态精灵
	CCScale9Sprite* p3 = SystemData::getScale9SpriteByPlist("ui_NPCbag_title", 
		plabel2->getContentSize().width + 20, 
		SystemData::getLayoutValue("ui_func.anniu.h"));
	CCScale9Sprite* p4 = SystemData::getScale9SpriteByPlist("ui_NPCbag_title.sel", 
		plabel2->getContentSize().width + 20, 
		SystemData::getLayoutValue("ui_func.anniu.h"));

	// 创建菜单项精灵，设置点击回调为menucallback函数
	CCMenuItemSprite* prightSprite1 = CCMenuItemSprite::create(p3, p4, NULL, this, menu_selector(NPCbagPanel::menucallback));
	prightSprite1->setTag(e_RoleBag);  // 设置标签标识为角色背包
	prightSprite1->setAnchorPoint(ccp(0, 1));
	prightSprite1->setPosition(SystemData::getLayoutPoint("ui_NPCbag_title2_pos"));
	m_pBtnMenu->addChild(prightSprite1);

	// 设置文本位置在按钮中心
	plabel2->setColor(ccWHITE);
	plabel2->setPosition(ccp(
		prightSprite1->getPositionX() + prightSprite1->getContentSize().width / 2,
		prightSprite1->getPositionY() - prightSprite1->getContentSize().height / 2
	));
	m_pBtnMenu->addChild(plabel2);

	// 8. 创建并添加右侧第二个标签按钮（宠物背包按钮）
	// 获取右侧第二个标签文本
	CCLabelTTF* plabel3 = SystemData::getLabelTTF("ui_NPCbag_right_text2");
	plabel3->setColor(ccWHITE);
	plabel3->setFontSize(18);

	// 创建右侧第二个按钮的正常和选中状态精灵
	CCScale9Sprite* p5 = SystemData::getScale9SpriteByPlist("ui_NPCbag_title", 
		plabel3->getContentSize().width + 20, 
		SystemData::getLayoutValue("ui_func.anniu.h"));
	CCScale9Sprite* p6 = SystemData::getScale9SpriteByPlist("ui_NPCbag_title.sel", 
		plabel3->getContentSize().width + 20, 
		SystemData::getLayoutValue("ui_func.anniu.h"));

	// 创建菜单项精灵，设置点击回调为menucallback函数
	CCMenuItemSprite* prightSprite2 = CCMenuItemSprite::create(p5, p6, NULL, this, menu_selector(NPCbagPanel::menucallback));
	prightSprite2->setTag(e_PetBag);  // 设置标签标识为宠物背包
	prightSprite2->setAnchorPoint(ccp(0, 1));
	// 位置在第一个右侧按钮的右侧
	prightSprite2->setPosition(ccp(
		prightSprite1->getPositionX() + prightSprite1->getContentSize().width,
		prightSprite1->getPositionY()
	));
	m_pBtnMenu->addChild(prightSprite2);

	// 设置文本位置在按钮中心
	plabel3->setColor(ccWHITE);
	plabel3->setPosition(ccp(
		prightSprite2->getPositionX() + prightSprite2->getContentSize().width / 2,
		prightSprite2->getPositionY() - prightSprite2->getContentSize().height / 2
	));
	m_pBtnMenu->addChild(plabel3);

	// 9. 创建关闭按钮菜单容器
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	pMenu->setAnchorPoint(CCPointZero);
	addChild(pMenu);

	// 10. 创建并添加关闭按钮
	// 从plist资源获取关闭按钮图片
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("ui_NPCbag_close");
	pClose->setTarget(this, menu_selector(NPCbagPanel::closeCallBack));  // 设置点击回调
	pClose->setPosition(SystemData::getLayoutPoint("ui_NPCbag_close_pos"));  // 从布局获取位置
	pMenu->addChild(pClose);

	// 11. 创建右侧菜单容器（用于放置背包内容）
	m_pRightMenu = GeneralMenu::create();
	m_pRightMenu->setAnchorPoint(CCPointZero);
	m_pRightMenu->setPosition(CCPointZero);
	addChild(m_pRightMenu);

	/* 注释掉的宠物背包面板创建代码
	BagPanel* bagPanel1 = BagPanel::create(5, 4, SystemData::getLayoutValue("MaxPetBagSlot"), Pet_Bag, Bag_Type_NPCBag);
	bagPanel1->setAnchorPoint(CCPointZero);
	bagPanel1->setPosition(SystemData::getLayoutPoint("ui_NPCbag_right_pos"));
	addChild(bagPanel1);
	*/

	// 12. 初始化左侧和右侧菜单
	initLeftMenu();                // 初始化左侧菜单
	initRightMenu(e_RoleBag);      // 默认初始化角色背包（右侧菜单）

	// 13. 初始化成功，返回true
	return true;
}

void NPCbagPanel::closeCallBack( CCObject* pSender )
{
	this->removeFromParent();
}

void NPCbagPanel::initRightMenu(int tag)
{
	if (m_iCurRightType==tag)
	{
		return;
	}
	m_pRightMenu->removeAllChildren();
	//加载右侧背包
	if (tag==e_PetBag)
	{
		BagPanel* bagPanel1 = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPetBagSlot"),Pet_Bag,Bag_Type_NPCBag);
		bagPanel1->setAnchorPoint(CCPointZero);
		bagPanel1->setPosition(SystemData::getLayoutPoint("ui_NPCbag_right_pos"));
		m_pRightMenu->addChild(bagPanel1);
		if (m_leftBag)
		{
			m_leftBag->setType2(Bag_Type_Pet);
		}
	}
	else if (tag==e_RoleBag)
	{
		BagPanel* bagPanel1 = BagPanel::create(5,4,SystemData::getLayoutValue("MaxPlayerBagSlot"),Self_Bag,Bag_Type_NPCBag);
		bagPanel1->setAnchorPoint(CCPointZero);
		bagPanel1->setPosition(SystemData::getLayoutPoint("ui_NPCbag_right_pos"));
		m_pRightMenu->addChild(bagPanel1);
		if (m_leftBag)
		{
			m_leftBag->setType2(Bag_Type_Self);
		}
	}


	if (m_pBtnMenu->getChildByTag(m_iCurRightType))
	{
		((CCMenuItemImage*)(m_pBtnMenu->getChildByTag(m_iCurRightType)))->unselected();
	}
	if (m_pBtnMenu->getChildByTag(tag))
	{
		((CCMenuItemImage*)(m_pBtnMenu->getChildByTag(tag)))->selected();
	}
	m_iCurRightType=tag;
}

void NPCbagPanel::initLeftMenu()
{
	//加载左侧背包
	m_leftBag = BagPanel::create(5,6,SystemData::getLayoutValue("NPC_bag_count"),NPC_Bag,Bag_Type_Self,1); 
	m_leftBag->setPosition(CCPointZero);
	m_leftBag->setPosition(SystemData::getLayoutPoint("ui_NPCbag_left_pos"));
	addChild(m_leftBag);
}

void NPCbagPanel::menucallback( CCObject* pSender )
{
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag=pNode->getTag();
		initRightMenu(tag);
	}
}

