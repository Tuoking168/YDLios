#include "GameAlive.h"


GameAlive::GameAlive()
{

}

GameAlive::~GameAlive()
{

}

bool GameAlive::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	setAnchorPoint(ccp(0, 1));
	return true;
}

void GameAlive::sortAllChildren()
{
	int i,j,length = m_pChildren->data->num;
	CCNode ** x = (CCNode**)m_pChildren->data->arr;
	CCNode *tempItem;

	// insertion sort
	for(i=1; i<length; i++)
	{
		tempItem = x[i];
		j = i-1;

		//continue moving element downwards while zOrder is smaller or when zOrder is the same but mutatedIndex is smaller
		while(j>=0 && ( tempItem->getZOrder() < x[j]->getZOrder() || ( tempItem->getZOrder()== x[j]->getZOrder() && tempItem->getOrderOfArrival() < x[j]->getOrderOfArrival() ) ) )
		{
			x[j+1] = x[j];
			j = j-1;
		}
		x[j+1] = tempItem;
	}
}