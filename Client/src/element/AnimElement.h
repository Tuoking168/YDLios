#ifndef __AnimElement_h__
#define __AnimElement_h__

#include "BaseElement.h"
#include <map>

class CCFlashAnimation;
class AnimElement : public BaseElement
{
public:
	AnimElement();
	~AnimElement();

public:
	static AnimElement *create(int id, int type);
	static AnimElement *create(int id, int type, int gender);
	void setCloth(int clothID);
	void setWeapon(int weaponID);
	void setWings(int wingsID);

	void refreshShadow(bool visible);

	void act(int animState, int direction);

	int getAnimState() const;
	int getDirection() const;

private:
	bool initWithData(int id, int type, int gender);
	void initUI();

	void setAnimData(int animNodeType, int data);
	void addAnimNodeIfNeed(int animNodeType);

	void updateAllAnim();
	void updateAnim(int animNodeType);
	void updateNodeZOrder(int animNodeType, cocos2d::CCNode *animNode);
	cocos2d::CCNode *getAnimNode(int animNodeType);
	CCFlashAnimation *getAnimation(int animNodeType);
	cocos2d::CCAction *getAction(int animNodeType);

	void visit();

private:
	int mGender;
	int mDirection;
	int mAnimState;

	typedef std::map<int, int> IDMap;
	IDMap mIDMap;
};

#endif //__AnimElement_h__