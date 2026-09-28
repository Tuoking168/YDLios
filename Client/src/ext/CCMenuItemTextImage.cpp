#include "CCMenuItemTextImage.h"

CCMenuItemTextImage::CCMenuItemTextImage()
: m_pText(NULL)
, m_normalColor(ccWHITE)
, m_selectColor(ccWHITE)//ccc3(80,80,80))
{

}

CCMenuItemTextImage* CCMenuItemTextImage::create( const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector, const char *string, const char *fontName, float fontSize, ccColor3B normalColor )
{
	CCMenuItemTextImage* pItem = new CCMenuItemTextImage();
	if(pItem && pItem->initWithImageAndText(normalImage,selectedImage,NULL,target,selector,string,fontName,fontSize,normalColor))
	{
		pItem->autorelease();
		return pItem;
	}
	return NULL;
}

CCMenuItemTextImage* CCMenuItemTextImage::create( const char *normalImage, const char *selectedImage, const char *disableImage,CCObject* target, SEL_MenuHandler selector, const char *string, const char *fontName, float fontSize, ccColor3B normalColor )
{
	CCMenuItemTextImage* pItem = new CCMenuItemTextImage();
	if(pItem && pItem->initWithImageAndText(normalImage,selectedImage,disableImage,target,selector,string,fontName,fontSize,normalColor))
	{
		pItem->autorelease();
		return pItem;
	}
	return NULL;
}

CCMenuItemTextImage* CCMenuItemTextImage::create( const char *normalImage, const char *selectedImage, const char *disableImage,CCObject* target, SEL_MenuHandler selector )
{
	CCMenuItemTextImage* pItem = new CCMenuItemTextImage();
	if(pItem && pItem->initWithNormalImage(normalImage,selectedImage,disableImage,target,selector))
	{
		pItem->autorelease();
		return pItem;
	}
	return NULL;
}

CCMenuItemTextImage* CCMenuItemTextImage::create()
{
	CCMenuItemTextImage* pItem = new CCMenuItemTextImage();
	if(pItem && pItem->initWithNormalImage(NULL,NULL,NULL,NULL,NULL))
	{
		pItem->autorelease();
		return pItem;
	}
	return NULL;
}

bool CCMenuItemTextImage::initWithImageAndText( const char *normalImage, const char *selectedImage, const char *disableImage, CCObject* target, SEL_MenuHandler selector, const char *string, const char *fontName, float fontSize, ccColor3B normalColor )
{
	if(!initWithNormalImage(normalImage,selectedImage,disableImage,target,selector))
	{
		return false;
	}
	m_pText = CCLabelTTF::create(string,fontName,fontSize);
	if(m_pText)
	{
		m_normalColor = normalColor;
		m_pText->setColor(normalColor);
		m_pText->setPosition(ccp(getContentSize().width/2,getContentSize().height/2));
		addChild(m_pText);
	}
	else
	{
		return false;
	}
	return true;
}

void CCMenuItemTextImage::selected()
{
	CCMenuItemImage::selected();
	if(m_pText)
	{
		m_pText->setColor(m_selectColor);
	}
}

void CCMenuItemTextImage::unselected()
{
	CCMenuItemImage::unselected();
	if(m_pText)
	{
		m_pText->setColor(m_normalColor);
	}
}

void CCMenuItemTextImage::setString( const char* string )
{
	if(m_pText)
	{
		m_pText->setString(string);
	}
}

void CCMenuItemTextImage::setColor( const ccColor3B& color )
{
	m_normalColor = color;
	if(!isSelected())
	{
		m_pText->setColor(m_normalColor);
	}
}

void CCMenuItemTextImage::setSelectedColor( const ccColor3B& color )
{
	m_selectColor = color;
	if(isSelected())
	{
		m_pText->setColor(m_selectColor);
	}
}

void CCMenuItemTextImage::setTextPosition(CCPoint pos)
{
	m_pText->setPosition(pos);
}

CCPoint CCMenuItemTextImage::getTextPosition()
{
	return ccp(m_pText->getPositionX(), m_pText->getPositionY());
}

void CCMenuItemTextImage::addText( const char *string, const char *fontName, float fontSize, ccColor3B normalColor )
{
	if(!m_pText)
	{
		m_pText = CCLabelTTF::create(string,fontName,fontSize);
		if(m_pText)
		{
			m_normalColor = normalColor;
			m_pText->setColor(normalColor);
			m_pText->setPosition(ccp(getContentSize().width/2,getContentSize().height/2));
			addChild(m_pText);
		}
		else
		{
			CCLog("CCMenuItemTextImage::addText, failed to add text: %s.",string);
		}
	}
}
