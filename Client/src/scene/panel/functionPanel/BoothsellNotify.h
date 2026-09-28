#ifndef __BoothsellNotify_H__
#define __BoothsellNotify_H__


#include "ext/BasePanel.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
#include "event/IEventListener.h"
#include "userdata/BoothData.h"
USING_NS_CC_EXT;

struct BSData
{
	int sid;
	int price;
	int type;
};

class BoothsellNotify: public BasePanel
{
public:
	BoothsellNotify();
	~BoothsellNotify();
	static BoothsellNotify* create(int idx);
	virtual bool init(int idx);

private:
	void initUI();
	void initSellDesc(int idx);
	void close(CCObject* pSender);

private:
	int copyID;
	sellData sd;
	CCLayer* descLayer;
	CCLabelTTF* m_textDesc;
	CCLabelTTF* m_copyName;
	CCLabelTTF* m_recLvl;
	CCLabelTTF* m_recBattel;

};

#endif