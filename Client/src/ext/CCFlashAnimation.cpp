#include "CCFlashAnimation.h"
#include "SceneDefinition.h"

#include "res/Path.h"

#include "userdata/LayoutData.h"
#include "userdata/SystemData.h"
#include "userdata/luadata/LuaData.h"

#include "utils/TestUtils.h"

#define DIR_COUNT_ONE 1
#define DIR_COUNT_FIVE 5

namespace AnimLoadState
{
	enum
	{
		unload = 0,
		loading,
		loaded,
	};
}

static std::string getPlistFileName( const std::string &fullName )
{
	if (!fullName.empty())
	{
		return fullName + ".plist";
	}
	return "";
}

static std::string getImageFileName( const std::string &fullName )
{
	if (!fullName.empty())
	{
		return fullName + ".png";
	}
	return "";
}

static std::string getShortFileName( const std::string &fullName )
{
	if (!fullName.empty())
	{
		const std::string &temp = fullName.substr(fullName.find_last_of("/") + 1);
		return temp.substr(0, temp.find_last_of("."));
	}
	return "";
}

static bool needAsync( const std::string &fullName )
{
	const std::string &shortFileName = getShortFileName(fullName);
	if (!shortFileName.empty())
	{
		// a: carriage, b: dog, c: wing, d: fashion dress, f: female
		// g: monster, h: fashion dress weapon, m: male, npc: npc
		// p: pet, w: weapon
		std::string flag = shortFileName;
		const int k = shortFileName.find("_");
		if (k >= 0)
		{
			flag = shortFileName.substr(0, k);
		}

		if (flag == "a" ||
			flag == "b" ||
			flag == "c" ||
			flag == "d" ||
			flag == "f" ||
			flag == "g" ||
			flag == "h" ||
			flag == "m" ||
			flag == "npc" ||
			flag == "p" ||
			flag == "w")
		{
			return true;
		}
	}
	return false;
}

static void getParamAndOffset( const std::string &shortFileName, std::string &param, CCPoint &offset )
{
	if (shortFileName.size() > 1)
	{
		const int actionType = shortFileName[shortFileName.length() - 1] - '0';
		if (shortFileName[0] == 'g' ||
			shortFileName[0] == 'b') // monster, dog
		{
			param = SystemData::m_monsterFrameNum[actionType];
		}
		else if (shortFileName[0] == 'p') // pet
		{
			param = SystemData::m_petFrameNum[actionType];
		}
		else if (shortFileName[0] == 'z') // horse
		{
			param = SystemData::m_horseFrameNum[actionType];
			offset = SystemData::getLayoutPoint(shortFileName);
		}
		else if(shortFileName[0] == 'e')
		{
			if(shortFileName == "e_028")
			{
				param = SystemData::getConfigString("effect.chuantoushandian");
			}
			else if (shortFileName.find("e_162_") != shortFileName.npos)
			{
				param = SystemData::m_roleFrameNum[actionType];
			}
			else
			{
				param = SystemData::m_attackEffectNum;
				offset = ccp(0, 70);
			}
		}
		else//man, woman
		{
			param = SystemData::m_roleFrameNum[actionType];
			if(shortFileName[0] == 'f')
			{
				offset = ccp(-1, 0);
			}
		}
	}
}

////////CCFlashAnimation//////////////////////////////////////////
const float CCFlashAnimation::FRAME_TIME = 0.025f;
CCFlashAnimation::CCFlashAnimation()
	:mFirstFrame(NULL)
	,mDirCount(0)
	,mFrameCount(0)
	,mState(AnimLoadState::unload)
{

}

CCFlashAnimation::~CCFlashAnimation()
{
	for (int i = 0; i < (int)mAnims.size(); i++)
	{
		CCAnimation *anim = mAnims[i];
		if (anim)
		{
			anim->release();
		}
	}

	if (!mFileName.empty())
	{
		const std::string &plist = getPlistFileName(mFileName);
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plist.c_str());

		const std::string &png = getImageFileName(mFileName);
		CCTextureCache::sharedTextureCache()->removeTextureForKey(png.c_str());
	}
}

