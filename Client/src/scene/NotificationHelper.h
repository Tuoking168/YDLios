#ifndef __NotificationHelper_h__
#define __NotificationHelper_h__

#include <string>
#include "utils/MacroUtils.h"

namespace cocos2d
{
	class CCNode;
}

namespace NotificationType
{
	enum
	{
		debug = 0,
		normal	= 1,
		trivial	= 2,
		normal_red = 3,
		trivial_red = 4,
		top	= 5,
	};
}

typedef void (*VoidCallBack)();

class LowerRightNotificationPanel;
class NotificationHelper
{
public:
	static void showNote(const std::string &note);
	static void showNote(const std::string &note, int noteType);
	static void showTopNote(const std::string &baseMsg);
	static void showPeaceAreaNote(bool isInto);

	static void checkNetState();

	static void addNode(cocos2d::CCNode *node);

	static void setLowerRightPanel(LowerRightNotificationPanel *panel);

	static void delayRun(float dt, VoidCallBack func);

private:
	CP_MAKE_STATIC_CLASS(NotificationHelper);

private:
	static LowerRightNotificationPanel *sLowerRightPanel;
};

#endif //__NotificationHelper_h__