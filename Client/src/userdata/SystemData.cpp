#include "SystemData.h"
#include "ModuleData.h"
#include "cocos2d.h"
#include "SceneDefinition.h"
#include "PlatformDefinition.h"
#include "UserDataModule.h"
#include "res/Path.h"
#include "res/CPAnimationManager.h"
#include <fstream>
#include <sstream>
#include "GameData.h"
#include "UserData.h"
#include "netdata/GameRole.h"
#include "ext/TextField.h"
#include "ext/ProgressBar.h"
#include "CCFileUtils.h"
#include "ext/CCMenuItemTextImage.h"
#include "curl.h"
#include "script/LuaWrapper.h"
#include "script/MainLua.h"
#include "StaticData.h"

#include "element/ElementDefinition.h"
#include "element/CPElementHelper.h"

#include "luadata/LuaData.h"
#include "luadata/MinimapLua.h"

#include "utils/MacroUtils.h"
#include "utils/FileUtils.h"

#include "logic/platform/IPlatform.h"
#include "logic/platform/Win32Platform.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#include "logic/platform/AndroidPlatform.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	#include "logic/platform/IOSPlatform.h"
#endif

#include "LayoutData.h"

using namespace cocos2d;

woe::Properties		SystemData::layout;
woe::Properties		SystemData::config;

float SystemData::size_x;
float SystemData::size_y;

static std::string s_key_ex;

const double eps = 1e-6;

const float RtoA = (float)(180.0/3.141592653);

const int PrimeCount = 7;
const int PrimeNumber[PrimeCount] = {11,13,19,3,5,7,11};

std::string SystemData::m_monsterFrameNum[ACTION_COUNT];
std::string SystemData::m_roleFrameNum[ACTION_COUNT];
std::string SystemData::m_petFrameNum[ACTION_COUNT];
std::string SystemData::m_horseFrameNum[ACTION_COUNT];


void SystemData::initializeBasic()
{
	static bool inited = false;
	if (!inited)
	{
		inited = true;

		// add write path as the first search path
		IOSCode(
			string path_read;
			PathR::convert(path_read);
			if (!path_read.empty())
			{
				path_read = path_read.substr(0, path_read.size() - 1);
				Lua::instance()->addSearchPath(path_read.c_str());
				CCLog("sucess to add read path: %s", path_read.c_str());
			}
			else
			{
				CCLog("no need to add read path!");
			}
		);
		string path_write;
		PathW::convert(path_write);
		if (!path_write.empty())
		{
			path_write = path_write.substr(0, path_write.size() - 1);
			CCFileUtils* fileUtils = cocos2d::CCFileUtils::sharedFileUtils();
			std::vector<std::string> newPaths;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			newPaths.push_back(path_write + "/../..");
#endif
			newPaths.push_back(path_write);
			fileUtils->setSearchPaths(newPaths);
			Lua::instance()->addSearchPath(path_write.c_str());
			CCLog("success to add write path: %s", path_write.c_str());
		}
		else
		{
			CCLog("no need to add write path!");
		}

		//
		MainLua::libaray();
		Lua::instance()->call("require 'script/main'");
		Lua::instance()->call("main_initialize()");

		MiniMapLua::Register();

		std::string configfile = "gameconf";
		if (!config.init(configfile))
		{
			CCLog("Failed to initialize configuration data!");
			return;
		}

		//
		UserData::loadData();
		UserData::initSetting();
		checkSVNVersion();

		// platform
		Win32Code(PlatformManager::instance().setPlatform(new Win32Platform));
		AndroidCode(PlatformManager::instance().setPlatform(new AndroidPlatform));
		IOSCode(PlatformManager::instance().setPlatform(new IOSPlatform));
	}
}

/**
 * 系统数据初始化函数
 * 此函数用于初始化系统相关的配置参数，如分辨率设置、动画参数等
 * 使用静态变量确保只初始化一次
 */
void SystemData::initialize()
{
    // 使用静态局部变量确保初始化逻辑只执行一次
    static bool inited = false;
    
    // 如果已经初始化过，则直接返回
    if (!inited)
    {
        // 设置已初始化标志
        inited = true;

        // 获取目标平台信息
        TargetPlatform target = CCApplication::sharedApplication()->getTargetPlatform();
        
        // 安卓平台特定处理
        AndroidCode(
            // 安卓设备使用精确适配模式，确保全屏显示
            CCDirector::sharedDirector()->getOpenGLView()->setDesignResolutionSize(1200, 620, kResolutionExactFit);
        );
        
        // iOS平台特定代码块
        IOSCode(
            // 判断是否为iPad设备
            if (target == kTargetIpad)
            {
                // iPad设备使用显示全部模式
                // 调试注释：800 480全屏 (原注释，可能是参考分辨率)
                CCDirector::sharedDirector()->getOpenGLView()->setDesignResolutionSize(800, 480, kResolutionShowAll);
            }
            else
            {
                // 非iPad的iOS设备使用精确适配模式
                // 调试注释：800 480 (原注释，可能是参考分辨率)
                CCDirector::sharedDirector()->getOpenGLView()->setDesignResolutionSize(800, 480, kResolutionExactFit);
            }
        );
        
        // 其他平台默认设置
        #if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID && CC_TARGET_PLATFORM != CC_PLATFORM_IOS)
            CCDirector::sharedDirector()->getOpenGLView()->setDesignResolutionSize(1200, 620, kResolutionExactFit);//全屏kResolutionExactFit原始kResolutionShowAll
        #endif
        
        // 设置系统内部使用的尺寸变量             人物角色676545075
        size_x = 1200; // 对应800全屏的换算值 (根据注释推测)
        size_y = 620;  // 对应480的换算值 (根据注释推测)   
        
        // iPad设备额外处理：添加应用边框
        IOSCode(if (target == kTargetIpad) addAppFrame(););
        
        // 输出日志，显示设置的尺寸
        CCLog("size_x: %f", size_x);
        CCLog("size_y: %f", size_y);
        
        // 初始化布局数据
        std::string layout_path = "layout"; // 布局文件路径
        if (!layout.init(layout_path))
        {
            // 布局初始化失败，记录错误日志
            CCLog("Failed to initialize layout data!");
            return; // 初始化失败，直接返回
        }
        
        // 初始化动画参数
        
        // 定义所有动作类型的字符串标识数组
        const std::string strAction[ACTION_COUNT] = {
            "idle",    // 0: 待机动作
            "walk",    // 1: 行走动作
            "run",     // 2: 奔跑动作
            "null",    // 3: 空(未使用)
            "attack",  // 4: 攻击动作
            "magic",   // 5: 魔法动作
            "null",    // 6: 空(未使用)
            "die"      // 7: 死亡动作
        };
        
        std::string actionKey; // 用于构建配置键的临时变量
        
        // 初始化角色动画帧数配置
        for (int i = 0; i < ACTION_COUNT; i++)
        {
            // 构建配置键，格式：role.action.动作名
            actionKey = "role.action." + strAction[i];
            // 从配置中读取对应动作的帧数
            m_roleFrameNum[i] = getConfigString(actionKey);
        }
        
        // 初始化怪物动画帧数配置
        for (int i = 0; i < ACTION_COUNT; i++)
        {
            // 构建配置键，格式：monster.action.动作名
            actionKey = "monster.action." + strAction[i];
            // 从配置中读取对应动作的帧数
            m_monsterFrameNum[i] = getConfigString(actionKey);
        }
        
        // 初始化宠物动画帧数配置
        for (int i = 0; i < ACTION_COUNT; i++)
        {
            // 构建配置键，格式：pet.action.动作名
            actionKey = "pet.action." + strAction[i];
            // 从配置中读取对应动作的帧数
            m_petFrameNum[i] = getConfigString(actionKey);
        }
        
        // 初始化坐骑动画帧数配置
        for (int i = 0; i < ACTION_COUNT; i++)
        {
            // 构建配置键，格式：horse.action.动作名
            actionKey = "horse.action." + strAction[i];
            // 从配置中读取对应动作的帧数
            m_horseFrameNum[i] = getConfigString(actionKey);
        }
        
        // 读取攻击特效的帧数配置
        m_attackEffectNum = getConfigString("effect.action.attack");
        
        // 初始化完成，记录日志
        CCLog("SystemData::initialize() done");
    }
}

