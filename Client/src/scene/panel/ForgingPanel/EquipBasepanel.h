#ifndef _EquipBasepanel_H_
#define _EquipBasepanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "cocos-ext.h"
#include "event/EventListener.h"
USING_NS_CC_EXT;

struct UserItem;

//装备强化整块最基本界面
class EquipBasepanel :	public BasePanel , public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	EquipBasepanel(void);
	~EquipBasepanel(void);

	void onEnter();

	virtual void handleEvent(int channel);
	virtual void ItemCallBack(CCObject* pSender);
	virtual void MenuCallBack(CCObject* pSender);
	virtual void removeItem();

	virtual void initContent() = 0;
	virtual void addItem(UserItem * pUserItem) = 0;

protected:
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

public:
	void settgtPos(CCPoint pos);
	CCPoint gettgtPos();
	void setContentID(int id);
	int getContentID();

protected:
	UserItem * m_pUserItem;
	CCLabelTTF *m_pYuanBaoMoney;
	CCLabelTTF *m_pMoney;
	int m_iHeight;
	CCLabelTTF* m_pYuanBao;
	bool m_bLock;

	enum EquipTAG
	{
		TAG_LOCK,
	};
private:
	CCPoint m_Postgt;
	int m_iContentID;

};

#endif//_EquipBasepanel_H_