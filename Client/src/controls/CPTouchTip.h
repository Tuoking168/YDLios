#ifndef __CPTouchTip_h__
#define __CPTouchTip_h__

#include "cocos-ext.h"
#include "cocos2d.h"
#include "PartPanel.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CPTouchTip : public PartPanel
{
public:
	CPTouchTip();
	~CPTouchTip();
	CREATE_FUNC(CPTouchTip);
	virtual bool init();
    void setString(std::string note);
private:
	void initUI();
	void close();
    void onEnter();
private:
    CCLabelTTF* m_content;
    CCScale9Sprite *m_bg;
    CCSprite* m_anim;
};
#endif //__CPTouchTip_h__