#ifndef __GAME_UI_H__
#define __GAME_UI_H__

#include "cocos2d.h"
#include "../ext/ProgressBar.h"
#include "ext/RadioGroup.h"
#include "userdata/netdata/HeroAvatar.h"
#include "event/EventListener.h"
#include "event/IEventListener.h"
#include "Game.h"
#include "ext/CCLayerEx.h"
#include "MsgQuest.h"
#include "panel/guild/PopApplicationPanel.h"
#include "event/IEventListener.h"
#include "Login.h"
#include <stack>

using namespace cocos2d;

enum PANEL_TAG
{
    TAG_TALK_PANEL,         // NPC对话面板
    TAG_NPCTASK_PANEL,      // NPC任务面板
    TAG_MINMAP_PANEL,       // 迷你地图面板
    TAG_AI,                 // AI面板
    TAG_TASK_PANEL,         // 任务面板
    TAG_TEAM_PANEL,         // 队伍面板
    TAG_TASKCONTENT_PANEL,  // 任务内容面板
    TAG_MAIN_PANEL,         // 主功能面板
    TAG_FLOAT_PANEL,        // 浮动面板
    TAG_Tips_PANEL,         // 提示面板
    TAG_TRADE_PANEL,        // 交易面板
    TAG_TARGET_PANEL,       // 目标面板
    TAG_NUMBER_PANEL,       // 数字输入面板
    TAG_OPERATION_MENU,     // 操作菜单
    TAG_UNLOCKBAG_PANEL,    // 解锁背包面板
    TAG_ICONTIPS_PANEL,     // 图标提示面板
    TAG_SHOP_PANEL,         // 商店面板
    TAG_MINE_PANEL,         // 采矿面板
    TAG_PET_ADVANCE_PANEL,  // 宠物进阶面板
    TAG_PET_APEATTR_PANEL,  // 宠物属性面板
    TAG_FLYSHOES_MENU,      // 传送菜单
    TAG_PET_REBORN_PANEL,   // 宠物重生面板
    TAG_MAX_PANEL,          // 最大面板数

    // 其他标签
    TAG_HEAD_PIC,           // 头像
    TAG_EASY_HIT,           // 易击
    TAG_EXIT_GAME,          // 退出游戏
    TAG_SHOW_CHAT,          // 显示聊天
    TAG_GROUP_MSG,          // 组队消息
    TAG_MAX,                // 最大标签

    TAG_TREASUREDEPOT_PANEL,// 宝库面板

    TAG_SPECIAL_PANEL = 100,// 特殊面板
    TAG_Mail_PANEL = 101,   // 邮件面板
};

class BasePanel;
class GeneralMenu;
class CCMenuEx;
class ControlPanel;
struct UserItem;
struct UserPet;
class BottomSkillLayer;
class DogSkillPanel;
class FloatPanel;

static std::vector<std::string> emptyStringVector;

class CPComboBox;
class HeadPanel;
/**
 * 游戏主界面类
 * 继承自CCLayer，实现游戏主界面的所有UI功能
 * 同时实现EventListener和IEventListener接口，用于事件处理
 */
class GameUI : public CCLayer, public EventListener, public IEventListener
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	GameUI();		// 构造函数
	~GameUI();		// 析构函数
	
	// implement the "static node()" method manually
	CREATE_FUNC(GameUI);	// Cocos2d-x的CREATE_FUNC宏，用于创建节点
	
	virtual bool init();	// 初始化函数，cocos2d-x中返回bool而非id
	
	// 生命周期函数
	virtual void onEnter();		// 进入场景时调用
	virtual void onExit();		// 退出场景时调用
	
	virtual void handleEvent(int channel);	// 处理事件，继承自IEventListener
	
	virtual void update(float dt);		// 每帧更新函数
	virtual void keyBackClicked();		// 返回键点击回调
	
	// 触摸事件处理函数
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);		// 触摸开始
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);		// 触摸移动
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);		// 触摸结束
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);	// 触摸取消