void SystemData::addAppFrame()
{
    CCEGLView* eglView = CCDirector::sharedDirector()->getOpenGLView();
    CCSize frameSize = eglView->getFrameSize();
	float scaleX = eglView->getScaleX();
    float scaleY = eglView->getScaleY();
    
    CCRect sc_rect = CCRectMake((frameSize.width - SystemData::size_x * scaleX) / 2.0f,
                                    (frameSize.height - SystemData::size_y * scaleY) / 2.0f,
                                    SystemData::size_x * scaleX,
                                    SystemData::size_y * scaleY);
	float ratioX = SystemData::size_x / frameSize.width;
	float ratioY = SystemData::size_y / frameSize.height;
    CCRect rs_rect = CCRectMake(sc_rect.getMinX() * ratioX,
                                sc_rect.getMinY() * ratioY,
                                sc_rect.size.width * ratioX,
                                sc_rect.size.height * ratioY);
    
	CCSprite* imgTop = CCSprite::create("data-a/ui/common/appframe.png");
	CCSprite* imgBottom = CCSprite::create("data-a/ui/common/appframe.png");
    if(!imgTop||!imgBottom)return;
	
	CCDirector* director = CCDirector::sharedDirector();
    director->addRenderExtra(imgTop);
    director->addRenderExtra(imgBottom);
	
    imgBottom->setFlipY(true);
	
    imgTop->setAnchorPoint(ccp(0.5,0));
    imgBottom->setAnchorPoint(ccp(0.5,1));
    
    imgTop->setPosition(ccp(rs_rect.getMidX(), rs_rect.getMaxY()-1));
    imgBottom->setPosition(ccp(rs_rect.getMidX(), rs_rect.getMinY()));
}

bool SystemData::use_cross_fade()
{
	// If the gles version is lower than GLES_VER_1_0, 
	// all the functions in CCGrabber return directly.
	return true;//(gl_version >= GLES_VER_1_1);
}

woe::Properties&	SystemData::Configuration()
{
	return config;
}

float
SystemData::getConfigFloat(const std::string& key)
{
	float vf = 0.0f;
	if (config.parse(key, vf))
		return vf;
	else
		return 0.0f;
}

short
SystemData::getConfigShort(const std::string& key)
{
	short vf = 0;
	if (config.parse(key, vf))
		return vf;
	else
		return 0;
}

int
SystemData::getConfigInt(const std::string& key)
{
	int vf = 0;
	if (config.parse(key, vf))
		return vf;
	else
		return 0;
}

std::string
SystemData::getConfigString(const std::string& key)
{
	std::string value = "error";
	if (config.parse(key, value))
		return value;
	else
		return value;
}

void SystemData::getVersion( int &gameVersion, int &dataVersion )
{
	gameVersion = getConfigInt("gameVersion");
	dataVersion = UserData::getIntData(CPUserData::DATA_VERSION);
	const int configDataVersion = getConfigInt("dataVersion");
	if (dataVersion < configDataVersion)
	{
		dataVersion = configDataVersion;
		setDataVersion(dataVersion);
	}
}

std::string SystemData::getVersion()
{
	int gameVersion = 0, dataVersion = 0;
	getVersion(gameVersion, dataVersion);
	const int svnVersion = getConfigInt("svnVersion");
	return "v" + intToString(gameVersion) + "." + intToString(svnVersion) + "." + intToString(dataVersion);
}

void SystemData::setDataVersion( int dataVersion )
{
	UserData::setIntData(CPUserData::DATA_VERSION, dataVersion);
	UserData::saveData();
}

int SystemData::getSVNVersion()
{
	return getConfigInt("svnVersion");
}

void SystemData::checkSVNVersion()
{
	const int svnVersion = getSVNVersion();
	const int mySvnVersion = UserData::getIntData(CPUserData::SVN_VERSION);
	if (mySvnVersion != svnVersion)
	{
		FileUtils::delWritePathFiles();
		StaticData::reloadLuaFiles();
		UserData::setIntData(CPUserData::SVN_VERSION, svnVersion);
		UserData::saveData();
	}
}

void		SystemData::setNodeBase(const std::string& key, CCNode* node)
{
	setNodeBase(key, node, CCSize(size_x, size_y));
}