CCFlashAnimation* CCFlashAnimation::createFAWithFileName( const std::string &fileName )
{
	CCFlashAnimation* animate = new CCFlashAnimation();
	if (animate)
	{
		animate->initAnimationLoader(fileName, false);
		return animate;
	}

	CC_SAFE_DELETE(animate);
	animate = NULL;
	return NULL;
}

CCFlashAnimation* CCFlashAnimation::createFAWithFileNameOneDir( const std::string &fileName )
{
	CCFlashAnimation *animate = new CCFlashAnimation();
	if (animate)
	{
		animate->initAnimationLoader(fileName, true);
		return animate;
	}

	CC_SAFE_DELETE(animate);
	animate = NULL;
	return NULL;
}

void CCFlashAnimation::initAnimationLoader( const std::string &fileName, bool isOneDir )
{
	mFileName = fileName;
	const int dir = (isOneDir ? DIR_COUNT_ONE : DIR_COUNT_FIVE);
	initAnimVect(dir);
	if (needAsync(fileName))
	{
		setAnimFrames(true);
		mState = AnimLoadState::loading;
		CCTextureCache::sharedTextureCache()->addImageAsync(getImageFileName(fileName).c_str(), this, callfuncO_selector(CCFlashAnimation::onLoadFinish));
	}
	else
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(getImageFileName(fileName).c_str());
		onLoadFinish(texture);
	}
}

void CCFlashAnimation::initAnimVect( int dirCount )
{
	mDirCount = dirCount;
	for (int i = 0; i < mDirCount; i++)
	{
		CPAnimation *anim = CPAnimation::create();
		anim->setDelayPerUnit(FRAME_TIME);
		anim->retain();
		mAnims.push_back(anim);
	}
}

CCSpriteFrame* CCFlashAnimation::getSprite( int dir )
{
	dir = changeDirToSource(dir);
	CCArray* frames = mAnims[dir]->getFrames();
	if(frames && frames->count() > 0)
	{
		CCAnimationFrame* animframe = dynamic_cast<CCAnimationFrame*>(frames->objectAtIndex(0));
		if(animframe)
		{
			return animframe->getSpriteFrame();
		}
	}
	return NULL;
}

CCArray * CCFlashAnimation::getSpriteFrames( int dir )
{
	dir = changeDirToSource(dir);
	return mAnims[dir]->getFrames();
}

CCActionInterval* CCFlashAnimation::getAnimate(int dir)
{
	bool flip = false;
	if(mDirCount > 1 && dir >= DIR_DOWN_LEFT)
	{
		flip = true;
	}
	dir = changeDirToSource(dir);
	if (0 <= dir && dir < (int)mAnims.size() && (int)mAnims.size() == mDirCount)
	{
		CCAnimation* pAnimation = mAnims[dir];
		if(pAnimation)
		{
			return CCSequence::create(CCFlipX::create(flip), CCAnimate::create(pAnimation), NULL);
		}
	}
	
	return NULL;
}

CCSpriteFrame* CCFlashAnimation::getFirstFrame()
{
	return mFirstFrame;
}

void CCFlashAnimation::setSpeed( float speed )
{
	if (speed <= 0.1f)
	{
		speed = 0.1f;
	}
	const float delay = FRAME_TIME / speed;
	for (int i = 0; i< mDirCount; i++)
	{
		mAnims[i]->setDelayPerUnit(delay);
	}
}

int CCFlashAnimation::getFrameCount() const
{
	return mFrameCount;
}

void CCFlashAnimation::onLoadFinish( CCObject *texture )
{
	mState = AnimLoadState::loaded;

	const std::string &plist = getPlistFileName(mFileName);
	if (!CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist.c_str()))
	{
		CCLog(">>>Error: CCFlashAnimation::onLoadFinish, addSpriteFrames failed, plist: %s", plist.c_str());
		return;
	}

	setAnimFrames(false);
}

void CCFlashAnimation::setAnimFrames( bool isTemporary )
{
	if (mDirCount == DIR_COUNT_ONE)
	{
		setAnimFramesOneDir(isTemporary);
	}
	else
	{
		setAnimFramesFiveDir(isTemporary);
	}
}

