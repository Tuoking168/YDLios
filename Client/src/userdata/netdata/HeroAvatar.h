#ifndef __HERO_AVATAR__
#define __HERO_AVATAR__

//#include "AliveGhost.h"
#include "userdata/netdata/AliveGhost.h"


class HeroAvatar : public AliveGhost
{
public:
	HeroAvatar();
	~HeroAvatar();
	virtual bool init();

	virtual void update(float dt);

	virtual void initName();
	virtual void refreshNameLabel(bool visible);
	virtual void setExData(int type, int data);
	virtual void setExStr(int type, const std::string &str);

	void refreshHeadName();

	virtual void runAvatarAnimation();
private:
	void initHeadName();
	void refreshRebornLabel(int &ox);
	void refreshVIPLabel(int &ox);
	void refreshGuildLabel();
	void refreshCoupleLabel();

protected:
	CCNode *mHeadNameContainer;
};



#endif //__HERO_AVATAR__