void		SystemData::setNodeBase(const std::string& key, CCNode* node, CCSize rt)
{
	
	s_key_ex = key + ".invisible";
	if (layout.parse(s_key_ex))
	{
		node->setVisible(false);
	}

	CCPoint ptAnchor(0.5f, 0.5f);
	s_key_ex = key + ".anchor.x";
	layout.parse(s_key_ex, ptAnchor.x);
	s_key_ex = key + ".anchor.y";
	layout.parse(s_key_ex, ptAnchor.y);
	node->setAnchorPoint(ptAnchor);

	CCPoint pt(0, 0);
	s_key_ex = key + ".x";
	layout.parse(s_key_ex, pt.x);
	s_key_ex = key + ".y";
	layout.parse(s_key_ex, pt.y);

	if (pt.x>-1.0f &&pt.x<=1.0f)
	{
		pt.x *= rt.width;
	}

	if (pt.y>-1.0f &&pt.y<=1.0f)
	{
		pt.y *= rt.height;
	}

	node->setPosition(pt);

	bool flip = false;
	s_key_ex = key+".flipx";	
	layout.parse(s_key_ex,flip);
	if(flip)
	{
		node->setRotation(180);
	}
	flip = false;
	s_key_ex = key+".flipy";	
	layout.parse(s_key_ex,flip);
	if(flip)
	{
		node->setRotation(180);
	}
}

CCPoint		SystemData::getLayoutPoint(const std::string& key)
{
	std::string key_ex;
	CCPoint pt(0, 0);
	key_ex = key + ".x";
	layout.parse(key_ex, pt.x);
	key_ex = key + ".y";
	layout.parse(key_ex, pt.y);

	if (pt.x>=-1.0f &&pt.x<=1.0f)
	{
		pt.x *= size_x;
	}

	if (pt.y>=-1.0f &&pt.y<=1.0f)
	{
		pt.y *= size_y;
	}
	return pt;
}

CCRect		SystemData::getLayoutRect(const std::string& key)
{
	std::string key_ex;
	float left = 0, right = 0,
		top = 0, bottom = 0;

	key_ex = key + ".left";
	if (layout.parse(key_ex, left))
	{
		key_ex = key + ".bottom";
		layout.parse(key_ex, bottom);

		key_ex = key + ".right";
		layout.parse(key_ex, right);

		key_ex = key + ".top";
		layout.parse(key_ex, top);

		return CCRectMake(left, bottom, right-left, top-bottom);
	}
	else
	{
		key_ex = key + ".x";
		layout.parse(key_ex, left);

		key_ex = key + ".y";
		layout.parse(key_ex, bottom);

		key_ex = key + ".w";
		layout.parse(key_ex, right);

		key_ex = key + ".h";
		layout.parse(key_ex, top);

		return CCRectMake(left, bottom, right, top);
	}
}

CCSprite*	SystemData::getSprite(const std::string& key)
{
	CCSprite* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		sprite = CCSprite::create(file.c_str());
		if (sprite)
		{
			setNodeBase(key, sprite);
		}
	}
	
	if (sprite==NULL)
	{
		CCLog("Failed to load sprite : %s", key.c_str());
        sprite = CCSprite::create(LayoutData::defaultTexture());
	}

	return sprite;
}

CCSprite* SystemData::getSpriteByPlist(const std::string& key)
{
	CCSprite* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		sprite = CCSprite::createWithSpriteFrameName(file.c_str());
		if (sprite)
		{
			setNodeBase(key, sprite);
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load sprite : %s", key.c_str());
        sprite = CCSprite::create(LayoutData::defaultTexture());
	}

	return sprite;
}

CCProgressTimer* SystemData::progressWithFile(const std::string& key)
{
	CCProgressTimer* sprite = NULL;
	std::string filename;
	if (layout.parse(key, filename))
	{
		sprite = CCProgressTimer::create(CCSprite::create(filename.c_str()));
		if (sprite)
		{
			setNodeBase(key, sprite);
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load progressTimer : %s", key.c_str());
        return CCProgressTimer::create(CCSprite::create(LayoutData::defaultTexture()));
	}
	return sprite;
}

CCMenuItemImage*	SystemData::getMenuItemImage(const std::string& key)
{
	return getMenuItemImage(key, CCSize(size_x, size_y));
}

CCMenuItemImage*	SystemData::getMenuItemImage(const std::string& key, CCSize size)
{
	CCMenuItemImage* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		std::string file_sel;
		std::string key_ex = key + ".sel";
		std::string file_dis;
		std::string key_ex_ex = key + ".dis";
		
		if(layout.parse(key_ex, file_sel))
		{
			if (layout.parse(key_ex_ex, file_dis))
			{
				sprite = CCMenuItemImage::create(file.c_str(), file_sel.c_str(), file_dis.c_str());
			}
			else
			{
				sprite = CCMenuItemImage::create(file.c_str(), file_sel.c_str());
			}			
		}
		else
		{
			if (layout.parse(key_ex_ex, file_dis))
			{
				sprite = CCMenuItemImage::create(file.c_str(), file.c_str(), file_dis.c_str());
			}
			else
			{
				sprite = CCMenuItemImage::create(file.c_str(), file.c_str());
			}	
		}
		
		if (sprite)
		{
			setNodeBase(key, sprite, size);
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load menu item image : %s", key.c_str());
        sprite = CCMenuItemImage::create();
	}

	return sprite;
}

CCMenuItemImage*	SystemData::getMenuItemImageByPlist(const std::string& key)
{
	return getMenuItemImageByPlist(key, CCSize(size_x, size_y));
}

CCMenuItemImage*	SystemData::getMenuItemImageByPlist(const std::string& key, CCSize size)
{
	CCMenuItemImage* sprite = NULL;
	std::string file;
	
	if (layout.parse(key, file))
	{
		std::string file_sel;
		std::string key_ex = key + ".sel";
		std::string file_dis;
		std::string key_ex_ex = key + ".dis";
		CCSpriteFrame *normalframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file.c_str());
		sprite = CCMenuItemImage::create();
		sprite->setNormalSpriteFrame(normalframe);

		if(layout.parse(key_ex, file_sel))
		{
			CCSpriteFrame *selframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file_sel.c_str());
			sprite->setSelectedSpriteFrame(selframe);
			
			if (layout.parse(key_ex_ex, file_dis))
			{
				CCSpriteFrame *disframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file_dis.c_str());
				sprite->setDisabledSpriteFrame(disframe);
			}
		}
		else
		{
			sprite->setSelectedSpriteFrame(normalframe);
			if (layout.parse(key_ex_ex, file_dis))
			{
				CCSpriteFrame *disframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file_dis.c_str());
				sprite->setDisabledSpriteFrame(disframe);
			}
		}

		if (sprite)
		{
			setNodeBase(key, sprite, size);
		}
	}

	if (sprite == NULL)
	{
		CCLog("Failed to load menu item image : %s", key.c_str());
        sprite = CCMenuItemImage::create();
	}

	return sprite;
}

