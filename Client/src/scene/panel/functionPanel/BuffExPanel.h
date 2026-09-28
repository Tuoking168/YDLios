#ifndef __SoulStone_PANEL_H__
#define __SoulStone_PANEL_H__

// Show character panel,idle animation,equipments,name,level...etc

#include "cocos2d.h"
#include "ext/basepanel.h"
#include "ext/PartPanel.h"
#include "event/IEventListener.h"
USING_NS_CC;


class BuffExPanel : public BasePanel, public IEventListener
{
public:
	BuffExPanel();
	virtual ~BuffExPanel();
	CREATE_FUNC(BuffExPanel);
	virtual bool init();

	void onCPEvent(const std::string &eventName);

private:
	void updateBuff();
	void buffCallBack(CCObject* pSender);
};

class BuffTips : public PartPanel, public IEventListener
{
public:
	BuffTips();
	virtual ~BuffTips();
	static BuffTips* create(int tag);
	virtual bool init(int tag);

	void onCPEvent(const std::string &eventName);

private:
	CCLabelTTF* m_pTime;
	int m_iOddTime;
	int m_iTag;
};

#endif