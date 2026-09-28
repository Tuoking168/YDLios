#ifndef __CPComboBox_h__
#define __CPComboBox_h__

#include "CCLabelTTF.h"
#include "CCMenu.h"
#include <string>
#include <map>

namespace ComboBoxOpenType
{
	enum
	{
		open_Unsettled,
		open_Up,
		open_Down,
	};
};
class CPComboBox : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate
{
public:
	CPComboBox();
	~CPComboBox();

public:
	static CPComboBox *create(const std::string &normFrame, const std::string &selFrame, const std::string &flagFrame);

	void setLabelStyle(const std::string &fontName, float fontSize, const cocos2d::ccColor3B &color);
	void setChangeHandler(cocos2d::CCObject *target, cocos2d::SEL_CallFuncN func);
	void setChangeHandler_(cocos2d::CCObject *target, cocos2d::SEL_CallFuncN func);

	void addLabelItem(const std::string &text);
	void addLabelItem(const std::string &text, int index);
	void addSpriteItem(const std::string &frame);
	void addSpriteItem(const std::string &frame, int index);

	void setCurrentIndex(int index);
	int getCurrentIndex() const;

	int getItemCount() const;

	void cleanItems();
	void setDirection(int dir);

private:
	bool initWithData(const std::string &normFrame, const std::string &selFrame, const std::string &flagFrame);
	void initUI();
	void onEnter();
	void onExit();
	void refresh();
	void addItem(cocos2d::CCNode *item, int tag);

	void open();
	void close();

	void onClick(cocos2d::CCObject *target);
	void onItem(cocos2d::CCObject *target);

	void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

private:
	cocos2d::CCLabelTTF *mLabel;
	cocos2d::CCSprite *mCurrentItem;
	cocos2d::CCMenu *mItemContainer;
	cocos2d::CCObject *mChangeHandler;
	cocos2d::SEL_CallFuncN mChangeHandleFunc;

	cocos2d::CCObject *mChangeHandler_;
	cocos2d::SEL_CallFuncN mChangeHandleFunc_;

	cocos2d::CCSize mItemSize;

	int mCurrentIndex;
	bool mIsOpen;
	bool mIsItemContainerTouched;
	std::string mNormFrame;
	std::string mSelFrame;
	std::string mFlagFrame;

	typedef std::map<int, std::string> ItemFrameMap;
	ItemFrameMap mItemFrames;

	int m_zOrder;
	int m_iOpenDir;
};

#endif //__CPComboBox_h__