CCMenuItemImage* SystemData::getMenuItemImageByPlist(const char* normailimg, const char* selimg, CCObject *rec, SEL_MenuHandler selector)
{
	CCMenuItemImage* sprite = CCMenuItemImage::create();
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(normailimg);
	if (!pFrame)
		return NULL;
	sprite->setNormalSpriteFrame(pFrame);

	pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(selimg);
	if (!pFrame)
		return NULL;
	sprite->setSelectedSpriteFrame(pFrame);
	sprite->setTarget(rec, selector);

	return sprite;
}

CCMenuItemFont*	SystemData::getMenuItemFont(const std::string& key)
{
	CCMenuItemFont* sprite = NULL;
	std::string strInit;
	if (!layout.parse(key, strInit))
	{
		strInit = "NA";
	}
	sprite = CCMenuItemFont::create(strInit.c_str());
	if (sprite)
	{
		s_key_ex = key + ".size";
		int fnt_size = 8;
		layout.parse(s_key_ex, fnt_size);
		sprite->setFontSizeObj(fnt_size);

		short r=0, g=0, b=0;
		s_key_ex = key + ".r";
		layout.parse(s_key_ex, r);
		s_key_ex = key + ".g";
		layout.parse(s_key_ex, g);
		s_key_ex = key + ".b";
		layout.parse(s_key_ex, b);

		sprite->setColor(ccc3(r, g, b));

		setNodeBase(key,sprite);
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load menu item font : %s", key.c_str());
        sprite = CCMenuItemFont::create("");
	}
	
	return sprite;
}

float SystemData::getLayoutValue( const std::string& key )
{
	float value = 0;
	if(layout.parse(key,value))
	{
		return value; 
	}
	return 0;
}

std::string SystemData::getLayoutString( const std::string& key )
{
	std::string value;
	if(layout.parse(key,value))
	{
		return value; 
	}
	return "";
}

CCLabelTTF* SystemData::getLabelTTF( const std::string& key )
{
	CCLabelTTF* pLabel = NULL;
	std::string strInit;
	if (!layout.parse(key, strInit))
	{
		strInit = "NA";
	}
	pLabel = CCLabelTTF::create(strInit.c_str(),"Consolas",20);

	s_key_ex = key + ".size";
	int fnt_size = 12;
	layout.parse(s_key_ex, fnt_size);

	s_key_ex = key + ".font";
	std::string fontName="AppleGothic";
	layout.parse(s_key_ex,fontName);

	bool hasDimention = false;
	CCSize dimentions;
	s_key_ex = key + ".width";
	if(layout.parse(s_key_ex,dimentions.width))
	{
		hasDimention = true;
	}
	s_key_ex = key + ".height";
	if(!layout.parse(s_key_ex,dimentions.height))
	{
		hasDimention = false;
	}
	
	short alignment;
	s_key_ex = key + ".alignment";
	layout.parse(s_key_ex,alignment);

	if(!hasDimention)
	{
		pLabel = CCLabelTTF::create(strInit.c_str(),fontName.c_str(),fnt_size);
	}
	else
	{ 
		pLabel = CCLabelTTF::create(strInit.c_str(),fontName.c_str(),fnt_size,dimentions,(CCTextAlignment)alignment);
	}

	if(pLabel)
	{
		short r=0, g=0, b=0;
		s_key_ex = key + ".r";
		layout.parse(s_key_ex, r);
		s_key_ex = key + ".g";
		layout.parse(s_key_ex, g);
		s_key_ex = key + ".b";
		layout.parse(s_key_ex, b);

		ccColor3B color;
		color.r = GLubyte(r);
		color.g = GLubyte(g);
		color.b = GLubyte(b);

		pLabel->setColor(color);

		setNodeBase(key,pLabel);
	}

	if(!pLabel)
	{
		CCLog("getLabelTTF error, NULL Pointer!");
        pLabel = CCLabelTTF::create();
	}

	return pLabel;
}

TextField* SystemData::getTextField( const std::string& key )
{
	TextField *textField = NULL;
	short width = 0,height = 0,alignCopy = 0,size = 0,r = 0,g = 0,b = 0,x = 0,y = 0,limit = 100;
	CCTextAlignment align = kCCTextAlignmentLeft;
	std::string font = "";
	std::string keyWidth = key + ".width", keyHeight = key + ".height",
		keyAlign = key + ".align", keyFont = key + ".font",
		keySize = key + ".size", keyRed = key + ".r",
		keyGreen = key + ".g", keyBlue = key + ".b",
		keyLimit = key + ".limit";

	layout.parse(keyAlign,alignCopy);
	if(alignCopy == 0)
	{
		align = kCCTextAlignmentLeft;
	}
	else if(alignCopy == 1)
	{
		align = kCCTextAlignmentCenter;
	}
	else if(alignCopy == 2)
	{
		align = kCCTextAlignmentRight;
	}

	if(layout.parse(keyWidth, width) && layout.parse(keyHeight, height) &&
		layout.parse(keyFont,font)   && layout.parse(keySize,size) &&
		layout.parse(keyRed,r)       && layout.parse(keyGreen,g) &&
		layout.parse(keyBlue,b)      &&	layout.parse(keyLimit,limit))
	{
		textField = new TextField(width,height,align,font.c_str(),size,ccc3(r,g,b));
		textField->setLimitFontCount(limit);

		if(textField)
		{
			setNodeBase(key, textField);
		}

		return textField;
	}
	else
	{
		CCLog("Hi guy,your <getTextField> got a big error here!");
		return NULL;
	}
}

