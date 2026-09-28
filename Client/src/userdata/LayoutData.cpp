#include "LayoutData.h"
#include "StaticData.h"

#include "script/LuaWrapper.h"

#include "controls/CPCheckBox.h"
#include "controls/CPComboBox.h"

static void luaPush( const std::string &module, const std::string &key )
{
	Lua::instance()->push(module);
	Lua::instance()->push(key);
}

static bool luaCall( const std::string &func, int narg, int nret )
{
	if (Lua::instance()->call(func.c_str(), narg, nret))
	{
		return true;
	}
	CCLog(">>>Error: lua call func %s failed!", func.c_str());
	return false;
}

static CCSprite *getSpriteByPath( const std::string &path, bool isPlist = true )
{
	if (path.empty())
	{
		return NULL;
	}

	if (isPlist)
	{
		CCSprite *ret = CCSprite::create();
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path.c_str());
		if(frame)
		{
			ret->initWithSpriteFrame(frame);
			return ret;
		}
		CCLog(">>>Error: getSpriteByPath failed, path = %s", path.c_str());
		return ret;
	}
	CCSprite *ret =  CCSprite::create(path.c_str());
    if (!ret) {
        ret = CCSprite::create(LayoutData::defaultTexture());
    }
    return ret;
}

static CCScale9Sprite *getScale9SpriteByPath( const std::string &path )
{
	if (path.empty())
	{
		return NULL;
	}

	CCScale9Sprite *ret = CCScale9Sprite::createWithSpriteFrameName(path.c_str());
	if (!ret)
	{
		ret = CCScale9Sprite::create(path.c_str());
        if (!ret) {
            ret = CCScale9Sprite::create(LayoutData::defaultTexture());
        }
	}
	return ret;
}

///////////LayoutData////////////////////////////////////////////////////
int LayoutData::getInt( const std::string &module, const std::string &key )
{
	int ret = 0;
	luaPush(module, key);
	if (luaCall("get_layout_int", 2, 1))
	{
		Lua::instance()->pop(ret);
	}
	return ret;
}

float LayoutData::getFloat( const std::string &module, const std::string &key )
{
	float ret = 0;
	luaPush(module, key);
	if (luaCall("get_layout_float", 2, 1))
	{
		Lua::instance()->pop(ret);
	}
	return ret;
}

std::string LayoutData::getString( const std::string &module, const std::string &key )
{
	std::string ret;
	luaPush(module, key);
	if (luaCall("get_layout_string", 2, 1))
	{
		Lua::instance()->pop_utf8(ret);
	}
	return ret;
}

CCPoint LayoutData::getPoint( const std::string &module, const std::string &key )
{
	CCPoint ret = CCPointZero;
	luaPush(module, key);
	if (luaCall("get_layout_point", 2, 2))
	{
		Lua::instance()->pop(ret.y);
		Lua::instance()->pop(ret.x);
	}
	return ret;
}

CCSize LayoutData::getSize( const std::string &module, const std::string &key )
{
	CCSize ret = CCSizeZero;
	luaPush(module, key);
	if (luaCall("get_layout_size", 2, 2))
	{
		Lua::instance()->pop(ret.height);
		Lua::instance()->pop(ret.width);
	}
	return ret;
}

cocos2d::ccColor3B LayoutData::getColor3( const std::string &module, const std::string &key )
{
	ccColor3B ret = ccc3(0, 0, 0);
	luaPush(module, key);
	if (luaCall("get_layout_color", 2, 3))
	{
		int r = 0, g = 0, b = 0;
		Lua::instance()->pop(b);
		Lua::instance()->pop(g);
		Lua::instance()->pop(r);
		ret = ccc3(r, g, b);
	}
	return ret;
}

CCRect LayoutData::getRect( const std::string &module, const std::string &key )
{
	CCRect ret = CCRectZero;
	luaPush(module, key);
	if (luaCall("get_layout_rect", 2, 4))
	{
		Lua::instance()->pop(ret.size.height);
		Lua::instance()->pop(ret.size.width);
		Lua::instance()->pop(ret.origin.y);
		Lua::instance()->pop(ret.origin.x);
	}
	return ret;
}

const char* LayoutData::defaultTexture()
{
    std::string ret =  LayoutData::getString(CPModuleName::COMMON, "defaultPic");
    return ret.c_str();
}

CCSprite * LayoutData::getSprite( const std::string &module, const std::string &key )
{
	CCSprite *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_sprite", 2, 7))
	{
		std::string path;
		int fx = 0, fy = 0;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(fy);
		Lua::instance()->pop(fx);
		Lua::instance()->pop(path);
		ret = getSpriteByPath(path);
		if (ret)
		{
			ret->setFlipX(fx != 0);
			ret->setFlipY(fy != 0);
			ret->setAnchorPoint(anPt);
			ret->setPosition(pt);
		}
	}

	if (!ret)
	{
		CCLog(">>>Error: LayoutData::getSprite failed, module = %s, key = %s", module.c_str(), key.c_str());
		ret = CCSprite::create();
	}
	return ret;
}