public:
	// 提示面板相关
	void showTipsPanel(UserItem* pItem, int type, const CCPoint& pos=ccp(300,10), const CCPoint& anpos=CCPointZero);		// 显示物品提示面板
	void showPetBaseTipPanel(UserPet* pPet,int type, const CCPoint& pos=ccp(300,10), const CCPoint& anpos=CCPointZero);	// 显示宠物基础提示面板
	void showSkillTipsPanel(int skillid);		// 显示技能提示面板
	
	// 功能面板显示
	void showBoothPanel(int targeteid,int type,bool isHighBooth);	// 显示摊位面板
	void showTargetPanel();		// 显示目标面板
	void hideTargetPanel();		// 隐藏目标面板
	
	// 数字输入面板
	void showNumberBoard(int *a,int b,int eventc,int d,const std::string& str="");		// 显示数字面板
	void showNumberKeyBoard(int a,int b,int eventc,int d,const std::string& str="");		// 显示数字键盘
	void showNumberKeyBoard(int curValue,int MaxValue,int tag,int sid,int str);			// 重载数字键盘显示
	
	// 浮动和特殊面板
	FloatPanel* showFloatPanel(int type, const std::vector<std::string>& strlist= emptyStringVector ,bool visibleSelect = true, bool visibleButton=true);	// 显示浮动面板
	void showUnlockPanel(int cnt, int bagtype);		// 显示解锁面板
	void showTradePanel();		// 显示交易面板
	void showOperationMenu(int type);	// 显示操作菜单
	void showTalkPanel(bool flag=true);	// 显示对话面板
	void showNPCTaskPanel(int qid);		// 显示NPC任务面板
	void showMinePanel();		// 显示采矿面板
	
	// 宠物系统面板
	void showPetAdvance();		// 显示宠物进阶面板
	void showPetSpeAttr();		// 显示宠物特殊属性面板
	void showPetReborn();		// 显示宠物重生面板
	
	// 其他功能面板
	void showFlyShoes(int data);	// 显示传送鞋功能
	void showBuffTips(int tag);		// 显示Buff提示
	
	// 面板管理
	void showPanel(int tag);		// 显示指定标签的面板
	void hidePanel(int tag);		// 隐藏指定标签的面板
	void hidePanel(CCNode* panel);	// 隐藏指定面板节点
	void hideAllPanels();			// 隐藏所有面板
	CCNode *getPanel(int tag);		// 获取指定标签的面板
	
	void initControlPanel();		// 初始化方向控制按钮面板

