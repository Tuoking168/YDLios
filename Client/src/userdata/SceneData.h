#ifndef __SceneData_h__
#define __SceneData_h__

#include <string>
#include "utils/MacroUtils.h"

class SceneData
{
public:
	static void clear();

	// prop
	static void setProp(int key, int data);
	static int getProp(int key);
	static int getProp(const std::string &keyName);

	static void setStringProp(int key, const std::string &data);
	static std::string getStringProp(int key);
	static std::string getStringProp(const std::string &keyName);

	static int getPropKey(const std::string &keyName);

	static void setHasEnterScene(bool flag);
	static bool hasEnterScene();

private:
	CP_MAKE_STATIC_CLASS(SceneData);
};
#endif //__SceneData_h__