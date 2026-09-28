#ifndef __LayoutData_h__
#define __LayoutData_h__

#include "cocos2d.h"
#include "GUI//CCControlExtension/CCScale9Sprite.h"
#include "GUI/CCEditBox/CCEditBox.h"
#include <string>
#include "CommonModule.h"
#include "utils/MacroUtils.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class CPCheckBox;
class CPComboBox;
class LayoutData
{
public:
	static int getInt(const std::string &module, const std::string &key);
	static float getFloat(const std::string &module, const std::string &key);
	static std::string getString(const std::string &module, const std::string &key);
    
    static const char* defaultTexture();

	static CCPoint getPoint(const std::string &module, const std::string &key);
	static CCSize getSize(const std::string &module, const std::string &key);
	static ccColor3B getColor3(const std::string &module, const std::string &key);
	static CCRect getRect(const std::string &module, const std::string &key);

	static CCSprite *getSprite(const std::string &module, const std::string &key);
	static CCSprite *getSpriteByFile(const std::string &module, const std::string &key);
	static CCSprite *getSpriteByFrameName(const std::string &frameName);
	static CCMenuItemImage *getMenuItemImg(const std::string &module, const std::string &key);
	static CCMenuItemFont *getMenuItemFont(const std::string &module, const std::string &key);
	static CCLabelTTF *getLabelTTF(const std::string &module, const std::string &key);

	static CCScale9Sprite *getScale9Sprite(const std::string &module, const std::string &key);
	static CCEditBox *getEditBox(const std::string &module, const std::string &key);

	static CCMenuItemImage *getMenuItemLabelImage(const std::string &module, const std::string &key);

	static CPCheckBox *getCheckBox(const std::string &module, const std::string &key);

	static CPComboBox *getComboBox(const std::string &module, const std::string &key);

	//
	static CCSprite *getItemIcon(int itemSID);
	static CCSprite *getItemIcon(int itemSID, int count);
	static CCSprite *getItemIcon(const std::string &icon, int count);
	static CCSprite *getItemIcon(CCSprite *ret, int count);
	// conversion
	static CCPoint getCenter(const CCSize &size);

private:
	CP_MAKE_STATIC_CLASS(LayoutData);
};
#endif //__LayoutData_h__