private:
	// 初始化函数组
	void initMainMenu();			// 初始化主菜单
	void initIconTips();			// 初始化图标提示
	
	void initHeadPanel();			// 初始化头像面板
	void initExperienceBar();		// 初始化经验条
	void initSkillButtom();			// 初始化技能按钮
	void initControlTipsPanel();	// 初始化左侧控制提示面板（任务，组队，宠物）
	void initAutoMoveNote();		// 初始化自动移动提示
	void initAutoFightNote();		// 初始化自动战斗提示
	void initTeleportButton();		// 初始化传送按钮
	
	void initCommondPanel();		// 初始化GM命令调试窗口
	void initDogSkillPanel();		// 初始化技能面板
	void showDogSkillPanelIfNeed();	// 根据需要显示技能面板
	void hideDogSkillPanel();		// 隐藏技能面板
	
	// 面板管理辅助函数
	void addSubPanel(CCNode *subPanel);		// 添加子面板
	void addSubPanel(CCNode *subPanel, int zOrder);		// 添加子面板（带层级）
	void addSubPanel(CCNode *subPanel, int zOrder, int tag);	// 添加子面板（带层级和标签）
	bool hasSubPanel(int tag);		// 检查是否存在指定标签的子面板
	
	// 地图相关
	void showMapName();			// 显示地图名称
	void initMapName();			// 初始化地图名称显示
	
	// 状态设置
	void setUnlockCount(int count);		// 设置解锁计数
	void setExpProgress();				// 设置经验进度
	void updateAutoMoveFlag();			// 更新自动移动标志
	void updateAutoFightFlag();			// 更新自动战斗标志
	void updateTeleportButton();		// 更新传送按钮状态
	
	// 战斗相关
	void initAttackMode();				// 初始化攻击模式
	void updateAttackMode();			// 更新攻击模式
	void changeAttackModeRequest(int mode);	// 改变攻击模式请求
	void refreshRedBarAndBlueBar();		// 刷新红蓝条
	
	// 显示特效和提示
	void showReliveAlert(int reliveMode,const std::string& killName,int killType);	// 显示复活警告
	void showLevelUp();		// 显示升级特效
	void showDangerous();	// 显示危险提示
	void showBossLifeBar();	// 显示Boss血条
	void hideBossLifeBar();	// 隐藏Boss血条
	void showFireworks(int itemSID);	// 显示烟花特效
	
	// 死亡处理
	void checkDeath(const std::string& killName,int killType);	// 检查死亡状态
	void DeathCallBack(CCObject* pSender);		// 死亡回调
	
	// 其他功能
	void showApplicationPanel();		// 显示应用面板
	void tryToMine(const CCPoint &touchPos);	// 尝试采矿
	
	// 事件处理
	void onChangeAttackMode(CCNode* pSender);	// 改变攻击模式回调
	void onHeadPanel();		// 头像面板点击
	void onTeleport(CCObject *target);	// 传送点击
	void onResetClickState();	// 重置点击状态
	void onCPEvent(const std::string &eventName);	// 控制面板事件
	
	// 更新相关
	void showMiniUpdatePanel(std::string strContent,int panelFormat=NotePanel::normal);	// 显示迷你更新面板
	void miniUpdate(int code);	// 迷你更新

public:
	std::vector<CCNode*> m_panels;	// 存储所有面板的向量

private:
	// UI组件
	CCLayer *mSubPanelContainer;		// 子面板容器
	ProgressBar*	 m_experiencebar;	// 经验条进度条
	
	// 状态指示器
	CCSprite *mAutoMoveNode;		// 自动移动节点
	CCSprite *mAutoFightNode;		// 自动战斗节点
	CPComboBox *mPKModeBox;			// PK模式选择框
	HeadPanel *mHeadPanel;			// 头像面板
	CCMenuItemImage *mTeleportBtn;	// 传送按钮
	
	// 窗口管理
	std::stack<int>	m_pOpenWindowStack;	// 打开的窗口堆栈
	
	// 控制面板
	ControlPanel*	m_pControlPanel;		// 控制面板
	
	// 菜单相关
	CCMenu*				 m_pBelowMenu;		// 底部菜单
	CCLabelTTF*			m_roteLabel;		// 角色标签
	float				m_rotex;			// 角色X坐标
	float				m_rotew;			// 角色宽度
	CCMenu*             m_rolemenu;			// 角色菜单
	
	// 地图显示
	CCNode*				m_mapNameNode;		// 地图名称节点
	CCLabelTTF*			mapCoordinates;		// 地图坐标标签
	
	// 状态标志
	CCSprite*	m_pBuleFlag[3];		// 蓝色标志数组（3个）
	
	// 状态变量
	bool m_bIsDeath;		// 是否死亡标志
	int			m_nBuleFlag;		// 当前蓝色标志索引
	bool		m_bShowBelowMenu;	// 是否显示底部菜单
	bool		m_bBelowMenuIsMoving;	// 底部菜单是否正在移动
	
	// 触摸相关
	bool mIsShortClick;		// 是否是短按点击
	CCPoint mClickPoint;	// 点击点坐标
	
	// 技能面板
	DogSkillPanel* m_DogSkillPanel;	// 技能面板
	
	// 界面布局常量
	const static int BelowY = 80;		// 底部Y坐标
	const static int RightX = 680;		// 右侧X坐标
	const static int LeftX = 100;		// 左侧X坐标
	
	// 地图状态
	bool m_IsInUnknownMap;	// 是否在未知地图中
};

#endif //__GAME_UI_H__