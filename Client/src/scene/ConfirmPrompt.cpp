#include "ConfirmPrompt.h"
#include "event/EventDispatcher.h"
#include "userdata/SystemData.h"

ConfirmPrompt* ConfirmPrompt::create( const std::string& strTips, const std::string& strLeftBtn, int nLeftEvent, const std::string& strRightBtn, int nRightEvent )
{
	ConfirmPrompt* pConfirm = new ConfirmPrompt;
	if(pConfirm && pConfirm->init(strTips,strLeftBtn,nLeftEvent,strRightBtn,nRightEvent))
	{
		pConfirm->autorelease();
		return pConfirm;
	}
	if(pConfirm)
	{
		delete pConfirm;
		pConfirm = NULL;
	}
	return NULL;
}

ConfirmPrompt* ConfirmPrompt::create( const std::string& strTips, const std::string& strBtn, int nEvent )
{
	ConfirmPrompt* pConfirm = new ConfirmPrompt;
	if(pConfirm && pConfirm->init(strTips,strBtn,nEvent))
	{
		pConfirm->autorelease();
		return pConfirm;
	}
	if(pConfirm)

	{
		delete pConfirm;
		pConfirm = NULL;
	}
	return NULL;
}

bool ConfirmPrompt::init( const std::string& strTips, const std::string& strLeftBtn, int nLeftEvent, const std::string& strRightBtn, int nRightEvent )
{
	initBackGroud();
	CCLabelTTF* pTips = CCLabelTTF::create(strTips.c_str(),"楷体",18,SystemData::getLayoutSize("ui_float_menu_size"),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	pTips->setAnchorPoint(CCPointZero);
	pTips->setPosition(CCPointZero);
	addChild(pTips);
	
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	int	tag[2] = {nLeftEvent,nRightEvent};
	std::string label[2] = {strLeftBtn,strRightBtn};

	for (int i=0;i<2;i++)
	{
		CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("ui_float_button",70,35);
		CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("ui_float_button.sel",70,35);
		CCMenuItemSprite* pButton=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(ConfirmPrompt::callback));
		pButton->setPosition(ccp(SystemData::getLayoutPoint("ui_float_block1_pos").x+30+(i%2)*130,SystemData::getLayoutPoint("ui_float_block1_pos").y-60-(i/2)*50));
		pButton->setAnchorPoint(CCPointZero);
		pButton->setTag(tag[i]);
		CCLabelTTF* pLabel=CCLabelTTF::create(label[i].c_str(),"微软雅黑",18);
		pLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
		pMenu->addChild(pButton);
		pButton->addChild(pLabel);
	}

	return true;
}

bool ConfirmPrompt::init( const std::string& strTips, const std::string& strBtn, int nEvent )
{
	initBackGroud();
	CCLabelTTF* pTips = CCLabelTTF::create(strTips.c_str(),"楷体",18,SystemData::getLayoutSize("ui_float_menu_size"),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	pTips->setAnchorPoint(CCPointZero);
	pTips->setPosition(CCPointZero);
	addChild(pTips);

	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);

	CCScale9Sprite* p1=SystemData::getScale9SpriteByPlist("ui_float_button",70,35);
	CCScale9Sprite* p2=SystemData::getScale9SpriteByPlist("ui_float_button.sel",70,35);
	CCMenuItemSprite* pButton=CCMenuItemSprite::create(p1,p2,NULL,this,menu_selector(ConfirmPrompt::callback));
	pButton->setAnchorPoint(CCPointZero);
	pButton->setPosition(ccp(SystemData::getLayoutPoint("ui_float_block_pos").x,SystemData::getLayoutPoint("ui_float_block_pos").y-60));
	pButton->setTag(nEvent);
	CCLabelTTF* pLabel=CCLabelTTF::create(strBtn.c_str(),"微软雅黑",18);
	pLabel->setPosition(ccp(pButton->getContentSize().width/2,pButton->getContentSize().height/2));
	pMenu->addChild(pButton);
	pButton->addChild(pLabel);

	return true;
}

