#ifndef __CPCheckBox_h__
#define __CPCheckBox_h__

#include "CCMenuItem.h"
#include "CCLabelTTF.h"

class CPCheckBox : public cocos2d::CCNode
{
public:
	CPCheckBox();
	~CPCheckBox();

public:
	static CPCheckBox *create(cocos2d::CCMenuItem *item, cocos2d::CCNode *selFlag);
	static CPCheckBox *create(cocos2d::CCMenuItem *item, cocos2d::CCNode *selFlag, cocos2d::CCLabelTTF *label);

	void setHandler(cocos2d::CCObject *target, cocos2d::SEL_MenuHandler func);

	void setChecked(bool checked);
	bool isChecked() const;
	void setEnable(bool flag);
	cocos2d::CCLabelTTF *getLabel() const;
	
private:
	bool initWithData(cocos2d::CCMenuItem *item, cocos2d::CCNode *selFlag, cocos2d::CCLabelTTF *label);

	void onClick(cocos2d::CCObject *target);

private:
	cocos2d::CCNode *mSelFlag;
	cocos2d::CCLabelTTF *mLabel;
	cocos2d::CCObject *mTarget;
	cocos2d::SEL_MenuHandler mHandleFunc;
	bool m_bEnable;
};
#endif //__CPCheckBox_h__