void SystemData::releaseMemory()
{
	CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

CCSprite* SystemData::getSpriteByRect( const std::string& file, CCRect rect )
{
	if(rect.size.width && rect.size.height)
	{
		return CCSprite::create(file.c_str(), rect);
	}
	return NULL;
}

CCSprite* SystemData::getSpriteByRect( const std::string& key )
{
	std::string file;
	if(layout.parse(key, file))
	{
		CCRect rect = getLayoutRect(key);
		CCSprite *sprite = CCSprite::create(file.c_str(), rect);
		if(sprite)
		{
			setNodeBase(key, sprite);
		}
		return sprite;
	}
	return CCSprite::create(LayoutData::defaultTexture());
}

CCMenuItemSprite* SystemData::getMenuItemSpriteByRect( const std::string& key )
{
	CCMenuItemSprite* button = NULL;
	std::string file;

	if (layout.parse(key, file))
	{
		std::string key_ex = key + ".sel";

		CCRect rect	= getLayoutRect(key);
		CCRect rectSel = getLayoutRect(key_ex);
		if(rect.size.width && rect.size.height)
		{
			CCSprite *normal = getSpriteByRect(file, rect);
			if (rectSel.size.width && rect.size.height)
			{
				CCSprite *sel = getSpriteByRect(file, rectSel);
				button = CCMenuItemSprite::create(normal, sel);		
			}
			else
			{
				button = CCMenuItemSprite::create(normal, NULL);
			}
		}

		if (button)
		{
			setNodeBase(key, button);
		}
	}

	if (button == NULL)
	{
		CCLog("Failed to load menu item sprite : %s", key.c_str());
        CCSprite *normal = CCSprite::create(LayoutData::defaultTexture());
        CCSprite *sel = CCSprite::create(LayoutData::defaultTexture());
        return button = CCMenuItemSprite::create(normal, sel);
	}

	return button;
}

CCFlashAnimation* SystemData::getAnimation(const std::string& key)
{
	const std::string &file = "data-a/animation/" + key;
	CCFlashAnimation* anim = CPAnimMnger.getAnimationMultDir(file);
	return anim;
}

CCFlashAnimation* SystemData::getAnimationOneDir(const std::string& key)
{
	const std::string &file = "data-a/animation/" + key;
	CCFlashAnimation* anim = CPAnimMnger.getAnimationOneDir(file);
	return anim;
}

double SystemData::getDistance( const cocos2d::CCPoint &pa, const cocos2d::CCPoint &pb )
{
	return sqrt((pa.x-pb.x)*(pa.x-pb.x)+(pa.y-pb.y)*(pa.y-pb.y));
}

short SystemData::getAngle( CCPoint from, CCPoint to )
{
	short angle = atan((to.y-from.y)/(to.x-from.x))*RtoA;
	
	if(to.x < from.x)
	{
		angle += 180;
	}
	if(to.y <= from.y)
	{
		angle += 360;
	}
	angle %= 360;

	return angle;
}

short SystemData::getDirection( CCPoint from, CCPoint to )
{
	short rot = getAngle(from,to);
	if ( rot >= 337.5 || rot < 22.5 )
	{
		return DIR_RIGHT;
	}

	if ( rot >= 22.5 && rot < 67.5 )
	{
		return DIR_DOWN_RIGHT;
	}

	if ( rot >= 67.5 && rot < 112.5 )
	{
		return DIR_DOWN;
	}

	if ( rot >= 112.5 && rot < 157.5 )
	{
		return DIR_DOWN_LEFT;
	}

	if ( rot >= 157.5 && rot < 202.5 )
	{
		return DIR_LEFT;
	}

	if ( rot >= 202.5 && rot < 247.5 )
	{
		return DIR_UP_LEFT;
	}

	if ( rot >= 247.5 && rot < 292.5 )
	{
		return DIR_UP;
	}

	if ( rot >= 292.5 && rot < 337.5 )
	{
		return DIR_UP_RIGHT;
	}
	return DIR_UP;
}

cocos2d::CCPoint SystemData::convertToMapPosition( CCPoint& touchPos )
{
	CCPoint roleMapPos = GameData::s_user->m_pMainRole->getMapPosition();
	touchPos = ccpSub(touchPos, GameData::s_user->m_pMainRole->getSceenPosition());
	return ccp(roleMapPos.x+touchPos.x, roleMapPos.y-touchPos.y);
}

cocos2d::CCPoint SystemData::convertToAliveLayerPosition( CCPoint& touchPos )
{
	CCPoint roleLayerPos = GameData::s_user->m_pMainRole->getSpritePosition();
	touchPos = ccpSub(touchPos, GameData::s_user->m_pMainRole->getSceenPosition());
	return ccpAdd(roleLayerPos,touchPos);
}

int SystemData::stringToInt( const std::string &str )
{
	int result=0;
	sscanf(str.c_str(),"%d",&result);
	return result;
}

std::string SystemData::intToString( int k )
{
	char str[32];
	sprintf(str,"%d",k);
	return std::string(str);
}

std::string SystemData::floatToString(float k)
{
	char str[32];
	sprintf(str,"%.2f",k);
	return std::string(str);
}

std::string SystemData::intToHexString( int k )
{
	char str[32];
	sprintf(str,"%06x",k);
	return std::string(str);
}

short SystemData::getAngleCW( CCPoint from, CCPoint to )
{
	return 360-getAngle(from,to);
}

short SystemData::getAngleFromDir(short dir)
{
	if (dir == 2)
		return 0;
	else if (dir == 1)
		return 45;
	else if (dir == 0)
		return 90;
	else if (dir == 7)
		return 135;
	else if (dir == 6)
		return 180;
	else if (dir == 5)
		return 225;
	else if (dir == 4)
		return 270;
	else
		return 315;
}

ProgressBar* SystemData::getProgresBar( const std::string& key )
{
	ProgressBar* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		sprite = ProgressBar::create(file.c_str());
		if (sprite)
		{
			setNodeBase(key, sprite);
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load progressbar : %s", key.c_str());
        return ProgressBar::create(LayoutData::defaultTexture());
	}

	return sprite;
}

ProgressBar* SystemData::getProgresBarByPlist( const std::string& key )
{
	ProgressBar* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		sprite = ProgressBar::createWithSpriteFrameName(file.c_str());
		if (sprite)
		{
			setNodeBase(key, sprite);
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load progressbar : %s", key.c_str());
        return ProgressBar::create(LayoutData::defaultTexture());
	}

	return sprite;
}

float SystemData::getSystemTime()
{
	struct cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now,NULL);
	return now.tv_sec+now.tv_usec/1000000.0;
}

void SystemData::addButtonList( CCNode* target, std::string key[], int num, SEL_MenuHandler selector, int tag[]/*=NULL*/, CCNode* parent/*=NULL*/ )
{
	if(parent==NULL)
	{
		parent = target;
	}
	for(int i=0; i<num; i++)
	{
		CCMenuItemImage* pItem = getMenuItemImage(key[i]);
		if(pItem)
		{
			pItem->setTag(tag ? tag[i] : i);
			pItem->setTarget(target, selector);
			parent->addChild(pItem);
		}
		else
		{
			CCLog("SystemData::addButtonList, faild to create button..%s",key[i].c_str());
		}
	}
}

