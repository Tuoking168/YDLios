#ifndef __WorldData_h__
#define __WorldData_h__

#include <string>
#include <vector>
#include <map>
#include "utils/MacroUtils.h"

class WorldData
{
public:
	static void setWorldDataString(int wid, std::string datas, int version);
	static void setWorldDataNormal(int wid, int datax,int datay,int dataz, int version);
	static std::string getWorldDataS(int wid);
	static int getWorldDataX(int wid);
	static int getWorldDataY(int wid);
	static int getWorldDataZ(int wid);
	static int getWorldDataVersion(int wid);
	static int getWorldDataSVersion(int wid);

	static void clearWorldData();

private:
	CP_MAKE_STATIC_CLASS(WorldData);

};
#endif //__WorldData_h__