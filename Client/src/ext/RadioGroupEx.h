#ifndef __RadioGroupEx_MENU_H__
#define __RadioGroupEx_MENU_H__

#include "CCMenu.h"

USING_NS_CC;

class RadioGroupEx : public CCMenu
{
public:
	RadioGroupEx();
	~RadioGroupEx();

	static RadioGroupEx* create();
    static RadioGroupEx* create(CCMenuItem* item, ...);
    static RadioGroupEx* createWithArray(CCArray* pArrayOfItems);
    static RadioGroupEx* createWithItem(CCMenuItem* item);

	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);

	virtual bool setSelectItem(CCMenuItem* currentItem);
	virtual bool setSelectItem(int tag);
	virtual void setInitItemRandom();
	
public:
	void	clearSelect();
};

#endif//__RadioGroupEx_MENU_H__