#ifndef _MergeMainPanel_H_
#define _MergeMainPanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
USING_NS_CC_EXT;

#define POST_MOVE_POS "postmovepos"

enum TopList1
{		
	TAG_HSHC_HSHC=100,
	TAG_HSHC_HSZH,


	TAG_WPHC_LZHC=200,
	TAG_WPHC_BSMJHC,
	TAG_WPHC_ZSJNS,
	TAG_WPHC_ZBHC,
	TAG_WPHC_WPHC,
	TAG_WPHC_CBHC,
	TAG_WPHC_MJS,
};

class MergeMainPanel :
	public BasePanel
{
public:
	MergeMainPanel(void);
	~MergeMainPanel(void);
	static MergeMainPanel* create( int tag=-1 );
	virtual bool init( int tag=-1 );

public:
	virtual void menuCallBack(CCObject *pSender);
	virtual void updateTopList(int tag);
	virtual void addTopFunc(int tag);
	virtual void reloadRightButton();
	virtual void updateRightList(int tag,int type=0);
	virtual void PostNotic(UserItem* pObject);
	int m_iCurrentTopTag;//当前顶部tag

private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pMainMenu;//左边主要Menu
	GeneralMenu* m_pRightMenu;//右边主要Menu
	GeneralMenu* m_pBagMenu;//右边背包Menu
	int m_iCurrentRightTag;//当前右边tag
	int m_iCurrentType;//当前筛选type
};

#endif//_MergeMainPanel_H_