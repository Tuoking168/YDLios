#include "FileUtils.h"
#include "CCCommon.h"

#include "res/Path.h"

#include "logic/platform/IPlatform.h"

using namespace cocos2d;

#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#endif


bool FileUtils::delFilesByFolder( const std::string &fullPath )
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	DIR *dir = opendir(fullPath.c_str());
	if (!dir)
	{
		CCLog(">Info: FileUtils::delFilesByFolder, dir = NULL, fullPath = %s", fullPath.c_str());
		return false;
	}

	struct dirent *ent = NULL;
	while ((ent = readdir(dir)) != NULL)
	{
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
		{
			continue;
		}

		const int errcode = remove((fullPath + ent->d_name).c_str());
		if (errcode != 0)
		{
			CCLog(">Error: FileUtils::delFilesByFolder: %d, %d, %s, %s", errcode, errno, (fullPath + ent->d_name).c_str(),"");
		}
	}

	closedir(dir);
	return true;
#else
	CCLog(">Error: FileUtils::delFilesByFolder, not implement!");
	return false;
#endif
}

void FileUtils::delWritePathFiles()
{
	std::string writePath;
	PathW::convert(writePath);

	const int FOLDER_COUNT = 3;
	const std::string folders[FOLDER_COUNT] = {"data/", "script/", "layout/"};

	for (int i = 0; i < FOLDER_COUNT; i++)
	{
		delFilesByFolder(writePath + folders[i]);
	}

	//
	writePath = CPPlatformMnger.getStringData(CPPlatformData::EXT_WRITE_PATH)
		+ CPPlatformMnger.getStringData(CPPlatformData::PACKAGE_NAME) + "/";
	delFilesByFolder(writePath);
}
