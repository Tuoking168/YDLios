#include "LaunchedFocus.h"
#include "ActivityModule.h"
#include "EntityDefinition.h"
#include "event/CPEventHelper.h"
#include "event/CPEventDispatcher.h"
#include "userdata/SystemData.h"
#include "userdata/LayoutData.h"
#include "userdata/FuncData.h"
#include "userdata/HeroData.h"
#include "controls/CPItemComponents.h"
#include "utils/StringUtils.h"

LaunchedFocus::LaunchedFocus():
	mFindExpList(NULL),
	m_sid(0),
	pTextLabel3(NULL),
	pStr3(NULL),
	mostExp(0),
	findBtn(NULL)
{
	CPEvtDispatcher.addEventListener(CPEventName::MSG_CHANGE, this);
}

LaunchedFocus::~LaunchedFocus()
{
	CPEvtDispatcher.removeEventListener(CPEventName::MSG_CHANGE, this);
}

/**
 * LaunchedFocus::init() 初始化函数
 * 功能：初始化"首发焦点"或"登录奖励"界面的UI布局
 * 返回: bool - 初始化是否成功
 */
bool LaunchedFocus::init()
{
	// 1. 首先调用父类CCLayer的初始化
	if (!CCLayer::init())
	{
		return false; // 父类初始化失败，直接返回false
	}
	
	// 2. 设置面板的宽度和高度（基于1200x520的设计分辨率）
	m_nWidth = 800;  // 注释：对应800全屏的换算值
	m_nHeight = 480;  // 注释：对应480的换算值
	
	// 3. 创建并添加背景面板
	// 从plist资源获取九宫格精灵作为背景
	// 参数说明：
	// "Login_Reward_bkg" - 登录奖励背景资源名称
	// m_nWidth, m_nHeight - 使用前面定义的宽度和高度
	CCScale9Sprite* pBkg = SystemData::getScale9SpriteByPlist("Login_Reward_bkg", m_nWidth, m_nHeight);
	
	// 设置背景位置在屏幕中心
	pBkg->setPosition(ccp(
		CCDirector::sharedDirector()->getWinSize().width / 2,
		CCDirector::sharedDirector()->getWinSize().height / 2
	));
	
	// 4. 添加覆盖层（半透明黑色遮罩）
	// 参数说明：覆盖层位置为背景面板的左下角坐标
	addCover(ccp(
		pBkg->getPositionX() - m_nWidth / 2,  // 背景左边缘X坐标
		pBkg->getPositionY() - m_nHeight / 2  // 背景下边缘Y坐标
	));
	
	// 5. 将背景添加到当前面板
	addChild(pBkg);
	
	// 6. 创建菜单容器（用于放置按钮）
	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	pMenu->setPosition(CCPointZero);      // 设置位置为(0,0)
	pBkg->addChild(pMenu);                // 添加到背景面板（不是当前面板）
	
	// 7. 创建并添加关闭按钮
	// 从plist资源获取关闭按钮图片
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("Login_Reward_Close");
	
	// 设置关闭按钮的点击回调函数
	pClose->setTarget(this, menu_selector(LaunchedFocus::close));
	
	// 设置关闭按钮位置：背景面板的右上角
	pClose->setPosition(ccp(
		m_nWidth - pClose->getContentSize().width / 2,    // 背景右侧边缘
		m_nHeight - pClose->getContentSize().height / 2    // 背景上侧边缘
	));
	pMenu->addChild(pClose);  // 添加到菜单容器
	
	// 8. 创建并添加标题文本
	// 从系统数据获取标题文本资源
	CCLabelTTF *title = SystemData::getLabelTTF("Launched_focus");
	title->setFontSize(24);                // 设置字体大小为24
	title->setFontName("HiraKakuProN-W3"); // 设置字体名称（日文字体）
	title->setColor(ccORANGE);            // 设置文本颜色为橙色
	// 设置标题位置：屏幕顶部居中，距离顶部26像素
	title->setPosition(ccp(
		CCDirector::sharedDirector()->getWinSize().width / 2,  // 屏幕水平中心
		CCDirector::sharedDirector()->getWinSize().height - 26 // 距离屏幕顶部26像素
	));
	pBkg->addChild(title);  // 添加到背景面板
	
	// 9. 创建并添加内容边框
	// 从plist资源获取内容区域的边框
	// 参数说明：
	// "Launched_focus_border" - 边框资源名称
	// SystemData::getLayoutValue("Launched_focus_border.w") - 从布局配置获取边框宽度
	// SystemData::getLayoutValue("Launched_focus_border.h") - 从布局配置获取边框高度
	CCScale9Sprite* pBorder = SystemData::getScale9SpriteByPlist(
		"Launched_focus_border",
		SystemData::getLayoutValue("Launched_focus_border.w"),
		SystemData::getLayoutValue("Launched_focus_border.h")
	);
	pBorder->setPosition(ccp(10, 20));  // 设置位置：相对背景(10,20)位置
	pBorder->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	pBkg->addChild(pBorder);  // 添加到背景面板
	
	// 10. 初始化UI界面（具体内容在initUI()中实现）
	initUI();
	
	// 11. 设置焦点列表的当前索引为0（默认选中第一个）
	mFindExpList->setCurrentIndex(0);
	
	// 12. 初始化成功，返回true
	return true;
}

