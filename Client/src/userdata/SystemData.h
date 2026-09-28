#ifndef	___SYSTEM_DATA_____
#define ___SYSTEM_DATA_____

#include "cocos2d.h"
#include "ext/Properties.h"
#include "gui/CCControlExtension/CCScale9Sprite.h"
USING_NS_CC_EXT;
using namespace cocos2d;

#ifdef _DEBUG
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
#endif


class CCFlashAnimation;
class TextField;
class ProgressBar;
class CCMenuItemTextImage;

typedef size_t (*CurlCallback)(void *buffer, size_t size, size_t nmemb, void *user_p);

enum GestureType
{
	GESTURE_NONE,
	GESTURE_HORIZONTAL_LEFT,
	GESTURE_HORIZONTAL_RIGHT,
	GESTURE_VERTICAL_DOWN,
	GESTURE_VERTICAL_UP,
};

enum NotificationColor
{
	Notification_RED=0,
	Notification_GREEN,
	Notification_BLUE,

};
//
enum PlatformSever
{
	SEVER_TEST			= 1,
	SEVER_UC			= 2,
	SEVER_OFFICAL		= 3,
};

//
class SystemData
{
public:
	static	float	size_x;
	static	float	size_y;

	static	woe::Properties	layout;

	static	woe::Properties config;

	static const int FONT_STATIC_SIZE	= 12;
	const static int GestureLen = 30;
	static const int ACTION_COUNT = 8;

	static std::string m_roleFrameNum[ACTION_COUNT];
	static std::string m_monsterFrameNum[ACTION_COUNT];
	static std::string m_petFrameNum[ACTION_COUNT];
	static std::string m_horseFrameNum[ACTION_COUNT];
	static std::string m_attackEffectNum;

public:
	static void initializeBasic();
	static void initialize();
    
    static void addAppFrame();

	static bool use_cross_fade();

	static	woe::Properties&	Configuration();
	static	float		getConfigFloat(const std::string& key);
	static	short		getConfigShort(const std::string& key);
	static	int			getConfigInt(const std::string& key);
	static	std::string	getConfigString(const std::string& key);

	static void getVersion(int &gameVersion, int &dataVersion);
	static std::string getVersion();
	static void setDataVersion(int dataVersion);
	static int getSVNVersion();
	static void checkSVNVersion();

	static	void			setNodeBase(const std::string& key, CCNode* node);
	static	void			setNodeBase(const std::string& key, CCNode* node, CCSize);

	static  float			getLayoutValue(const std::string& key);
	static  std::string     getLayoutString( const std::string& key);
	static	CCPoint			getLayoutPoint(const std::string& key);
	static	CCSize			getLayoutSize(const std::string& key);
	static	CCRect			getLayoutRect(const std::string& key);
	static	ccColor3B		getLayoutColor3B(const std::string& key);
	static	CCSprite*		getSprite(const std::string& key);
	static  CCSprite*		getSpriteByPlist(const std::string& key);
	static  CCScale9Sprite*		getScale9SpriteByPlist(const std::string& key);
	static  CCScale9Sprite*		getScale9SpriteByPlist(const std::string& key, int width, int height);
	static  CCScale9Sprite*		getScale9Sprite(const std::string& key, int width, int height);
	static  CCScale9Sprite*		getScale9Sprite(const std::string& key);

	static  CCSprite*		getSpriteByRect(const std::string& key);
	static  CCSprite*		getSpriteByRect(const std::string& file, CCRect rect);

	static  CCProgressTimer* progressWithFile(const std::string& key);

	static	CCMenuItemImage*	getMenuItemImage(const std::string& key);
	static	CCMenuItemImage*	getScale9MenuItemImage(const std::string& key);
	static	CCMenuItemImage*	getScale9MenuItemImageByPlist(const std::string& key);
	static	CCMenuItemImage*	getMenuItemImage(const std::string& key, CCSize size);
	static	CCMenuItemImage*	getMenuItemImageByPlist(const std::string& key);
	static	CCMenuItemImage*	getMenuItemImageByPlist(const std::string& key, CCSize size);
	static  CCMenuItemImage*	getMenuItemImageByPlist(const char* normailimg, const char* selimg, CCObject *rec, SEL_MenuHandler selector);
	static	CCMenuItemFont*		getMenuItemFont(const std::string& key);
	static  CCMenuItemSprite*	getMenuItemSpriteByRect(const std::string& key);
	static  CCLabelTTF*			getLabelTTF(const std::string& key);
	static  TextField*			getTextField(const std::string& key);

	static ProgressBar*			getProgresBar(const std::string& key);
	static ProgressBar*			getProgresBarByPlist(const std::string& key);

	static CCMenuItemTextImage* getMenuItemTextImage(const std::string& key, const char* text, const char* fontName, float fontSize, ccColor3B normalColor);
	static CCMenuItemTextImage* getStandardButton(const std::string& key);
	static CCMenuItemTextImage* getSmallButton(const std::string& key);
	static CCMenuItemTextImage* getSmallTopChoice(const std::string& key);
	static CCMenuItemTextImage* getBigTopChoice(const std::string& key);
	static CCSprite*			getSmallTopChoiceLabel(const std::string& key);
	static CCSprite*			getBigTopChoiceLabel(const std::string& key);	

	static	void	releaseMemory();
	static	CCFlashAnimation* getAnimation(const std::string& key);
	static  CCFlashAnimation* getAnimationOneDir(const std::string& key);

	static double getDistance( const cocos2d::CCPoint &pa, const cocos2d::CCPoint &pb );

	static short	getDirection(CCPoint from, CCPoint to);
	static short	getAngle(CCPoint from, CCPoint to);
	static short    getAngleCW(CCPoint from, CCPoint to);
	static short	getAngleFromDir(short dir);
	static CCPoint	convertToMapPosition(CCPoint& touchPos);
	static CCPoint  convertToAliveLayerPosition(CCPoint& touchPos);
	static int		stringToInt(const std::string &str);
	static std::string intToString(int k);
	static std::string floatToString(float k);
	static std::string intToHexString(int k);
	static float    getSystemTime();
	static void		addButtonList(CCNode* target, std::string key[], int num, SEL_MenuHandler selector, int tag[]=NULL, CCNode* parent=NULL);
	static void		addSpriteList(CCNode* target, std::string key[], int num, bool visible=true, CCSprite* savelist[]=NULL);
	static void		addButtonListByPlist(CCNode* target, std::string key[], int num, SEL_MenuHandler selector, int tag[]=NULL, CCNode* parent=NULL);
	static void		addSpriteListByPlist(CCNode* target, std::string key[], int num, bool visible=true, CCSprite* savelist[]=NULL);

	static void     scaleSize(CCNode* target,float factorX,float factorY);
	static void     scaleSize(CCNode* target,float factor);

	static short	getGesture(CCPoint& begin, CCPoint& end, int gestureLen=GestureLen);

	static void		encode(std::string& plaintext);
	static void		decode(std::string& ciphertext);

	static CCSprite*	getItemSprite(int id);
	static CCMenuItemImage* getItemMenuItemImage(int id, CCObject *rec, SEL_MenuHandler selector);

	static void addColorToString(std::string& source, int color);

	static void printMemoryLog(std::string location);

	static void curlRequestHttp(std::string& strCmd, CurlCallback callback);

	static std::string getHorseAnimationName(int id, int avatartype, int gender);
	static std::string getAnimationName(int id, int ghosttype, int avatartype, int gender);
	static std::string getAnimationName(int id, int ghosttype, int avatartype, int gender, int reborn);
};

#endif