/**
 * ConfirmPrompt::initBackGroud() 初始化背景函数
 * 功能：初始化确认提示框的背景、边框、标题栏和关闭按钮等UI元素
 * 返回: bool - 初始化是否成功
 */
bool ConfirmPrompt::initBackGroud()
{
	// 1. 创建并添加对话框边框
	// 从plist资源获取九宫格精灵作为对话框边框
	// 参数说明：
	// "ui_float_menu_border" - 边框资源名称
	// SystemData::getLayoutValue("ui_float_menu_size.w") - 从布局配置获取边框宽度
	// SystemData::getLayoutValue("ui_float_menu_size.h") - 从布局配置获取边框高度
	CCScale9Sprite* pborder = SystemData::getScale9SpriteByPlist(
		"ui_float_menu_border",
		SystemData::getLayoutValue("ui_float_menu_size.w"),
		SystemData::getLayoutValue("ui_float_menu_size.h")
	);
	pborder->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	pborder->setPosition(CCPointZero);     // 设置位置为(0,0)
	addChild(pborder);                     // 添加到当前面板

	// 2. 创建并添加标题栏背景
	// 从plist资源获取九宫格精灵作为标题栏背景
	// 参数说明：
	// "ui_float_menu_title" - 标题栏资源名称
	// SystemData::getLayoutValue("ui_float_menu_size.w") + 2 - 宽度比边框宽2像素（可能为了边框效果）
	// 39 - 标题栏固定高度为39像素
	CCScale9Sprite* pTitle = SystemData::getScale9SpriteByPlist(
		"ui_float_menu_title",
		SystemData::getLayoutValue("ui_float_menu_size.w") + 2,
		39
	);
	pTitle->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	
	// 设置标题栏位置：在边框的上方，并略微偏移以实现视觉叠加效果
	// 水平位置：边框X坐标-1（向左偏移1像素）
	// 垂直位置：边框Y坐标 + 边框高度 - 38（在边框顶部，留出1像素边框）
	pTitle->setPosition(ccp(
		pborder->getPositionX() - 1,  // 向左偏移1像素，可能为了边框阴影效果
		pborder->getPositionY() + pborder->getContentSize().height - 38
	));
	addChild(pTitle);  // 添加到当前面板

	// 3. 设置面板的宽度和高度（基于1200x520的设计分辨率）
	m_nWidth = 800;   // 注释：对应800全屏的换算值
	m_nHeight = 480;   // 注释：对应480的换算值
	
	// 4. 添加覆盖层（半透明黑色遮罩，用于突出显示对话框）
	addCover();

	// 5. 创建关闭按钮菜单容器
	CCMenu* pMenu = CCMenu::create();
	pMenu->setAnchorPoint(CCPointZero);  // 设置锚点为左下角
	pMenu->setPosition(CCPointZero);      // 设置位置为(0,0)
	addChild(pMenu);                      // 添加到当前面板

	// 6. 创建并添加关闭按钮
	// 从plist资源获取关闭按钮图片
	CCMenuItemImage* pClose = SystemData::getMenuItemImageByPlist("ui_float_menu_close");
	
	// 设置关闭按钮位置（从布局配置获取）
	pClose->setPosition(SystemData::getLayoutPoint("ui_float_menu_close_pos"));
	
	// 设置点击回调函数（调用基类BasePanel的关闭回调）
	pClose->setTarget(this, menu_selector(BasePanel::closeCallBack));
	
	// 将关闭按钮添加到菜单容器
	pMenu->addChild(pClose);

	// 7. 初始化成功，返回true
	return true;
}

void ConfirmPrompt::callback( CCObject* pSender )
{
// 	int tag = this->getTag();
// 	EventDispatcher::sharedEventDispather()->dispatchEvent(tag);
// 	closeCallBack(NULL);
	
	CCNode* pNode = dynamic_cast<CCNode*>(pSender);
	if(pNode)
	{
		int tag = pNode->getTag();
		EventDispatcher::sharedEventDispather()->dispatchEvent(tag);
		closeCallBack(NULL);
	}
}

void ConfirmPrompt::closeCallBack( CCObject* pSender )
{
	this->removeFromParent();
}

