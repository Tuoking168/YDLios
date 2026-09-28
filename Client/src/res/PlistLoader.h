#ifndef __PlistLoader_h__
#define __PlistLoader_h__

#include "utils/MacroUtils.h"

class PlistLoader
{
public:
	static void loadCommon();

	static void loadWelcome();
	static void unloadWelcome();

	static void loadLogin();
	static void unloadLogin();

	static void loadLoading();
	static void unloadLoading();

	static int getMainCount();
	static void loadMain(int index);

private:
	CP_MAKE_STATIC_CLASS(PlistLoader);
};
#endif //__PlistLoader_h__