void LaunchedFocus::initUI()
{
	CCScale9Sprite *pLeftborder=SystemData::getScale9SpriteByPlist("taskcontent_menuback",306,397);
	pLeftborder->setAnchorPoint(CCPointZero);
	pLeftborder->setPosition(ccp(20,26));
	addChild(pLeftborder);

	CCScale9Sprite *pRightTopborder=SystemData::getScale9SpriteByPlist("taskcontent_menuback",457,180);
	pRightTopborder->setAnchorPoint(CCPointZero);
	pRightTopborder->setPosition(ccp(333,243));
	addChild(pRightTopborder);

	CCScale9Sprite *pRightDownborder=SystemData::getScale9SpriteByPlist("taskcontent_menuback",457,213);
	pRightDownborder->setAnchorPoint(CCPointZero);
	pRightDownborder->setPosition(ccp(333,26));
	addChild(pRightDownborder);

	CCScale9Sprite* pTitlesp = SystemData::getScale9SpriteByPlist("Launched_focus_biaotisprite",pRightDownborder->getContentSize().width,SystemData::getLayoutValue("copynotify_title.h"));
	pTitlesp->setPosition(ccp(563,221));
	addChild(pTitlesp);

	CCLabelTTF* pTitle = SystemData::getLabelTTF("Launched_focus_outlineExp");
	pTitle->setColor(ccYELLOW);
	pTitle->setFontSize(22);
	pTitle->setPosition(pTitlesp->getPosition());
	addChild(pTitle);

	int outlineTime = HeroData::getProp(Entity::attr_ex_exp_time)/3600;
	int outLineExp5times = outlineTime*100*5;
	mostExp = outlineTime*100*1;
	CCString* pStr1 = CCString::createWithFormat(SystemData::getLayoutString("Launched_focus_text1").c_str(),outlineTime);
	CCString* pStr2 = CCString::createWithFormat(SystemData::getLayoutString("Launched_focus_text2").c_str(),outLineExp5times);
	pStr3 = CCString::createWithFormat(SystemData::getLayoutString("Launched_focus_text3").c_str(),mostExp);

	CCLabelTTF* pTextLabel1 = CCLabelTTF::create(pStr1->getCString(),"",20);
	pTextLabel1->setColor(ccGREEN);
	pTextLabel1->setDimensions(CCSizeMake(pRightDownborder->getContentSize().width,0));
	pTextLabel1->setPosition(ccp(560,190));
	addChild(pTextLabel1);

	CCLabelTTF* pTextLabel2 = CCLabelTTF::create(pStr2->getCString(),"",16);
	pTextLabel2->setColor(ccGREEN);
	pTextLabel2->setDimensions(CCSizeMake(pRightDownborder->getContentSize().width,0));
	pTextLabel2->setPosition(ccp(560,165));
	addChild(pTextLabel2);

	pTextLabel3 = CCLabelTTF::create(pStr3->getCString(),"",16);
	pTextLabel3->setColor(ccORANGE);
	pTextLabel3->setDimensions(CCSizeMake(pRightDownborder->getContentSize().width,0));
	pTextLabel3->setPosition(ccp(560,90));
	addChild(pTextLabel3);

	CCLabelTTF* pTextLabel4 = SystemData::getLabelTTF("Launched_focus_text4");
	pTextLabel4->setFontSize(16);
	pTextLabel4->setColor(ccORANGE);
	pTextLabel4->setDimensions(CCSizeMake(pRightDownborder->getContentSize().width,0));
	pTextLabel4->setPosition(ccp(560,65));
	addChild(pTextLabel4);

	CCLabelTTF* pTextLabel5 = SystemData::getLabelTTF("Launched_focus_text5");
	pTextLabel5->setFontSize(16);
	pTextLabel5->setColor(ccORANGE);
	pTextLabel5->setDimensions(CCSizeMake(pRightDownborder->getContentSize().width,0));
	pTextLabel5->setPosition(ccp(560,40));
	addChild(pTextLabel5);

	const CCSize &listSize = LayoutData::getSize(CPModuleName::ACTIVITY, "findOutLineExpList");
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "findOutLineExpListItem");
	const int cnt = LayoutData::getInt(CPModuleName::ACTIVITY, "findOutLineExpListItemCnt");
	mFindExpList = CPItemComponents::create(listSize, new CPLayoutGrid(cnt, itemSize, true));
	mFindExpList->setPosition(ccp(pTitlesp->getPositionX(),pTitlesp->getPositionY()-90));
	addChild(mFindExpList);
	for (int i = 0; i < cnt; i++)
	{
		CCMenuItem *btn = getChooseFindNum(i);
		btn->setTarget(this, menu_selector(LaunchedFocus::onChangeNum));
		mFindExpList->addItem(btn);
	}

	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCScale9Sprite * normalsprite = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY,"norm");
	CCScale9Sprite * selectsprite = LayoutData::getScale9Sprite(CPModuleName::ACTIVITY,"sel"); 

	findBtn=CCMenuItemSprite::create(normalsprite,selectsprite);
	findBtn->setTarget(this,menu_selector(LaunchedFocus::onFindExp));
	findBtn->setPosition(ccp(750,45));
	menu->addChild(findBtn);

	CCLabelTTF* pLbl=SystemData::getLabelTTF("btn_findExpLabel");
	pLbl->setFontSize(14);
	pLbl->setColor(ccWHITE);
	pLbl->setPosition(ccp(findBtn->getContentSize().width/2,findBtn->getContentSize().height/2));
	findBtn->addChild(pLbl);
}

