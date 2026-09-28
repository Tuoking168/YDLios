#ifndef __CPNodeHelper_h__
#define __CPNodeHelper_h__

#include "cocos2d.h"
#include <map>

using namespace cocos2d;

class CPNodeHelper
{
public:
	static CCClippingNode *getClippingNode(CCSize size);
	static CCDrawNode *getBorderNode(CCSize size);
	static CCLabelTTF *getLabelByWidth(const std::string &text, const std::string &fontName, int fontSize, int width);
	static CCAction *getScaleToBig();
	static CCAction *getScaleToSmall();

private:
	CPNodeHelper();
	CPNodeHelper(const CPNodeHelper &);
	CPNodeHelper &operator=(const CPNodeHelper &);
	~CPNodeHelper();
};

////////////StringSizeCache/////////////////////////////////////////
class WordWidthCache
{
public:
	static WordWidthCache &instance();

	int getWordWidth(const std::string &word, const std::string &fontName, int fontSize);
	
private:
	WordWidthCache();

private:
	typedef std::map<int, int> FontSizeToWidth;
	typedef std::map<std::string, FontSizeToWidth> WordToFontSize;
	WordToFontSize mCache;
};
#endif //__CPNodeHelper_h__