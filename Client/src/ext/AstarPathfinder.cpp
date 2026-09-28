#include "AstarPathfinder.h"
#include <queue>

#include "utils/TestUtils.h"

#include "userdata/netdata/GameRole.h"
#include "userdata/mapdata/PixesMap.h"
		
static const short m_moveOffsets[MAX_MoveDirections][2] = 
{
	{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}
};
static const float m_moveDistance[MAX_MoveDirections] = 
{
	1.0f, 1.4f, 1.0f, 1.4f, 1.0f, 1.4f, 1.0f, 1.4f
};

/////////AstarPathfinder/////////////////////////////////////////
AstarPathfinder::AstarPathfinder()
: m_pGhost(NULL)
{
	m_closeList.clear();
	memset(m_pVisited, false, sizeof(m_pVisited));
	clear();
}

AstarPathfinder::AstarPathfinder( GameRole* pGhost)
: m_pGhost(pGhost)
{
	m_closeList.clear();
	memset(m_pVisited, false, sizeof(m_pVisited));
	clear();
}

AstarPathfinder::~AstarPathfinder()
{
	m_closeList.clear();
	clear();
	m_pGhost = NULL;
}

bool AstarPathfinder::A_StarPathFinding( const CCPoint &targetPosition)
{
	std::priority_queue< SearchNode, std::vector<SearchNode> > openList;
	while(!openList.empty())
	{
		openList.pop();
	}
	m_closeList.clear();
	clear();
	memset(m_pVisited, false, sizeof(m_pVisited));

	SearchNode start;
	start.x = m_pGhost->mTx;
	start.y = m_pGhost->mTy;
	start.g = 0;
	start.f = start.g + getH(ccp(m_pGhost->mTx, m_pGhost->mTy), targetPosition);
	start.parent = -1;
	openList.push(start);
	while(!openList.empty())
	{
		//move out from the openlist and add to the closelist
		SearchNode curNode = openList.top();
		openList.pop();
		m_closeList.push_back(curNode);

		int id = m_closeList.size() - 1;
		if(targetPosition.equals(ccp(curNode.x, curNode.y)))
		{
			printPath(id);
			return true;
		}

		//find its children nodes
		for(int i = 0; i < MAX_MoveDirections; i++)
		{
			int x = curNode.x + m_moveOffsets[i][0];
			int y = curNode.y + m_moveOffsets[i][1];
			if(m_pGhost->isBlocked(x, y) || m_pVisited[x][y])
			{
				continue;
			}
		
			m_pVisited[x][y] = true;
			SearchNode childNode;
			childNode.x = x;
			childNode.y = y;
			childNode.dir = i;
		
			childNode.g = curNode.g + 1;
			childNode.f = curNode.g + getH(ccp(x, y), targetPosition);
			childNode.parent = id;
			openList.push(childNode);
		}
	}
	return false;
}

float AstarPathfinder::getH( const CCPoint &tempPos, const CCPoint &targetPosition )
{
	return ccpDistance(tempPos, targetPosition);
}

void AstarPathfinder::printPath( int lastId )
{
	while(!m_shortestPath.empty())
	{
		m_shortestPath.pop();
	}

	while(lastId != 0)
	{
		m_shortestPath.push(m_closeList[lastId].dir);
		lastId = m_closeList[lastId].parent;
	}
	m_closeList.clear();
}

short AstarPathfinder::getNextStep()
{
	if(hasNextStep())
	{
		short nextPos = m_shortestPath.top();
		m_shortestPath.pop();
		return nextPos;
	}
	else
	{
		CCLog("No next step!");
		return 0;
	}
}

bool AstarPathfinder::hasNextStep()
{
	return !m_shortestPath.empty();
}

short AstarPathfinder::watchNextStep()
{
	if(hasNextStep())
	{
		short nextPos = m_shortestPath.top();
		return nextPos;
	}
	else
	{
		CCLog("No next step!");
		return 0;
	}
}

void AstarPathfinder::clear()
{
	while(!m_shortestPath.empty())
	{
		m_shortestPath.pop();
	}
}

int AstarPathfinder::getLeftStepNum()
{
	return m_shortestPath.size();
}