#include "CCMenuItemInput.h"
#include "cocos2d.h"

using namespace cocos2d;



void CCMenuItemInput::activate()
{
	if(isEnabled())
	{
		CCMenuItem::activate();
	}
}
void CCMenuItemInput::selected()
{
	// subclass to change the default action
	if(isEnabled())
	{
		CCMenuItem::selected();

	}
}
void CCMenuItemInput::unselected()
{
	// subclass to change the default action
	if(isEnabled())
	{
		CCMenuItem::unselected();

	}
}


CCMenuItemInput::~CCMenuItemInput()
{
}


