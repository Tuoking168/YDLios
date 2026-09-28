#ifndef _ZBJDpanel_H_
#define _ZBJDpanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
USING_NS_CC_EXT;



class ZBJDpanel :
	public BasePanel, public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	ZBJDpanel(void);
	~ZBJDpanel(void);
	static ZBJDpanel* create();
	virtual bool init(const char* filename);
	virtual void handleEvent(int channel);
	virtual void onEnter();
	virtual void onExit();

	virtual void addItem(UserItem* pUserItem);
	virtual void ItemCallBack(CCObject* pSender);
	virtual void InitBlock();
	virtual void removeItem();
	void postClearMsg(int i);

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	virtual void menuCallBack(CCObject *pSender);
	void initContent();
	int getSuoCount();
	void updateSuoCount();
private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pBottomList;//底部menu
	bool m_block1;//第一个锁定框是否锁住
	bool m_block2;//第二个锁定框是否锁住
	bool m_block3;//第三个锁定框是否锁住
	UserItem * m_pUserItem;
	CCLabelTTF *m_pButtonLabel;
	CCLabelTTF* pSJWPK;
	bool m_bflag;
	CCLabelTTF *m_pMoney;
	CCLabelTTF *m_pYuanBao;
	CCLabelTTF *m_pYuanBaoMoney;
	bool m_bLock;
	CCLabelTTF *m_pRoleItemCount;
	CCLabelTTF *m_pScore;
	CCLabelTTF *m_pTotalScore;
	CCLabelTTF *m_pblock[3];
	CCMenuItemImage* m_pSuoItem;
	CCSprite* m_pSuoBkg;
	int m_iSuoCnt;
	int m_iHasSuoCnt;
	int m_iHeight;
	int m_iLastSuoCnt;

	enum ZBSJTAG
	{
		TAG_UP=0,
		TAG_DOWN,
		TAG_UPGRADE,
		TAG_LOCK,
	};
};

#endif//_ZBJDpanel_H_