void LaunchedFocus::onCPEvent( const std::string &eventName )
{
	const std::string &evtSource = CPEventHelper::getEventSource();
	if (eventName == CPEventName::MSG_CHANGE)
	{
		if (evtSource=="HandleMessageUpdPlayerPropsDataNotify")
		{
			if (CPEventHelper::getEventIntData(CPEventData::VALUE_2) == Entity::attr_ex_exp_time)
			{
				addFlag();
			}
		}
	}
}

void LaunchedFocus::close( CCObject* pSender )
{
	this->removeFromParent();
}

void LaunchedFocus::onChangeNum( CCObject* pSender )
{
	int index = mFindExpList->getCurrentIndex();
	int outlineTime = HeroData::getProp(Entity::attr_ex_exp_time)/3600;
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if (pNode)
	{
		m_sid = SystemData::getLayoutValue("lixiandan_sid_"+SystemData::intToString(index+1));
		if (index == 3)
		{
			index = 4;
		}
		mostExp = outlineTime*100*(index+1);
		pStr3 = CCString::createWithFormat(SystemData::getLayoutString("Launched_focus_text3").c_str(),mostExp);
		pTextLabel3->setString(pStr3->getCString());
	}
}

CCMenuItem * LaunchedFocus::getChooseFindNum( int index )
{
	const CCSize &itemSize = LayoutData::getSize(CPModuleName::ACTIVITY, "findOutLineExpListItem");
	CCSprite *norm = LayoutData::getSprite(CPModuleName::ACTIVITY, "findExpCheckedBoard");
	CCSprite *sel = LayoutData::getSprite(CPModuleName::ACTIVITY, "findExpCheckedBoard");
	CCSprite *flag = LayoutData::getSprite(CPModuleName::ACTIVITY, "findExpCheckedFlag");
	sel->addChild(flag);
	CCMenuItemSprite *ret = CCMenuItemSprite::create(norm, sel);
	ret->setContentSize(itemSize);
	ret->setTarget(this, menu_selector(LaunchedFocus::onChangeNum));
	CCString* pStr = CCString::createWithFormat(SystemData::getLayoutString("outline_findExp_num").c_str(),index+1);
	CCLabelTTF* pFound = SystemData::getLabelTTF(pStr->getCString());
	pFound->setPosition(ccp(63,17));
	pFound->setColor(ccORANGE);
	pFound->setFontSize(14);
	ret->addChild(pFound);
	
	return ret;
}

void LaunchedFocus::onEnter()
{
	CCLayer::onEnter();
	addFlag();
}

void LaunchedFocus::onFindExp( CCObject* pSender )
{
	FuncData::sendFuncMsgWithID(13,m_sid,0,0);
}

void LaunchedFocus::addFlag()
{
	int outlineTime = HeroData::getProp(Entity::attr_ex_exp_time)/3600;
	if (outlineTime == 0)
	{
		CCSprite* pFlag = SystemData::getSpriteByPlist("Login_Reward_hasget");
		pFlag->setPosition(ccp(737,178));
		addChild(pFlag);
	}
	if (outlineTime>0)
	{
		findBtn->setVisible(true);
	}
	else
	{
		findBtn->setVisible(false);
	}
}