void SystemData::addSpriteList( CCNode* target, std::string key[], int num, bool visible/*=true*/, CCSprite* savelist[]/*=NULL*/ )
{
	for(int i=0; i<num; i++)
	{
		CCSprite* pItem = getSprite(key[i]);
		if(pItem)
		{
			pItem->setVisible(visible);
			target->addChild(pItem);
			if(savelist)
			{
				savelist[i] = pItem;
			}
		}
		else
		{
			CCLog("SystemData::addSpriteList, failed to create sprite %s!!",key[i].c_str());
		}
	}
}


void SystemData::addButtonListByPlist( CCNode* target, std::string key[], int num, SEL_MenuHandler selector, int tag[]/*=NULL*/, CCNode* parent/*=NULL*/ )
{
	if(parent==NULL)
	{
		parent = target;
	}
	for(int i=0; i<num; i++)
	{
		CCMenuItemImage* pItem = getMenuItemImageByPlist(key[i]);
		if(pItem)
		{
			pItem->setTag(tag ? tag[i] : i);
			pItem->setTarget(target, selector);
			parent->addChild(pItem);
		}
		else
		{
			CCLog("SystemData::addButtonListByPlist, faild to create button..%s",key[i].c_str());
		}
	}
}

void SystemData::addSpriteListByPlist( CCNode* target, std::string key[], int num, bool visible/*=true*/, CCSprite* savelist[]/*=NULL*/ )
{
	for(int i=0; i<num; i++)
	{
		CCSprite* pItem = getSpriteByPlist(key[i]);
		if(pItem)
		{
			pItem->setVisible(visible);
			target->addChild(pItem);
			if(savelist)
			{
				savelist[i] = pItem;
			}
		}
		else
		{
			CCLog("SystemData::addSpriteListByPlist, failed to create sprite %s!!",key[i].c_str());
		}
	}
}

cocos2d::CCSize SystemData::getLayoutSize( const std::string& key )
{
	std::string key_ex;
	CCSize sz = CCSizeMake(0, 0);
	key_ex = key + ".w";
	layout.parse(key_ex, sz.width);
	key_ex = key + ".h";
	layout.parse(key_ex, sz.height);
	return sz;
}

void SystemData::scaleSize( CCNode* target,float factorX,float factorY )
{
	if(target)
	{
		target->setContentSize(CCSizeMake(target->getContentSize().width*factorX,target->getContentSize().height*factorY));
		target->setScaleX(factorX);
		target->setScaleY(factorY);
	}
}

void SystemData::scaleSize( CCNode* target,float factor )
{
	if(target)
	{
		target->setContentSize(CCSizeMake(target->getContentSize().width*factor,target->getContentSize().height*factor));
		target->setScale(factor);
	}
}

CCScale9Sprite* SystemData::getScale9SpriteByPlist( const std::string& key )
{
	const std::string &keyW = key+".w";
	const std::string &keyH = key+".h";
	const float width = getLayoutValue(keyW);
	const float height = getLayoutValue(keyH);
	return getScale9SpriteByPlist(key, width, height);
}

CCScale9Sprite*	SystemData::getScale9SpriteByPlist(const std::string& key, int width, int height)
{
	CCScale9Sprite* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		sprite = CCScale9Sprite::createWithSpriteFrameName(file.c_str());
		if (sprite)
		{
			sprite->setContentSize(CCSizeMake(width, height));
			setNodeBase(key, sprite);
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load sprite : %s", key.c_str());
        sprite = CCScale9Sprite::create(LayoutData::defaultTexture());
	}

	return sprite;
}

CCScale9Sprite* SystemData::getScale9Sprite( const std::string& key , int width, int height)
{
	CCScale9Sprite* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		sprite = CCScale9Sprite::create(file.c_str());
		if (sprite)
		{
			sprite->setContentSize(CCSizeMake(width, height));
			setNodeBase(key, sprite);
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load sprite : %s", key.c_str());
        sprite = CCScale9Sprite::create(LayoutData::defaultTexture());
	}

	return sprite;
}

CCScale9Sprite* SystemData::getScale9Sprite( const std::string& key )
{
	CCScale9Sprite* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		sprite = CCScale9Sprite::create(file.c_str());
		if (sprite)
		{
			std::string keyW = key+".w";
			std::string keyH = key+".h";
			float width = getLayoutValue(keyW);
			float height = getLayoutValue(keyH);
			sprite->setContentSize(CCSizeMake(width, height));
			setNodeBase(key, sprite);
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load sprite : %s", key.c_str());
        sprite = CCScale9Sprite::create(LayoutData::defaultTexture());
	}

	return sprite;
}

CCMenuItemTextImage* SystemData::getMenuItemTextImage( const std::string& key,  const char* text, const char* fontName, float fontSize, ccColor3B normalColor )
{
	CCMenuItemTextImage* sprite = NULL;
	std::string file;

	if (layout.parse(key, file))
	{
		std::string file_sel;
		std::string key_ex = key + ".sel";
		std::string file_dis;
		std::string key_ex_ex = key + ".dis";
		CCSpriteFrame *normalframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file.c_str());
		sprite = CCMenuItemTextImage::create();
		sprite->setNormalSpriteFrame(normalframe);

		if(layout.parse(key_ex, file_sel))
		{
			CCSpriteFrame *selframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file_sel.c_str());
			sprite->setSelectedSpriteFrame(selframe);

			if (layout.parse(key_ex_ex, file_dis))
			{
				CCSpriteFrame *disframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file_dis.c_str());
				sprite->setDisabledSpriteFrame(disframe);
			}
		}
		else
		{
			sprite->setSelectedSpriteFrame(normalframe);
			if (layout.parse(key_ex_ex, file_dis))
			{
				CCSpriteFrame *disframe = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(file_dis.c_str());
				sprite->setDisabledSpriteFrame(disframe);
			}
		}

		if (sprite)
		{
			setNodeBase(key, sprite);
		}
	}

	if (sprite == NULL)
	{
		CCLog("Failed to load menu item image : %s", key.c_str());
        sprite = CCMenuItemTextImage::create();
	}

	sprite->addText(text,fontName,fontSize,normalColor);

	return sprite;
}

short SystemData::getGesture( CCPoint& begin, CCPoint& end, int gestureLen/*=GestureLen*/ )
{
	short gesture = GESTURE_NONE;
	if (fabs(end.x-begin.x)>fabs(end.y-begin.y))//horizontal
	{
		if(end.x-begin.x > GestureLen)
		{
			gesture = GESTURE_HORIZONTAL_RIGHT;
		}
		else if(begin.x-end.x> GestureLen)
		{
			gesture = GESTURE_HORIZONTAL_LEFT;
		}
	}
	else//vertical
	{
		if(end.y-begin.y > GestureLen)
		{
			gesture = GESTURE_VERTICAL_UP;
		}
		else if(begin.y-end.y > GestureLen)
		{
			gesture = GESTURE_VERTICAL_DOWN;
		}
	}
	return gesture;
}

