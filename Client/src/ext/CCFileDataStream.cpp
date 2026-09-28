#include "CCFileDataStream.h"
#include "cocos2d.h"

USING_NS_CC;

CCFileDataStream::CCFileDataStream()
: m_pBuffer(0)
, m_uRPtr(0)
, m_uWPtr(0)
{
}

CCFileDataStream::~CCFileDataStream()
{
	CC_SAFE_DELETE_ARRAY(m_pBuffer);
}

bool CCFileDataStream::load(const char* pszFileName)
{
	CC_SAFE_DELETE_ARRAY(m_pBuffer);
//	CCLog("data file name: %s",pszFileName);
	//
	//	test whether the destination file exist or not
	//	if read from the read path don't execute the test code
	//
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(pszFileName[0] == '/')
	{
#endif
		FILE *fp = fopen(pszFileName, "rb");
		if (fp==NULL)
		{
			return false;  
		}
		fclose(fp);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	}
#endif


//	CCLog("Open file success!");

	//
	//	read file by FileUtils
	//	this will extract file from package on android
	//
	m_pBuffer = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(pszFileName, "rb", &m_uWPtr);
	m_uRPtr = 0;
	return (m_pBuffer) ? true : false;
}

bool CCFileDataStream::save(const char* pszFileName)
{
	FILE* file = fopen(pszFileName, "wb");

	if (file)
	{
		if (m_pBuffer!=NULL)
		{
			fwrite(m_pBuffer, m_uWPtr-m_uRPtr, 1, file);
		}
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}