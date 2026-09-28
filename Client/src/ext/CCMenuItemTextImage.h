#ifndef __CC_MENU_ITEM_TEXT_IMAGE_H__
#define __CC_MENU_ITEM_TEXT_IMAGE_H__

#include "cocos2d.h"
USING_NS_CC;

class CCMenuItemTextImage : public CCMenuItemImage
{
public:
	CCMenuItemTextImage();
	static CCMenuItemTextImage* create();
	static CCMenuItemTextImage* create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector, const char *string, const char *fontName, float fontSize, ccColor3B normalColor);
	static CCMenuItemTextImage* create(const char *normalImage, const char *selectedImage,  const char *disableImage,CCObject* target, SEL_MenuHandler selector, const char *string, const char *fontName, float fontSize, ccColor3B normalColor);
	static CCMenuItemTextImage* create(const char *normalImage, const char *selectedImage,  const char *disableImage,CCObject* target, SEL_MenuHandler selector);
	bool initWithImageAndText(const char *normalImage, const char *selectedImage, const char *disableImage, CCObject* target, SEL_MenuHandler selector, const char *string, const char *fontName, float fontSize, ccColor3B normalColor);
	void addText(const char *string, const char *fontName, float fontSize, ccColor3B normalColor);

public:
	void setColor(const ccColor3B& color);
	void setSelectedColor(const ccColor3B& color);
	void setString(const char* string);
	CCPoint getTextPosition();
	void setTextPosition(CCPoint pos);

	virtual void selected();
	virtual void unselected();

protected:
	CCLabelTTF* m_pText;
	ccColor3B m_selectColor;
	ccColor3B m_normalColor;
};

#endif//__CC_MENU_ITEM_TEXT_IMAGE_H__