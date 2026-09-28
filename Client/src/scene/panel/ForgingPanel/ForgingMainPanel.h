#ifndef _ForgingMainPanel_H_
#define _ForgingMainPanel_H_	
#include "ext/basepanel.h"
#include <string>
#include <vector>
#include "event/EventListener.h"
#include "cocos-ext.h"
#include "userdata/UserItemData.h"
USING_NS_CC_EXT;

#define POST_MOVE_POS "postmovepos"

enum TopList2
{		
	TAG_ZBSJ=0,
	TAG_ZBQH,
	TAG_ZBJD,
	TAG_ZSDZ,
	TAG_SXZY,
	TAG_HWTH,
	TAG_ZBFM,
	TAG_Max2,
	TAG_HWQL = TAG_Max2,
	TAG_QHZY,
	TAG_JDZY,
	TAG_JPZY,
	TAG_JPQX,
	TAG_WMQH,
	TAG_PTQH,
	TAG_QHDM,
	TAG_CBYH,
	TAG_ZJTH,
	TAG_ZJSJ,
	TAG_ZBFM_ZBFM,
	TAG_ZBFM_FMQH,

	TAG_LZ=50,
	TAG_ZSJNS,
	TAG_ZB,
	TAG_WP,
	TAG_CB,
	TAG_MJS,
	TAG_HSHC,
	TAG_Max1,
	TAG_HSZH,

	TAG_SSZB=300,
	TAG_BBWP,
	TAG_CWWP,

	TAG_501=501,
	TAG_502,
	TAG_503,
	TAG_504,
};
class ForgingMainPanel :
	public BasePanel
{
public:
	ForgingMainPanel(void);
	~ForgingMainPanel(void);
	static ForgingMainPanel* create(int type);
	virtual bool init(int type);
	virtual void handleEvent(int channel);

public:
	virtual void menuCallBack(CCObject *pSender);
	virtual void updateTopList(int tag);
	virtual void addTopFunc(int tag);
	virtual void reloadRightButton();
	virtual void updateRightList(int tag,int type=0);
	virtual void PostNotic(UserItem* pObject);
	int m_iCurrentTopTag;//当前顶部tag

	virtual void updateBag(int type);
	
private:
	GeneralMenu* m_pTopList;//顶部menu
	GeneralMenu* m_pMainMenu;//左边主要Menu
	GeneralMenu* m_pRightMenu;//右边主要Menu
	GeneralMenu* m_pBagMenu;//右边背包Menu
	int m_iCurrentRightTag;//当前右边tag
	int m_iCurrentType;//当前筛选type


	
};

#endif//_ForgingMainPanel_H_