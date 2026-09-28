#ifndef __FileUtils_h__
#define __FileUtils_h__

#include "MacroUtils.h"
#include <string>

class FileUtils
{
public:
	static bool delFilesByFolder(const std::string &fullPath);
	static void delWritePathFiles();

private:
	CP_MAKE_STATIC_CLASS(FileUtils);
};
#endif //__FileUtils_h__