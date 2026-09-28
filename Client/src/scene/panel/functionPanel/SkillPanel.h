#ifndef __SKILL_PANEL_H__
#define __SKILL_PANEL_H__

#include "ext/GeneralMenuListener.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum SkillPanelType
{
	s_RolePanel	=	1,
	s_SettingPanel,
};

class SkillPanel : public GeneralMenuListener , public CCTableViewDataSource, public CCTableViewDelegate
{
public:
	SkillPanel();
	virtual ~SkillPanel();
	bool init(int tag);
	//CREATE_FUNC(SkillPanel);
	static SkillPanel* create(int tag=s_RolePanel);

public:
	//implement the interfaces for the TabelView
	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view){};
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view){};
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell){};
	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);
	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
	
protected:
	//create description for a skill, which is a button tagged with this skill's static id
	CCMenuItem* createSkillDescription(int skillid);
	void clickSkillCallback(CCObject* pSender);
	void showSkillTips(int skillid);
	void setSetting(CCObject* pSender);
	void onSetting(CCObject *target);
private:
	CCTableViewEx*		m_pTableView;
	GeneralMenu*		m_pContainer;
	CCSize				m_szListCellSize;
	int					m_icurSkillPanelType;
};


#endif //__SKILL_PANEL_H__