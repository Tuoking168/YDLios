#ifndef __CPTips_h__
#define __CPTips_h__

#include "CCNode.h"
#include "CCTouchDelegateProtocol.h"

class ICloseHandler
{
public:
	virtual ~ICloseHandler(){}

	virtual void close() = 0;
};

//////CPTips////////////////////////////////////////////////
namespace CPTipsType
{
	enum
	{
		autoHide = 0,
		modal,
		lazy,
	};
}
class CPTipsSub;
class CPTips : public cocos2d::CCNode, public cocos2d::CCTargetedTouchDelegate, public ICloseHandler
{
public:
	CPTips();
	~CPTips();
	
	static CPTips *create(CPTipsSub *subNode);
	static CPTips *create(CPTipsSub *subNode, int type);

public:
	void close();

private:
	bool initWithData(CPTipsSub *subNode, int type);
	void onEnter();
	void onExit();

	void registerWithTouchDispatcher(void);

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

private:
	CPTipsSub *mSubNode;
	int mType;
};

///////CPTipsSub/////////////////////////////////////////////////////
typedef void (cocos2d::CCObject::*SEL_ConfirmPanel)(int);
#define confirmpanel_selector(_SELECTOR) (SEL_ConfirmPanel)(&_SELECTOR)
typedef void (cocos2d::CCObject::*SEL_InputPanel)(const std::string &key);
#define inputpanel_selector(_SELECTOR) (SEL_InputPanel)(&_SELECTOR)
class CPTipsSub : public cocos2d::CCNode
{
public:
	CPTipsSub();
	~CPTipsSub();

public:
	void setCloseHandler(ICloseHandler *handler);

protected:
	void close();

private:
	ICloseHandler *mCloseHandler;
};
#endif //__CPTips_h__