CCSprite * LayoutData::getSpriteByFile( const std::string &module, const std::string &key )
{
	CCSprite *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_sprite", 2, 7))
	{
		std::string path;
		int fx = 0, fy = 0;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(fy);
		Lua::instance()->pop(fx);
		Lua::instance()->pop(path);
		ret = getSpriteByPath(path, false);
		if (ret)
		{
			ret->setFlipX(fx != 0);
			ret->setFlipY(fy != 0);
			ret->setAnchorPoint(anPt);
			ret->setPosition(pt);
		}
	}

	if (!ret)
	{
		CCLog(">>>Error: LayoutData::getSpriteByFile failed, module = %s, key = %s", module.c_str(), key.c_str());
		ret = CCSprite::create();
	}
	return ret;
}

CCSprite * LayoutData::getSpriteByFrameName( const std::string &frameName )
{
	return getSpriteByPath(frameName);
}

CCMenuItemImage * LayoutData::getMenuItemImg( const std::string &module, const std::string &key )
{
	CCMenuItemImage *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_menu_item_img", 2, 9))
	{
		std::string norm, sel, dis;
		int fx = 0, fy = 0;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(fy);
		Lua::instance()->pop(fx);
		Lua::instance()->pop(dis);
		Lua::instance()->pop(sel);
		Lua::instance()->pop(norm);
		CCSprite *normSprite = getSpriteByPath(norm);
		if (normSprite)
		{
			normSprite->setFlipX(fx != 0);
			normSprite->setFlipY(fy != 0);
		}
		CCSprite *selSprite = getSpriteByPath(sel);
		if (selSprite)
		{
			selSprite->setFlipX(fx != 0);
			selSprite->setFlipY(fy != 0);
		}
		CCSprite *disSprite = getSpriteByPath(dis);
		if (disSprite)
		{
			disSprite->setFlipX(fx != 0);
			disSprite->setFlipY(fy != 0);
		}
		ret = CCMenuItemImage::create();
		ret->initWithNormalSprite(normSprite, selSprite, disSprite, NULL, NULL);
		ret->setAnchorPoint(anPt);
		ret->setPosition(pt);
	}
	return ret;
}

CCMenuItemFont * LayoutData::getMenuItemFont( const std::string &module, const std::string &key )
{
	CCMenuItemFont *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_menu_item_font", 2, 10))
	{
		std::string text, font;
		int size = 0;
		int r = 0, g = 0, b = 0;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(b);
		Lua::instance()->pop(g);
		Lua::instance()->pop(r);
		Lua::instance()->pop(size);
		Lua::instance()->pop(font);
		Lua::instance()->pop_utf8(text);
		if (text.empty())
		{
			text = " ";
		}
		ret = CCMenuItemFont::create(text.c_str());
		ret->setFontName(font.c_str());
		ret->setFontSizeObj(size);
		ret->setColor(ccc3(r, g, b));
		ret->setAnchorPoint(anPt);
		ret->setPosition(pt);
	}
	return ret;
}

CCLabelTTF * LayoutData::getLabelTTF( const std::string &module, const std::string &key )
{
	CCLabelTTF *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_label", 2, 13))
	{
		std::string text, font;
		int size = 0;
		int align = kCCTextAlignmentCenter;
		CCSize dim = CCSizeZero;
		int r = 0, g = 0, b = 0;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(b);
		Lua::instance()->pop(g);
		Lua::instance()->pop(r);
		Lua::instance()->pop(dim.height);
		Lua::instance()->pop(dim.width);
		Lua::instance()->pop(align);
		Lua::instance()->pop(size);
		Lua::instance()->pop(font);
		Lua::instance()->pop_utf8(text);
		ret = CCLabelTTF::create(text.c_str(), font.c_str(), size, dim, (CCTextAlignment)align);
		ret->setColor(ccc3(r, g, b));
		ret->setAnchorPoint(anPt);
		ret->setPosition(pt);
	}
	return ret;
}

CCScale9Sprite * LayoutData::getScale9Sprite( const std::string &module, const std::string &key )
{
	CCScale9Sprite *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_scale_sprite", 2, 7))
	{
		std::string path;
		CCSize size = CCSizeZero;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(size.height);
		Lua::instance()->pop(size.width);
		Lua::instance()->pop(path);
		ret = getScale9SpriteByPath(path);
		if (ret)
		{
			ret->setContentSize(size);
			ret->setAnchorPoint(anPt);
			ret->setPosition(pt);
		}
		else
		{
			CCLog(">>>Error: LayoutData::getScale9Sprite, module = %s, key = %s", module.c_str(), key.c_str());
		}
	}
	return ret;
}

