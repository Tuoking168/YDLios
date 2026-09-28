#include "RichTextUtils.h"
#include "cocos2d.h"

#include "script/LuaWrapper.h"

using namespace cocos2d;


static bool initRichStringCount( const std::string &richString, const std::string &delimiterL, const std::string &delimiterR, int &count )
{
	Lua::instance()->push_utf8(richString);
	Lua::instance()->push(delimiterL);
	Lua::instance()->push(delimiterR);
	if (Lua::instance()->call("g_init_rich_string_count", 3, 1) &&
		Lua::instance()->pop(count))
	{
		return true;
	}
	CCLog(">>>Error: lua call failed, g_init_rich_string_count");
	return false;
}

static bool getRichStringData( int index, std::string &text, ccColor3B &color )
{
	int r = 0, g = 0, b = 0;
	Lua::instance()->push(index + 1);
	if (Lua::instance()->call("g_get_rich_string_data", 1, 4) &&
		Lua::instance()->pop(b) &&
		Lua::instance()->pop(g) &&
		Lua::instance()->pop(r) &&
		Lua::instance()->pop_utf8(text))
	{
		color = ccc3(r, g, b);
		return true;
	}
	CCLog(">>>Error: lua call failed, g_init_rich_string_count");
	return false;
}

/////RichTextUtils/////////////////////////////////////////////////////
CPRichText * RichTextUtils::getRichText( const std::string &richString, int fontSize )
{
	return getRichText(richString, fontSize, 0, 0);
}

CPRichText * RichTextUtils::getRichText( const std::string &richString, int fontSize, int width, int height )
{
	return getRichText(richString, fontSize, width, height, CPRichText::AlignLeft);
}

CPRichText * RichTextUtils::getRichText( const std::string &richString, int fontSize, int width, int height, int align )
{
	return getRichText(richString, fontSize, width, height, align, "%[", "%]");
}

CPRichText * RichTextUtils::getRichText( const std::string &richString, int fontSize, int width, int height, int align, const std::string &delimiterL, const std::string &delimiterR )
{
	CPRichText *ret = CPRichText::create(width, height, align);
	int cnt = 0;
	initRichStringCount(richString, delimiterL, delimiterR, cnt);
	std::string text;
	ccColor3B color;
	for (int i = 0; i < cnt; i++)
	{
		if (getRichStringData(i, text, color))
		{
			ret->addItem(new CPRichTextItemLabel(text, "Arial", fontSize, color));
		}
	}
	return ret;
}
