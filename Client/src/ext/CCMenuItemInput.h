#ifndef __CC_MENU_ITEM_INPUT_EXT___
#define __CC_MENU_ITEM_INPUT_EXT___


#include "cocos2d.h"
#include "CCTextFieldEX.h"

using namespace cocos2d;

class CCMenuItemInput : public cocos2d::CCMenuItem
{
	public:
		CCMenuItemInput()
		{}
		virtual ~CCMenuItemInput();

		virtual void activate();
		virtual void selected();
		virtual void unselected();


	protected:
		CCTextFieldEx *textField;

		bool isPassWord;

		static CCMenuItemInput* _s_current_focus;
};


#endif