CCEditBox * LayoutData::getEditBox( const std::string &module, const std::string &key )
{
	CCEditBox *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_edit_box", 2, 14))
	{
		std::string path, text, font;
		int lenMax = 0;
		int fontSize = 0;
		int r = 0, g = 0, b = 0;
		CCSize size = CCSizeZero;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(size.height);
		Lua::instance()->pop(size.width);
		Lua::instance()->pop(b);
		Lua::instance()->pop(g);
		Lua::instance()->pop(r);
		Lua::instance()->pop(fontSize);
		Lua::instance()->pop(font);
		Lua::instance()->pop_utf8(text);
		Lua::instance()->pop(lenMax);
		Lua::instance()->pop(path);
		CCScale9Sprite *scaleSprite = getScale9SpriteByPath(path);
		if (scaleSprite)
		{
			ret = CCEditBox::create(size, scaleSprite);
			if (!text.empty())
			{
				ret->setPlaceHolder(text.c_str());
			}

			if (lenMax > 0)
			{
				ret->setMaxLength(lenMax);
			}

			if (!font.empty())
			{
				ret->setFontName(font.c_str());
				ret->setPlaceholderFontName(font.c_str());
			}

			if (fontSize > 0)
			{
				ret->setFontSize(fontSize);
				ret->setPlaceholderFontSize(fontSize);
			}

			ret->setPlaceholderFontColor(ccc3(r, g, b));
			ret->setFontColor(ccc3(r, g, b));
			ret->setAnchorPoint(anPt);
			ret->setPosition(pt);
		}
	}
	return ret;
}

CCMenuItemImage * LayoutData::getMenuItemLabelImage( const std::string &module, const std::string &key )
{
	CCMenuItemImage *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_menu_item_label_image", 2, 15))
	{
		std::string norm, sel, dis;
		std::string text, font;
		int fontSize = 0;
		int r = 0, g = 0, b = 0;
		CCSize size = CCSizeZero;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(size.height);
		Lua::instance()->pop(size.width);
		Lua::instance()->pop(b);
		Lua::instance()->pop(g);
		Lua::instance()->pop(r);
		Lua::instance()->pop(fontSize);
		Lua::instance()->pop(font);
		Lua::instance()->pop_utf8(text);
		Lua::instance()->pop(dis);
		Lua::instance()->pop(sel);
		Lua::instance()->pop(norm);
		CCScale9Sprite *normSprite = getScale9SpriteByPath(norm);
		CCScale9Sprite *selSprite = getScale9SpriteByPath(sel);
		CCScale9Sprite *disSprite = getScale9SpriteByPath(dis);
		if (!size.equals(CCSizeZero))
		{
			if (normSprite)
			{
				normSprite->setContentSize(size);
			}

			if (selSprite)
			{
				selSprite->setContentSize(size);
			}

			if (disSprite)
			{
				disSprite->setContentSize(size);
			}
		}
		ret = CCMenuItemImage::create();
		ret->initWithNormalSprite(normSprite, selSprite, disSprite, NULL, NULL);
		ret->setAnchorPoint(anPt);
		ret->setPosition(pt);

		size = ret->getContentSize();
		CCLabelTTF *label = CCLabelTTF::create();
		label->setString(text.c_str());
		label->setFontName(font.c_str());
		label->setFontSize(fontSize);
		label->setColor(ccc3(r, g, b));
		label->setPosition(ccp(size.width/2, size.height/2));
		ret->addChild(label, 1, 0);
	}
	return ret;
}

CPCheckBox * LayoutData::getCheckBox( const std::string &module, const std::string &key )
{
	CPCheckBox *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_check_box", 2, 14))
	{
		std::string norm, sel, dis;
		std::string flag;
		std::string text, font;
		int fontSize = 0;
		int r = 0, g = 0, b = 0;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(b);
		Lua::instance()->pop(g);
		Lua::instance()->pop(r);
		Lua::instance()->pop(fontSize);
		Lua::instance()->pop(font);
		Lua::instance()->pop_utf8(text);
		Lua::instance()->pop(flag);
		Lua::instance()->pop(dis);
		Lua::instance()->pop(sel);
		Lua::instance()->pop(norm);

		CCSprite *normSprite = getSpriteByPath(norm);
		CCSprite *selSprite = getSpriteByPath(sel);
		CCSprite *disSprite = getSpriteByPath(dis);
		CCMenuItemImage *item = CCMenuItemImage::create();
		item->initWithNormalSprite(normSprite, selSprite, disSprite, NULL, NULL);

		CCSprite *flagSprite = getSpriteByPath(flag);

		CCLabelTTF *label = CCLabelTTF::create();
		label->setString(text.c_str());
		label->setFontName(font.c_str());
		label->setFontSize(fontSize);
		label->setColor(ccc3(r, g, b));
		
		ret = CPCheckBox::create(item, flagSprite, label);
		ret->setAnchorPoint(anPt);
		ret->setPosition(pt);
	}
	return ret;
}

