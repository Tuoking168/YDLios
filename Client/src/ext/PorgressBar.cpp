#include "ProgressBar.h"

ProgressBar::ProgressBar()
: m_fOriginalWidth(0)
, m_fOriginalHeight(0)
{
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::setNewProgress(float some, float sum)
{
	if (sum > 0)
	{	
		if(some<0)
		{
			some = 0;
		}
		if (some <= sum)
		{
			//param1: the target rect that that you want to get
			//param2: if the original texture is rotated
			//param3: the target rect's width not the original's texture's width
			setTextureRect(CCRectMake(getTextureRect().origin.x,getTextureRect().origin.y,m_fOriginalWidth*some/sum,m_fOriginalHeight),
				isTextureRectRotated(),CCSizeMake(m_fOriginalWidth*some/sum,m_fOriginalHeight));
		}
		else
		{
			CCLog("Error: percent is biger than 100!");
		}
	}
}

ProgressBar* ProgressBar::create(const char* filename)
{
	ProgressBar* pProgressBar = new ProgressBar();
	if(pProgressBar && pProgressBar->initWithFile(filename))
	{
		pProgressBar->autorelease();
		return pProgressBar;
	}
	CCLog("ProgressBar::create, ERROR, failed to create a progress bar %s.",filename);
	return NULL;
}

bool ProgressBar::initWithFile(const char* filename)
{
	if(CCSprite::initWithFile(filename))
	{
		m_fOriginalWidth = getContentSize().width;
		m_fOriginalHeight = getContentSize().height;
		return true;
	}
	return false;
}


bool ProgressBar::initWithSpriteFrameName( const char *pszSpriteFrameName )
{
	if(CCSprite::initWithSpriteFrameName(pszSpriteFrameName))
	{
		m_fOriginalWidth = getContentSize().width;
		m_fOriginalHeight = getContentSize().height;
		return true;
	}
	return false;
}

ProgressBar* ProgressBar::createWithSpriteFrameName( const char *pszSpriteFrameName )
{
	ProgressBar* pProgressBar = new ProgressBar();
	if(pProgressBar && pProgressBar->initWithSpriteFrameName(pszSpriteFrameName))
	{
		pProgressBar->autorelease();
		return pProgressBar;
	}
	CCLog("ProgressBar::createWithSpriteFrameName, ERROR, failed to create a progress bar %s.",pszSpriteFrameName);
	return NULL;
}

float ProgressBar::getOriginalWidth() const
{
	return m_fOriginalWidth;
}

float ProgressBar::getOriginalHeight() const
{
	return m_fOriginalHeight;
}