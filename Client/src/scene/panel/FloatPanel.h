#ifndef __Float_PANEL_H__
#define __Float_PANEL_H__


#include "ext/PartPanel.h"
#include "cocos-ext.h"
#include "ext/GeneralMenu.h"
#include "FloatPanelType.h"
#include <set>

USING_NS_CC_EXT;

enum ButtonType
{
	Button_QD=0,//È·¶¨
	Button_QX,
	Button_Close,
};

typedef void (CCObject::*SEL_FloatPanel)(int);
#define floatpanel_selector(_SELECTOR) (SEL_FloatPanel)(&_SELECTOR)
typedef std::vector<std::string> StrVector;
typedef std::set<int> HideSet;
class FloatPanel : public PartPanel
{
public:
	FloatPanel();
	~FloatPanel();
	virtual bool init(int type);
	void onEnter();
	void onExit();

	static FloatPanel* create(int type);
	static bool needShow(int type);
	static FloatPanel *show(int type, const StrVector &strlist, CCNode *parent, SEL_FloatPanel func);

public:
	void setTipsContent(const StrVector &strlist);
	void setAlignment(CCTextAlignment align);
	void setbtnVisible(bool flag);
	void setselectVisible(bool flag);
	void setHandler(CCObject *target, SEL_FloatPanel func);
	void setData(int data1,int data2);
	virtual void hide();

private:
	void initMain();
	CCArray* initSelectButton();
	GeneralMenu* initButton(int type);
	void blockCallBack(CCObject* pSender);
	void buttonCallBack(CCObject* pSender);

private:
	static const int TypeMax=10;

	int m_iCurrentType;
	CCLabelTTF* m_pContent;
	GeneralMenu* m_pBtnMenu;
	GeneralMenu* m_pSelectMenu;
	CCObject *mTarget;
	SEL_FloatPanel mHandleFunc;
 	bool block[TypeMax];
	int m_data1;
	int m_data2;

	static HideSet sHideSet;
};

#endif//__Float_PANEL_H__