void CCFlashAnimation::setAnimFramesOneDir( bool isTemporary )
{
	const std::string &shortFileName = getShortFileName(mFileName);
	int imgCount = 0;
	LuaData::getProp(LuaData::ANIM_FRAME_COUNT, shortFileName, imgCount);
	if (!imgCount)
	{
		CCLog(">>>Error: CCFlashAnimation::setAnimFramesOneDir, get anim imageCount failed, shortFileName: %s", shortFileName.c_str());
		return;
	}

	const bool isNPC = (shortFileName.substr(0, 3) == "npc");
	const int imageRepeat = (isNPC ? SystemData::getConfigInt("npcAnimRepeat") : 1);
	const float delay = (isNPC ? FRAME_TIME : 4 * FRAME_TIME);

	CCArray *animFrames = CCArray::create();
	mFrameCount = 0;
	char frameName[64];
	const std::string &tempFrameName = LayoutData::getString(CPModuleName::COMMON, "waitIconFrameName");
	for(int j = 1; j <= imgCount; j++)
	{
		if (isTemporary)
		{
			sprintf(frameName,"%s", tempFrameName.c_str());
		}
		else
		{
			sprintf(frameName,"%s_%02d.png", shortFileName.c_str(), j);
		}
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
		for (int i = 0; i < imageRepeat; i++)
		{
			CCAnimationFrame *animFrame = new CCAnimationFrame();
			animFrame->initWithSpriteFrame(pFrame, 1.0f, NULL);
			animFrames->addObject(animFrame);
			animFrame->release();

			mFrameCount++;
		}

		if(j == 1)
		{
			mFirstFrame = pFrame;
		}
	}
	CPAnimation *anim = mAnims[0];
	anim->setDelayPerUnit(delay);
	anim->setFrames(animFrames);
}

void CCFlashAnimation::setAnimFramesFiveDir( bool isTemporary )
{
	const std::string &shortFileName = getShortFileName(mFileName);
	std::string frameParam;
	CCPoint offset = CCPointZero;
	getParamAndOffset(shortFileName, frameParam, offset);
	const int imageCount = frameParam[0] - '0';
	int k = 1;
	char frameName[64];
	const std::string &tempFrameName = LayoutData::getString(CPModuleName::COMMON, "waitIconFrameName");
	for(int i = 0; i < mDirCount; i++)
	{
		CCArray *animFrames = CCArray::create();
		for(int j = k; j < k + imageCount; j++)
		{
			if (isTemporary)
			{
				sprintf(frameName,"%s", tempFrameName.c_str());
			}
			else
			{
				sprintf(frameName,"%s_%02d.png", shortFileName.c_str(), j);
			}
			CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
			if(pFrame)
			{
				if (!isTemporary)
				{
					pFrame->setOffset(ccpAdd(pFrame->getOffset(), offset));
				}
				const int imagedump = frameParam[j - k + 1]- '0';
				for(int p = 0; p < imagedump; p++)
				{
					CCAnimationFrame *animFrame = new CCAnimationFrame();
					animFrame->initWithSpriteFrame(pFrame, 1.0f, NULL);
					animFrames->addObject(animFrame);
					animFrame->release();
				}
			}
		}
		CPAnimation *anim = mAnims[i];
		anim->setFrames(animFrames);

		k += imageCount;
	}
	mFrameCount = 0;
	for(int i = 1; i <= imageCount; i++)
	{
		mFrameCount += frameParam[i] - '0';
	}
}

int CCFlashAnimation::changeDirToSource( int dir )
{
	if(mDirCount <= 1)
	{
		return DIR_UP;
	}

	if (dir < DIR_UP || dir >= AVATAR_DIR_COUNT)
	{
		return DIR_UP;
	}

	switch (dir)
	{
	case DIR_DOWN_LEFT:
		return DIR_DOWN_RIGHT;
	case DIR_LEFT:
		return DIR_RIGHT;
	case DIR_UP_LEFT:
		return DIR_UP_RIGHT;
	}
	return dir;
}

///////CPAnimation/////////////////////////////////////////////////////
CPAnimation::CPAnimation()
{}

CPAnimation::~CPAnimation()
{}

void CPAnimation::setFrames( CCArray* var )
{
	CCAnimation::setFrames(var);
	if (var && var->count())
	{
		m_fTotalDelayUnits = var->count();
	}
}

CPAnimation * CPAnimation::create()
{
	CPAnimation *ret = new CPAnimation;
	ret->init();
	ret->autorelease();
	return ret;
}