CCMenuItemTextImage* SystemData::getStandardButton( const std::string& key )
{
	CCMenuItemTextImage* pItem = SystemData::getMenuItemTextImage("ui.common.btn.standardbtn",
		SystemData::getLayoutString(key).c_str(),"隶书",20,ccWHITE);
	pItem->setPosition(SystemData::getLayoutPoint(key));
	return pItem;
}

CCMenuItemTextImage* SystemData::getSmallButton( const std::string& key )
{
	CCMenuItemTextImage* pItem = SystemData::getMenuItemTextImage("ui.common.btn.smallbtn",
		SystemData::getLayoutString(key).c_str(),"隶书",20,ccWHITE);
	pItem->setPosition(SystemData::getLayoutPoint(key));
	return pItem;
}

CCMenuItemTextImage* SystemData::getSmallTopChoice( const std::string& key )
{
	CCMenuItemTextImage* pItem = SystemData::getMenuItemTextImage("ui.common.btn.smallchoice",
		SystemData::getLayoutString(key).c_str(),"隶书",20,ccWHITE);
	pItem->setPosition(SystemData::getLayoutPoint(key));
	return pItem;
}

CCMenuItemTextImage* SystemData::getBigTopChoice( const std::string& key )
{
	CCMenuItemTextImage* pItem = SystemData::getMenuItemTextImage("ui.common.btn.bigchoice",
		SystemData::getLayoutString(key).c_str(),"隶书",20,ccWHITE);
	pItem->setPosition(SystemData::getLayoutPoint(key));
	return pItem;
}

CCSprite* SystemData::getSmallTopChoiceLabel( const std::string& key )
{
	CCSprite* pSprite = SystemData::getSpriteByPlist("ui.common.btn.smallchoice.sel");
    if (!pSprite)
    {
        return CCSprite::create(LayoutData::defaultTexture());
    }
	CCLabelTTF* pLabel = CCLabelTTF::create(SystemData::getLayoutString(key).c_str(),"隶书",20);
	pSprite->setPosition(SystemData::getLayoutPoint(key));
	pLabel->setPosition(ccp(pSprite->getContentSize().width/2,pSprite->getContentSize().height/2));
	pSprite->addChild(pLabel);
	return pSprite;
}

CCSprite* SystemData::getBigTopChoiceLabel( const std::string& key )
{
	CCSprite* pSprite = SystemData::getSpriteByPlist("ui.common.btn.bigchoice.sel");
    if (!pSprite)
    {
        return CCSprite::create(LayoutData::defaultTexture());
    }
	CCLabelTTF* pLabel = CCLabelTTF::create(SystemData::getLayoutString(key).c_str(),"隶书",20);
	pLabel->setPosition(ccp(pSprite->getContentSize().width/2,pSprite->getContentSize().height/2));
	pSprite->addChild(pLabel);
	pSprite->setPosition(SystemData::getLayoutPoint(key));
	return pSprite;
}

void SystemData::encode( std::string& plaintext )
{
	int n = plaintext.size();
	for(int i=0; i<n; i++)
	{
		char c = plaintext[i];
		int j = i*i%PrimeNumber[i%PrimeCount]%n;
		plaintext[i] = plaintext[j];
		plaintext[j] = c;
	}
	for(int i=0; i<n; i++)
	{
		char c = plaintext[i];
		if(c>='0' && c<='9')
		{
			c -= 10;
		}
		else if(c>='A' && c<='Z')
		{
			c = 'a'+c-'A';
		}
		else if(c>='a' && c<='z')
		{
			c = 'A'+c-'a';
		}
		plaintext[i] = c;
	}
}

void SystemData::decode( std::string& ciphertext )
{
	int n = ciphertext.size();
	for(int i=0; i<n; i++)
	{
		char c = ciphertext[i];
		if(c>='&' && c<='/')
		{
			c += 10;
		}
		else if(c>='A' && c<='Z')
		{
			c = 'a'+c-'A';
		}
		else if(c>='a' && c<='z')
		{
			c = 'A'+c-'a';
		}
		ciphertext[i] = c;
	}
	for(int i=n-1; i>=0; i--)
	{
		char c = ciphertext[i];
		int j = i*i%PrimeNumber[i%PrimeCount]%n;
		ciphertext[i] = ciphertext[j];
		ciphertext[j] = c;
	}
}

CCSprite* SystemData::getItemSprite( int id )
{
	char file[32];
	sprintf(file,"%05d.png",id);
// 	std::string file;
// 	file = SystemData::intToString(id);
	return CCSprite::createWithSpriteFrameName(file);
}

CCMenuItemImage* SystemData::getItemMenuItemImage( int id, CCObject *rec, SEL_MenuHandler selector)
{
	char file[32];
	sprintf(file,"%05d.png",id);
	return getMenuItemImageByPlist(file,file,rec,selector);
}

void SystemData::addColorToString( std::string& source, int color )
{
	source = "<font color=\"#"+intToHexString(color)+"\">"+source+"</font>";
}

void SystemData::printMemoryLog(std::string location)
{
#ifdef _DEBUG
	HANDLE handle=GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));
	//std::ofstream fout("memory.log");
	CCLog("Memory using at location %s: %dK/ %dK + %dK/ %dK",location.c_str(),pmc.WorkingSetSize/1000 ,pmc.PeakWorkingSetSize/1000,pmc.PagefileUsage/1000,pmc.PeakPagefileUsage/1000 );
	//fout<<location<<"Memory using: "<<pmc.WorkingSetSize/1000<<"K/ "<<pmc.PeakWorkingSetSize/1000<<"K"<<std::endl;
#endif
}

