#include "HeadPanel.h"
#include "EntityDefinition.h"
#include "MainUIModule.h"

#include "userdata/LayoutData.h"

#include "controls/CPProgressBar.h"
#include "controls/CPRichText.h"

#include "utils/StringUtils.h"
#include "utils/RichTextUtils.h"


#define HANDRED 100.0f

//////HeadPanel///////////////////////////////////////////////////////
HeadPanel::HeadPanel()
	:mNameLabel(NULL)
	,mLevelLabel(NULL)
	,mJobIcon(NULL)
	,mHeadIcon(NULL)
	,mHPBar(NULL)
	,mMPBar(NULL)
	,mHPLabel(NULL)
	,mMPLabel(NULL)
	,mHandler(NULL)
	,mHandleFunc(NULL)
	,mJob(Entity::etj_zs)
	,mGender(Entity::etgd_male)
	,mVIP(0)
	,mIsOtherPlayer(false)
	,mCurrentHP(0)
	,mMaxHP(0)
	,mCurrentMP(0)
	,mMaxMP(0)
{

}

HeadPanel::~HeadPanel()
{

}

HeadPanel * HeadPanel::create()
{
	return create(false);
}

HeadPanel * HeadPanel::create( bool otherPlayer )
{
	HeadPanel *ret = new HeadPanel;
	if (ret && ret->initWithData(otherPlayer))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	ret = NULL;
	return NULL;
}

bool HeadPanel::initWithData( bool otherPlayer )//????????????ui
{
	if (!CCNode::init())
	{
		return false;
	}
	float panelX = 0.0f;  // ????????X????
	float panelY = 140.0f;  // ????????Y????
	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(panelX, panelY));

	mIsOtherPlayer = otherPlayer;

	initUI();
	refreshHeadIcon();
	refreshJobIcon();

	return true;
}

void HeadPanel::initUI()
{
	// board
	CCSprite *board = LayoutData::getSprite(CPModuleName::MAIN_UI, "headPanelBoard");
	addChild(board);
	setContentSize(board->getContentSize());

	// level
	mLevelLabel = LayoutData::getLabelTTF(CPModuleName::MAIN_UI, "headPanelLevel");
	addChild(mLevelLabel);

	// HP, MP bar, label
	mHPBar = CPProgressBar::create(LayoutData::getSprite(CPModuleName::MAIN_UI, "hpBar"));
	mHPBar->setPercentage(HANDRED);
	mHPBar->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "headPanelHPBar"));
	addChild(mHPBar);

	mMPBar = CPProgressBar::create(LayoutData::getSprite(CPModuleName::MAIN_UI, "mpBar"));
	mMPBar->setPercentage(HANDRED);
	mMPBar->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "headPanelMPBar"));
	addChild(mMPBar);

	mHPLabel = LayoutData::getLabelTTF(CPModuleName::MAIN_UI, "headPanelHP");
	addChild(mHPLabel);

	mMPLabel = LayoutData::getLabelTTF(CPModuleName::MAIN_UI, "headPanelMP");
	addChild(mMPLabel);

	// menu
	CCMenu *menu = CCMenu::create();
	menu->setPosition(CCPointZero);
	addChild(menu);

	CCMenuItem *btn = CCMenuItem::create();
	btn->setTarget(this, menu_selector(HeadPanel::onHead));
	btn->setContentSize(LayoutData::getSize(CPModuleName::MAIN_UI, "headPic"));
	btn->setAnchorPoint(CCPointZero);
	menu->addChild(btn);
	if (mIsOtherPlayer)
	{
		btn->setContentSize(board->getContentSize());
	}
}

