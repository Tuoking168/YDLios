#ifndef __SWITCH_MENU_H__
#define __SWITCH_MENU_H__

#include "CCMenu.h"

USING_NS_CC;

class RadioGroup : public CCMenu
{
public:
	RadioGroup();
	~RadioGroup();

	static RadioGroup* create();
    static RadioGroup* create(CCMenuItem* item, ...);
    static RadioGroup* createWithArray(CCArray* pArrayOfItems);
    static RadioGroup* createWithItem(CCMenuItem* item);
    static RadioGroup* createWithItems(CCMenuItem *firstItem, va_list args);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);

	virtual bool setSelectItem(CCMenuItem* currentItem);
	virtual bool setSelectItem(int tag);
	virtual void setInitItemRandom();
	virtual void setInitItem(int tag);

private:
	bool	m_bIsInitial;
};

#endif//__SWITCH_MENU_H__