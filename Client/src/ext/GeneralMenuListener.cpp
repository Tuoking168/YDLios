#include "GeneralMenuListener.h"
#include "userdata/UserData.h"
#include "userdata/GameData.h"

GeneralMenuListener::GeneralMenuListener()
{

}

GeneralMenuListener::~GeneralMenuListener()
{

}

bool GeneralMenuListener::init()
{
	if(!GeneralMenu::init())
	{
		return false;
	}
	return true;
}

void GeneralMenuListener::onEnter()
{
	GeneralMenu::onEnter();
}

void GeneralMenuListener::onExit()
{
	GeneralMenu::onExit();
}