CPComboBox * LayoutData::getComboBox( const std::string &module, const std::string &key )
{
	CPComboBox *ret = NULL;
	luaPush(module, key);
	if (luaCall("get_layout_combo_box", 2, 12))
	{
		std::string norm, sel;
		std::string flag;
		std::string font;
		int fontSize = 0;
		int r = 0, g = 0, b = 0;
		CCPoint anPt = ccp(0.5, 0.5);
		CCPoint pt = CCPointZero;
		Lua::instance()->pop(pt.y);
		Lua::instance()->pop(pt.x);
		Lua::instance()->pop(anPt.y);
		Lua::instance()->pop(anPt.x);
		Lua::instance()->pop(b);
		Lua::instance()->pop(g);
		Lua::instance()->pop(r);
		Lua::instance()->pop(fontSize);
		Lua::instance()->pop(font);
		Lua::instance()->pop(flag);
		Lua::instance()->pop(sel);
		Lua::instance()->pop(norm);

		ret = CPComboBox::create(norm, sel, flag);
		ret->setLabelStyle(font, fontSize, ccc3(r, g, b));
		ret->setAnchorPoint(anPt);
		ret->setPosition(pt);
	}
	return ret;
}

CCSprite * LayoutData::getItemIcon( int itemSID )
{
	return getItemIcon(itemSID, 1);
}

CCSprite * LayoutData::getItemIcon( int itemSID, int count )
{
	std::string iconStr;
	StaticData::getItemIcon(itemSID, iconStr);
	if (iconStr.empty())
	{
		CCLog(">Error: LayoutData::getItemIcon failed, itemSID = %d", itemSID);
		iconStr = getString(CPModuleName::COMMON, "defaultIcon");
	}
	const std::string iconStr2 = LayoutData::getString(CPModuleName::COMMON, "itemIconPath") + iconStr;
// 	fstream _file;
// 	_file.open(iconStr2,ios::in);
// 	if(!_file)
// 	{
// 		CCLog(">Error: LayoutData::getItemIcon failed, itemSID = %d", itemSID);
// 		iconStr = getString(CPModuleName::COMMON, "defaultIcon");
// 	}
	CCSprite* ret = getSpriteByPath(iconStr2,false);
	if (!ret)
	{
		CCLog(">Error: LayoutData::getItemIcon failed, itemSID = %d", itemSID);
		iconStr = getString(CPModuleName::COMMON, "defaultIcon");
		return getItemIcon(iconStr, count);
	}
	else
	{
		return getItemIcon(ret, count);
	}
	
}

CCSprite * LayoutData::getItemIcon( const std::string &icon, int count )
{
	const std::string &iconStr = LayoutData::getString(CPModuleName::COMMON, "itemIconPath") + icon;
	CCSprite *ret = getSpriteByPath(iconStr, false);
	if (count > 1)
	{
		char ch[64];
		sprintf(ch, "%d", count);
		const std::string &filePath = getString(CPModuleName::COMMON, "itemCountNumber");
		const CCSize &size = getSize(CPModuleName::COMMON, "itemCountNumber");
		CCLabelAtlas *countLabel = CCLabelAtlas::create(ch, filePath.c_str(), size.width, size.height, '0');
		countLabel->setAnchorPoint(CCPointZero);
		ret->addChild(countLabel);
	}
	return ret;
}

CCSprite * LayoutData::getItemIcon( CCSprite* ret, int count )
{
// 	const std::string &iconStr = LayoutData::getString(CPModuleName::COMMON, "itemIconPath") + icon;
// 	CCSprite *ret = getSpriteByPath(iconStr, false);
	// 	bool isD = ret->isDirty();
	// 	if (!isD)
	// 	{
	// 		ret = getSpriteByPath(LayoutData::getString(CPModuleName::COMMON, "itemIconPath") + "default.png",false);
	// 	}
	if (count > 1)
	{
		char ch[64];
		sprintf(ch, "%d", count);
		const std::string &filePath = getString(CPModuleName::COMMON, "itemCountNumber");
		const CCSize &size = getSize(CPModuleName::COMMON, "itemCountNumber");
		CCLabelAtlas *countLabel = CCLabelAtlas::create(ch, filePath.c_str(), size.width, size.height, '0');
		countLabel->setAnchorPoint(CCPointZero);
		ret->addChild(countLabel);
	}
	return ret;
}

cocos2d::CCPoint LayoutData::getCenter( const CCSize &size )
{
	return ccp(size.width/2, size.height/2);
}
