#include "WorldData.h"
#include "ModuleData.h"
#include "WorldModule.h"
#include "ActivityData.h"


void WorldData::setWorldDataString( int wid, std::string datas, int version )
{
	ActivityData::setWorldStringProp(wid, 0, datas, version);
}

void WorldData::setWorldDataNormal( int wid, int datax,int datay,int dataz, int version )
{
	ActivityData::setWorldIntProp(wid, 0, datax, version);
	ActivityData::setWorldIntProp(wid, 1, datay, version);
	ActivityData::setWorldIntProp(wid, 2, dataz, version);
}

std::string WorldData::getWorldDataS( int wid )
{
	return ActivityData::getWorldStringProp(wid, 0);
}

int WorldData::getWorldDataX( int wid )
{
	return ActivityData::getWorldIntProp(wid, 0);
}

int WorldData::getWorldDataY( int wid )
{
	return ActivityData::getWorldIntProp(wid, 1);
}

int WorldData::getWorldDataZ( int wid )
{
	return ActivityData::getWorldIntProp(wid, 2);
}

int WorldData::getWorldDataVersion( int wid )
{
	return ActivityData::getWorldIntPropVersion(wid);
}

int WorldData::getWorldDataSVersion( int wid )
{
	return ActivityData::getWorldStringPropVersion(wid);
}

void WorldData::clearWorldData()
{
	ModuleData::clearModule(CPModuleName::WORLD);
}