void HeadPanel::refreshName()
{
	std::string fullStr = mName;
	if (mVIP > 0)
	{
		fullStr += "{y[V" + StringUtils::toString(mVIP) + "]}";
	}

	if (mNameLabel)
	{
		mNameLabel->removeFromParent();
	}
	mNameLabel = RichTextUtils::getRichText(fullStr, LayoutData::getInt(CPModuleName::MAIN_UI, "headPanelNameFontSize"), 0, 0, CPRichText::AlignLeft, "{", "}");
	mNameLabel->setPosition(LayoutData::getPoint(CPModuleName::MAIN_UI, "headPanelName"));
	addChild(mNameLabel);
}

void HeadPanel::refreshHeadIcon()
{
	if (mHeadIcon)
	{
		mHeadIcon->removeFromParent();
	}
	int jobForIcon = (mJob > Entity::etj_ds) ? Entity::etj_zs : mJob;
	const std::string &key = "headPic" + StringUtils::toString(jobForIcon) + StringUtils::toString(mGender);
	mHeadIcon = LayoutData::getSprite(CPModuleName::MAIN_UI, key);
	mHeadIcon->setAnchorPoint(ccp(0, 1));
	mHeadIcon->setPositionY(getContentSize().height);
	addChild(mHeadIcon);
}

void HeadPanel::refreshJobIcon()
{
	if (mJobIcon)
	{
		mJobIcon->removeFromParent();
	}
	int jobForIcon = (mJob > Entity::etj_ds) ? Entity::etj_zs : mJob;
	const std::string &key = "jobIcon" + StringUtils::toString(jobForIcon);
	mJobIcon = LayoutData::getSprite(CPModuleName::MAIN_UI, key);
	addChild(mJobIcon);
}

void HeadPanel::onHead( CCObject *target )
{
	if (mHandler && mHandleFunc)
	{
		(mHandler->*mHandleFunc)();
	}
}

void HeadPanel::setName( const std::string &name )
{
	mName = name;
	refreshName();
}

void HeadPanel::setLevel( int level )
{
	level = (std::max)(level, 0);
	mLevelLabel->setString(StringUtils::toString(level).c_str());
}

void HeadPanel::setJob( int job )
{
	mJob = job;
	if (mJob < Entity::etj_zs ||
		Entity::etj_omni < mJob)
	{
		mJob = Entity::etj_zs;
	}
	refreshHeadIcon();
	refreshJobIcon();
}

void HeadPanel::setGender( int gender )
{
	mGender = gender;
	if (mGender < Entity::etgd_male ||
		Entity::etgd_female < mGender)
	{
		mGender = Entity::etgd_male;
	}
	refreshHeadIcon();
}

void HeadPanel::setVIP( int vip )
{
	mVIP = vip;
	if (mVIP < 0)
	{
		mVIP = 0;
	}
	refreshName();
}

void HeadPanel::setHP( int curHP, int maxHP )
{
	mCurrentHP = (std::max)(curHP, 0);
	mMaxHP = (std::max)(maxHP, 1);
	mHPBar->setPercentage(mCurrentHP * HANDRED/mMaxHP);

	const std::string &hp = StringUtils::toString(mCurrentHP) + "/" + StringUtils::toString(mMaxHP);
	mHPLabel->setString(hp.c_str());
}

void HeadPanel::setMP( int curMP, int maxMP )
{
	mCurrentMP = (std::max)(curMP, 0);
	mMaxMP = (std::max)(maxMP, 1);
	mMPBar->setPercentage(mCurrentMP * HANDRED/mMaxMP);

	const std::string &mp = StringUtils::toString(mCurrentMP) + "/" + StringUtils::toString(mMaxMP);
	mMPLabel->setString(mp.c_str());
}

int HeadPanel::getCurrentHP() const
{
	return mCurrentHP;
}

int HeadPanel::getMaxHP() const
{
	return mMaxHP;
}

int HeadPanel::getCurrentMP() const
{
	return mCurrentMP;
}

int HeadPanel::getMaxMP() const
{
	return mMaxMP;
}

void HeadPanel::setClickHandler( CCObject *handler, SEL_CallFunc func )
{
	mHandler = handler;
	mHandleFunc = func;
}


