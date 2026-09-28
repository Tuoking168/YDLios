#ifndef __WORSHIP_PANEL_H__
#define __WORSHIP_PANEL_H__

#include "scene/panel/FullScreenPanel.h"

#include "event/EventListener.h"


class CPCheckBox;
class CPComboBox;
class WorshipPanel : public FullScreenPanel, public EventListener
{
public:
	WorshipPanel();
	~WorshipPanel();
	CREATE_FUNC(WorshipPanel);
	
	bool init();
	void onEnter();
	void onExit();

private:
	void initUI();
	void dataRequest();

	void callback(CCObject* psender);
	void onRefreshTarget(int btnType);
	void onAddCount(int btnType);

	void addOneExpGrid(int id);

	void randomMultiple();
	//update the experience and multiple, and the refresh times
	void updateMultipleLabels();
	//update the double worship tips
	void updateDoubleWorshipTips();
	//update the worship times and times that can be added
	void updateWorshipTimes();

	void handleEvent(int channel);
	void onCPEvent(const std::string &eventName);

private:
	//random select border
	CCNode *m_pGoldenBorder;
	CPCheckBox *mCheckBox;
	CPComboBox *mComboBox;

	//the random result
	CCLabelTTF*		m_pFinalMultiple;
	CCLabelTTF*		m_pFinalExperience;
	CCLabelTTF*		m_pRefreshTimes;

	//double worship tips
	CCLabelTTF*		m_pDoubleWorship;

	//worship times
	CCLabelTTF*		m_pWorshipTimes;
	CCLabelTTF*		m_pAddTimes;
};



#endif//__WORSHIP_PANEL_H__