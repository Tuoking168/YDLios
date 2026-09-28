#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include "cocos2d.h"
using namespace cocos2d;

class ProgressBar : public CCSprite 
{
public:
	ProgressBar();
	~ProgressBar();

	void setNewProgress(float some, float sum);
	
	bool initWithFile(const char* filename);
	bool initWithSpriteFrameName(const char *pszSpriteFrameName);
	static ProgressBar* create(const char* filename);
	static ProgressBar* createWithSpriteFrameName(const char *pszSpriteFrameName);

	float getOriginalWidth() const;
	float getOriginalHeight() const;

private:
	float m_fOriginalWidth;
	float m_fOriginalHeight;
};


#endif