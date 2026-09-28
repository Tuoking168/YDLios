#ifndef __PanelFactory_h__
#define __PanelFactory_h__

#include "utils/MacroUtils.h"
#include "CCNode.h"
#include <string>

class PanelFactory
{
public:
	static cocos2d::CCNode *create(const std::string &panelName);

private:
	CP_MAKE_STATIC_CLASS(PanelFactory);
};

#endif //__PanelFactory_h__