#ifndef __BaseElement_h__
#define __BaseElement_h__

#include "CCNode.h"

class BaseElement : public cocos2d::CCNodeRGBA
{
public:
	int getID() const;
	int getType() const;

	void setColor(const cocos2d::ccColor3B &color);
	void setOpacity(GLubyte opacity);

protected:
	BaseElement();
	~BaseElement();

	bool initWithData(int id, int type);

	cocos2d::CCNode *getContainer();

private:
	bool init() {return false;}
	void initUI();

private:
	cocos2d::CCNode *mContainer;

	int mID;
	int mType;
};

#endif //__BaseElement_h__