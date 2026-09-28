#ifndef __MAIN_PANEL_H__
#define __MAIN_PANEL_H__

/*
功能：任务栏，显示当前的任务或者可接，并可响应点击任务自动寻路到目标NPC
*/

#include "ext/BasePanel.h"  // 基础面板基类
#include "cocos-ext.h"       // Cocos2d-x扩展库
#include "ext/CCTabelViewEx.h" // 扩展的表格视图
#include "ext/CCMenuEx.h"    // 扩展菜单
#include "event/IEventListener.h" // 事件监听接口

USING_NS_CC_EXT;  // 使用Cocos2d-x扩展命名空间

// 面板标签枚举
enum TAGPanel
{
    TAG_Role_Panel = 0,       // 角色面板
    TAG_Task_Panel,          // 任务面板
    TAG_Activity_Panel,      // 活动面板
    TAG_Enhance_Panel,       // 强化面板
    TAG_Merge_Panel,         // 合成面板
    TAG_Honor_Panel,         // 荣誉面板
    //TAG_Achieve_Panel,     // 成就面板（注释状态）
    //TAG_Shop_Panel,        // 商店面板（注释状态）
    TAG_Society_Panel,       // 社交面板
    TAG_Friend_Panel,        // 好友面板
    TAG_Setting_Panel,       // 设置面板
    TAG_VIP_Panel,          // VIP面板
    TAG_Designation_Panel,   // 称号面板
    TAG_Max_Panel,          // 最大面板数（用作数组大小）

    TAG_TreasureDepot_Panel, // 宝库面板
    TAG_Booth_Panel = 100,   // 摊位面板（从100开始编号）
};

// 主面板类
class MainPanel : public BasePanel, 
                 public CCTableViewDataSource,  // 表格数据源接口
                 public CCTableViewDelegate,    // 表格代理接口
                 public IEventListener         // 事件监听接口
{
public:
    MainPanel();    // 构造函数
    ~MainPanel();   // 析构函数
    virtual bool init(const char* filename);  // 初始化方法
    static MainPanel* create(int tag = TAG_Role_Panel);  // 创建静态方法
    virtual void handleEvent(int channel);    // 事件处理
    void onEnter();  // 进入回调
    void onExit();   // 退出回调

    void onCPEvent(const std::string &eventName);  // CP事件处理
protected:
    // 滚动视图代理方法（空实现）
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
    // 表格视图代理方法（空实现）
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, 
                                 cocos2d::extension::CCTableViewCell* cell){};
    // 表格数据源方法
    virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(
        cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
    virtual void MenuCallBack(CCObject* pSender);  // 菜单回调
    virtual void initLeftFunc(CCMenuItemImage* pItem);  // 初始化左侧功能
    virtual void addPanel(int tag, int type = -1, bool isHighBooth = false);  // 添加面板
    virtual void showOtherPanel(int openpanel);  // 显示其他面板
    virtual void CloseCallBack(CCObject* pSender);  // 关闭回调
    void  checkPanel();  // 检查面板
protected:
    CCMenu* m_pMainMenu;         // 全局主菜单
    CCLayer* m_pRightMenu;       // 右侧功能页面
    CCMenuItemImage* m_pCurrentItem;  // 当前选中菜单项
    CCTableViewEx* m_pTabelViewEx;    // 扩展表格视图
    int m_iCurItemTag;           // 当前选中项的标签
    int m_MaxCellCount;          // 最大单元格数量
    
    // 自定义枚举
    enum MyEnum
    {
        UnlockBagPanel,  // 解锁背包面板
        ClosePanel,      // 关闭面板
    };
    
    std::string func[TAG_Max_Panel];  // 功能名称数组
    int topTag[TAG_Max_Panel];        // 顶部标签数组
};

#endif//__MAIN_PANEL_H__