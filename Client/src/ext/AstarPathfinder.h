#ifndef __ASTAR_PATHFINDER_H__
#define __ASTAR_PATHFINDER_H__

#include <stack>
#include <vector>
#include "cocos2d.h"
USING_NS_CC;

static const short	MAX_MoveDirections = 8;
struct SearchNode
{
	SearchNode()
		:x(0)
		,y(0)
		,dir(0)
		,f(0)
		,g(0)
		,parent(0)
	{}
	
	bool operator < (const SearchNode &node) const
	{
		return f > node.f;
	}

	short x,y,dir;
	float f,g;
	int parent;
};

class GameRole;
class AstarPathfinder
{
public:
	AstarPathfinder();
	AstarPathfinder(GameRole* pRole);
	~AstarPathfinder();

public:
	//calculate the shortest path with A* algorithm
	bool            A_StarPathFinding(const CCPoint &targetPosition);

	bool			hasNextStep();
	short			getNextStep();
	short			watchNextStep();
	int				getLeftStepNum();

	void			clear();

private:
	//calculate the h-value for A_star algorithm
	float           getH(const CCPoint &tempPos, const CCPoint &targetPosition);
	//print the shortest path
	void            printPath(int lastId); 

private:
	static const short	MAX_ROW = 505;
	static const short	MAX_COLLOMN = 505;
	typedef   std::stack<short> ShortStack;
	typedef   std::vector<SearchNode> SearchNodeVec;
	ShortStack      m_shortestPath;
	SearchNodeVec   m_closeList;
	GameRole*		m_pGhost;
	bool			m_pVisited[MAX_ROW][MAX_COLLOMN];
};

#endif//__ASTAR_PATHFINDER_H__