void SystemData::curlRequestHttp( std::string& strCmd, CurlCallback callback )
{
	CURL *pCurl = curl_easy_init();
	curl_easy_setopt(pCurl,CURLOPT_URL,strCmd.c_str());
	curl_easy_setopt(pCurl,CURLOPT_WRITEFUNCTION,callback);
	curl_easy_perform(pCurl); 
	curl_easy_cleanup(pCurl);
}
std::string SystemData::getHorseAnimationName(int id, int avatartype, int gender)
{
	int animType = AnimType::cloth;
	switch (avatartype)
	{
	case AVATAR_TYPE_CLOTH:
		animType = AnimType::cloth;
		if (id < 0)
		{
			id = ((gender == Entity::etgd_male) ? -1 : -2);
		}
		break;
	case AVATAR_TYPE_HORSE:
		animType = AnimType::horse;
		break;
	case AVATAR_TYPE_HORSEHEAD:
		animType = AnimType::horsehead;
		break;
	}
	std::string ret = "";	
	std::string tail = "_0";	
	int animState = CPElement::State::idle;

	const std::string &head = "data-a/animation/";
	StaticData::getHorseAnimPath(animType, id, animState, ret);
	const int count = ret.size() - head.size() - tail.size();
	if (count > 0)
	{
		ret = ret.substr(head.size(), count);
	}		

	return ret;
}
std::string SystemData::getAnimationName( int id, int ghosttype, int avatartype, int gender )
{
	return getAnimationName(id, ghosttype, avatartype, gender, 0);
}
/**
 * 根据给定的参数生成动画资源路径名
 * 
 * @param id 动画资源ID，不同情况下含义不同：
 *            - 对于角色：表示服装ID
 *            - 对于宠物：表示宠物ID
 *            - 对于NPC/怪物等：表示对应类型的ID
 *            - id<0时：根据性别使用默认值(-1:男性, -2:女性)
 * @param ghosttype 实体类型，决定动画的大类别
 * @param avatartype 外观类型，决定动画的子类别
 * @param gender 性别，用于某些情况下的默认值处理
 * @param reborn 转生状态，主要用于宠物动画
 * @return std::string 动画资源的相对路径名
 */
std::string SystemData::getAnimationName( int id, int ghosttype, int avatartype, int gender, int reborn )
{


	std::string ret;
	std::string tail = "_0";	
	int animType = AnimType::cloth;
	int animState = CPElement::State::idle;
	if (avatartype == AVATAR_TYPE_CLOTH)
	{
		if (ghosttype == GHOST_TYPE_THIS || ghosttype == GHOST_TYPE_PLAYER)
		{
			animType = AnimType::cloth;
			if (id < 0)
			{
				 id = ((gender == Entity::etgd_male) ? -1 : -2);
			}
		}
		else if (ghosttype == GHOST_TYPE_PET)
		{
			StaticData::getPetAnimName(id, reborn, ret);
			if (ret.empty() ||	ret == "0")
			{
				ret = "p_001";
			}
			ret = "pet/" + ret;
		}
		else if (ghosttype == GHOST_TYPE_NPC)
		{
			animType = AnimType::npc;
			tail = "";
		}
		else if (ghosttype == GHOST_TYPE_MONSTER ||
			ghosttype == GHOST_TYPE_PLANT)
		{
			animType = AnimType::monster;
		}
		else if (ghosttype == GHOST_TYPE_SLAVE)
		{
			animType = AnimType::slave;
		}
	}
	else if (avatartype == AVATAR_TYPE_WEAPON
		|| avatartype == AVATAR_TYPE_WINGS)
	{
		animType = AnimType::weapon;
	}
	else if (avatartype == AVATAR_TYPE_HORSE)
	{
		animType = AnimType::horse;
	}
	else if (avatartype == AVATAR_TYPE_EFFECT)
	{
		animType = AnimType::effect;
		animState = CPElement::State::source;
		tail = "";
	}
	else if (avatartype == AVATAR_TYPE_YUANSHEN)//元神外观
	{
		animType = AnimType::yuanshen;
	}

	if (ret.empty())
	{
		const std::string &head = "data-a/animation/";
		StaticData::getAnimPath(animType, id, CPElement::State::idle, ret);
		const int count = ret.size() - head.size() - tail.size();
		if (count > 0)
		{
			ret = ret.substr(head.size(), count);
		}		
	}
	return ret;
}

cocos2d::ccColor3B SystemData::getLayoutColor3B( const std::string& key )
{
	cocos2d::ccColor3B c;
	c.r=getLayoutValue(key+".r");
	c.g=getLayoutValue(key+".g");
	c.b=getLayoutValue(key+".b");
	return c;
}

CCMenuItemImage* SystemData::getScale9MenuItemImage( const std::string& key )
{
	CCMenuItemImage* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		std::string file_sel;
		std::string key_ex = key + ".sel";
		
		if(layout.parse(key_ex, file_sel))
		{
			sprite = CCMenuItemImage::create();

			CCSize size = getLayoutSize(key);

			CCScale9Sprite* pNormal = CCScale9Sprite::create(file.c_str());
			if(pNormal)
			{
				pNormal->setContentSize(size);
				sprite->setNormalImage(pNormal);
			}
			CCScale9Sprite* pSelected = CCScale9Sprite::create(file_sel.c_str());
			if(pSelected)
			{
				pSelected->setContentSize(size);
				sprite->setSelectedImage(pSelected);	
			}
		}
		
		if (sprite)
		{
			setNodeBase(key, sprite, CCSizeMake(size_x,size_y));
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load menu item image : %s", key.c_str());
        sprite = CCMenuItemImage::create();
	}

	return sprite;
}

std::string SystemData::m_attackEffectNum;


CCMenuItemImage* SystemData::getScale9MenuItemImageByPlist( const std::string& key )
{
	CCMenuItemImage* sprite = NULL;
	std::string file;
	if (layout.parse(key, file))
	{
		std::string file_sel;
		std::string key_ex = key + ".sel";

		if(layout.parse(key_ex, file_sel))
		{
			sprite = CCMenuItemImage::create();

			CCSize size = getLayoutSize(key);

			//CCScale9Sprite* pNormal = CCScale9Sprite::create(file.c_str());
			CCScale9Sprite* pNormal = CCScale9Sprite::createWithSpriteFrameName(file.c_str());
			if(pNormal)
			{
				pNormal->setContentSize(size);
				sprite->setNormalImage(pNormal);
			}
			//CCScale9Sprite* pSelected = CCScale9Sprite::create(file_sel.c_str());
			CCScale9Sprite* pSelected = CCScale9Sprite::createWithSpriteFrameName(file_sel.c_str());
			if(pSelected)
			{
				pSelected->setContentSize(size);
				sprite->setSelectedImage(pSelected);	
			}
		}

		if (sprite)
		{
			setNodeBase(key, sprite, CCSizeMake(size_x,size_y));
		}
	}

	if (sprite==NULL)
	{
		CCLog("Failed to load menu item image : %s", key.c_str());
		sprite = CCMenuItemImage::create();
	}

	return sprite;
}
