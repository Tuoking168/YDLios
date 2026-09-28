#ifndef __MONSTER_LUA_DATA__
#define __MONSTER_LUA_DATA__
#include "cocos2d.h"
using namespace cocos2d;
class ItemLua
{
public:
	static bool getMonsterProp( int inx, const std::string& key,std::string& prop );
	static bool getMonsterProp( int inx, const std::string& key,int& prop );
	static bool getMonsterProp( int inx, const std::string& key,float& prop );
protected:
private:
};
#endif//__MONSTER_LUA_DATA__