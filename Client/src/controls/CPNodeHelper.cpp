#include "CPNodeHelper.h"

#include "utils/MacroUtils.h"
#include "utils/TestUtils.h"


static int getUTF8CharLength( unsigned char ch )
{
	if (ch < 128)
	{
		return 1;
	}
	else if ((ch & 0xe0) == 0xc0)
	{
		return 2;
	}
	else if ((ch & 0xf0) == 0xe0)
	{
		return 3;
	}
	else if ((ch & 0xf8) == 0xf0)
	{
		return 4;
	}
	else if ((ch & 0xfc) == 0xf8)
	{
		return 5;
	}
	else if ((ch & 0xfe) == 0xfc)
	{
		return 6;
	}
	return -1;
}

static CCDrawNode *getRectNode( const CCSize &size, const ccColor4F &fillColor, const ccColor4F &borderColor )
{
	CCPoint pointArray[4];
	pointArray[0] = CCPointZero;
	pointArray[1] = ccp(size.width, 0);
	pointArray[2] = ccp(size.width, size.height);
	pointArray[3] = ccp(0, size.height);

	CCDrawNode *drawNode = CCDrawNode::create();
	drawNode->drawPolygon(pointArray, 4, fillColor, 1, borderColor);
	return drawNode;
}

static std::string getFirstWord( const std::string &text )
{
	if (text.empty())
	{
		return "";
	}

	const char *p = text.c_str();
	unsigned char ch = (unsigned char) *p;
	const int &len = getUTF8CharLength(ch);
	if (len <= 0)
	{
		return "";
	}
	return text.substr(0, len);
}

static CCSize getStringTextureSize( const std::string &text, const std::string &fontName, int fontSize )
{
	if (text.empty() || fontSize <= 0)
	{
		return CCSizeZero;
	}

	CCTexture2D *texture = new CCTexture2D();
	texture->initWithString(text.c_str(), fontName.c_str(), fontSize * CC_CONTENT_SCALE_FACTOR(), CCSizeZero, kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
	const CCSize &ret = texture->getContentSize();
	texture->release();
	return ret;
}

////////////CPNodeHelper////////////////////////////////////////////////
CCClippingNode * CPNodeHelper::getClippingNode( CCSize size )
{
	CCDrawNode *drawNode = getRectNode(size, ccc4f(1, 1, 1, 0), ccc4f(0, 1, 0, 1));
	CCClippingNode *clipNode = CCClippingNode::create();
	clipNode->setStencil(drawNode);
	return clipNode;
}

CCDrawNode * CPNodeHelper::getBorderNode( CCSize size )
{
	CCDrawNode *drawNode = getRectNode(size, ccc4f(1, 1, 1, 0), ccc4f(0, 1, 0, 1));
	return drawNode;
}

CCLabelTTF * CPNodeHelper::getLabelByWidth( const std::string &text, const std::string &fontName, int fontSize, int width )
{
	std::string currentStr = text;
	std::string labelStr = "";
	int currentWidth = 0;
	std::string word = getFirstWord(text);
	while (!word.empty())
	{
		currentWidth += WordWidthCache::instance().getWordWidth(word, fontName, fontSize);
		if (currentWidth >= width)
		{
			break;
		}
		labelStr += word;
		currentStr = currentStr.substr(word.size());
		word = getFirstWord(currentStr);
	}

	CCLabelTTF *ret = CCLabelTTF::create();
	ret->setString(labelStr.c_str());
	ret->setFontName(fontName.c_str());
	ret->setFontSize(fontSize);
	return ret;
}

CCAction * CPNodeHelper::getScaleToBig()
{
	return CCSequence::create(
		CCScaleTo::create(0.0f, 0.0f),
		CCShow::create(),
		CCEaseBackOut::create(CCScaleTo::create(0.3f, 1.0f)),
		NULL);
}

CCAction * CPNodeHelper::getScaleToSmall()
{
	return CCSequence::create(
		CCScaleTo::create(0.0f, 1.0f),
		CCEaseBackIn::create(CCScaleTo::create(0.3f, 0.0f)),
		CCHide::create(),
		NULL);
}

/////////StringSizeCache//////////////////////////////////////////
WordWidthCache::WordWidthCache()
{}

WordWidthCache & WordWidthCache::instance()
{
	static WordWidthCache ret;
	return ret;
}

int WordWidthCache::getWordWidth( const std::string &word, const std::string &fontName, int fontSize )
{
	const int &len = word.size();
	if (len == 1)
	{
		WordToFontSize::const_iterator it = mCache.find(word);
		if (it != mCache.end())
		{
			const FontSizeToWidth &sizeToWidth = it->second;
			FontSizeToWidth::const_iterator itt = sizeToWidth.find(fontSize);
			if (itt != sizeToWidth.end())
			{
				return itt->second;
			}
		}
		
		const CCSize &size = getStringTextureSize(word, fontName, fontSize);
		mCache[word][fontSize] = size.width;
		return size.width;
	}
	else if (len > 1)
	{
		static const std::string &ZHONG_WEN = "zhong_wen";
		WordToFontSize::const_iterator it = mCache.find(ZHONG_WEN);
		if (it != mCache.end())
		{
			const FontSizeToWidth &sizeToWidth = it->second;
			FontSizeToWidth::const_iterator itt = sizeToWidth.find(fontSize);
			if (itt != sizeToWidth.end())
			{
				return itt->second;
			}
		}
		const CCSize &size = getStringTextureSize(word, fontName, fontSize);
		mCache[ZHONG_WEN][fontSize] = size.width;
		return size.width;
	}
	
	return 0;
}
