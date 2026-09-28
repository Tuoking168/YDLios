#ifndef __HeadPanel_h__
#define __HeadPanel_h__

#include "cocos2d.h"
#include <string>

using namespace cocos2d;

class CPProgressBar;
class CPRichText;
class HeadPanel : public CCNode
{
public:
	HeadPanel();
	~HeadPanel();

	static HeadPanel *create();
	static HeadPanel *create(bool otherPlayer);

public:
	void setName(const std::string &name);
	void setLevel(int level);
	void setJob(int job);
	void setGender(int gender);
	void setVIP(int vip);

	void setHP(int curHP, int maxHP);
	void setMP(int curMP, int maxMP);

	int getCurrentHP() const;
	int getMaxHP() const;
	int getCurrentMP() const;
	int getMaxMP() const;

	void setClickHandler(CCObject *handler, SEL_CallFunc func);

private:
	bool initWithData(bool otherPlayer);
	void initUI();
	void refreshName();
	void refreshHeadIcon();
	void refreshJobIcon();

	void onHead(CCObject *target);

private:
	CPRichText *mNameLabel;
	CCLabelTTF *mLevelLabel;
	CCSprite *mJobIcon;
	CCSprite *mHeadIcon;
	CPProgressBar *mHPBar;
	CPProgressBar *mMPBar;
	CCLabelTTF *mHPLabel;
	CCLabelTTF *mMPLabel;

	CCObject *mHandler;
	SEL_CallFunc mHandleFunc;

	std::string mName;
	int mJob;
	int mGender;
	int mVIP;
	bool mIsOtherPlayer;
	int mCurrentHP;
	int mMaxHP;
	int mCurrentMP;
	int mMaxMP;
};
#endif //__HeadPanel_h__