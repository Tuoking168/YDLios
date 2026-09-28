#include "IGhostVisitor.h"
#include "GameRole.h"
#include "cocos2d.h"

using namespace cocos2d;

//////////WhoGhostVisitor/////////////////////////////////////////////
WhoGhostVisitor::WhoGhostVisitor()
{

}

WhoGhostVisitor::~WhoGhostVisitor()
{

}

void WhoGhostVisitor::visit( Ghost *ghost )
{
	AliveGhost *aliveGhost = dynamic_cast<AliveGhost *>(ghost);
	if (aliveGhost)
	{
		CCLog(">>>%s, lv%d, (%d, %d), type:%d", aliveGhost->mName.c_str(), aliveGhost->mLevel, aliveGhost->mTx, aliveGhost->mTy, aliveGhost->mType);
	}
}

