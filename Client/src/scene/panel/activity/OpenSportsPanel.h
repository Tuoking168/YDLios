#ifndef _OpenSportsPanel_
#define _OpenSportsPanel_	

#include <string>
#include <vector>
#include "scene/panel/FullScreenPanel.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ext/CCTabelViewEx.h"
#include "userdata/UserItemData.h"
#include "controls/CPUpdater.h"
#include "scene/panel/OptionsHelper.h"
USING_NS_CC;
USING_NS_CC_EXT;

class CCMenuEx;
class CPItemComponents;

class OpenSportsPanel :public BasePanel
{
public:
	OpenSportsPanel();
	~OpenSportsPanel();
	bool init();
	CREATE_FUNC(OpenSportsPanel);
	
private:
	GeneralMenu* m_pMainMenu;
};

#endif//_OpenSportsPanel_