#include "SlideTable.h"
#include "ext/CCMenuEx.h"
#include "ext/TouchCover.h"
#include "userdata/SystemData.h"


SlideTable* SlideTable::create( int beginx, int beginy, int width, int height, int row, int collomn, int spanW, int spanH )
{
	SlideTable* pSlideTable = new SlideTable;
	if(pSlideTable && pSlideTable->init(beginx,beginy,width,height,row,collomn,spanW,spanH))
	{
		pSlideTable->autorelease();
		return pSlideTable;
	}
	if(pSlideTable)
	{
		delete pSlideTable;
	}
	return NULL;
}

bool SlideTable::init( int beginx, int beginy, int width, int height, int row, int collomn, int spanW, int spanH )
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_nViewRight = width;
	m_nViewTop = height;
	m_nViewLeft = 5;
	m_nViewBottom = 5;
	m_nLineSize = collomn;
	m_nPageSize = row*collomn;
	m_nSpanW = spanW;
	m_nSpanH = spanH;
	m_beginPos = ccp(beginx,beginy);


	//add the view cover using clipping node
	CCDrawNode* pStencil = CCDrawNode::create();
	static CCPoint rectangle[4];
	rectangle[0] = ccp(m_nViewLeft,m_nViewBottom);
	rectangle[1] = ccp(m_nViewLeft,m_nViewTop);
	rectangle[2] = ccp(m_nViewRight,m_nViewTop);
	rectangle[3] = ccp(m_nViewRight,m_nViewBottom);
	static ccColor4F green = {0,1,0,1};
	pStencil->drawPolygon(rectangle,4,green,0,green);

	CCClippingNode* clipper = CCClippingNode::create(pStencil);
	clipper->setPosition(CCPointZero);
	addChild(clipper);

	m_pMovingNode = CCNode::create();
	m_pMovingNode->setPosition(CCPointZero);
	clipper->addChild(m_pMovingNode);

	//create the menu and node container, and add them to the movable node
	m_pMenu = CCMenuEx::create();
	m_pMenu->setPosition(CCPointZero);
	m_pMovingNode->addChild(m_pMenu);

	m_pNodeContainer = CCNode::create();
	m_pNodeContainer->setPosition(CCPointZero);
	m_pMovingNode->addChild(m_pNodeContainer);

	addCover();

	return true;
}

SlideTable::SlideTable()
	: m_pMenu(NULL)
	, m_pNodeContainer(NULL)
	, m_pMovingNode(NULL)
	, m_nPageSize(0)
	, m_nLineSize(0)
	, m_nViewBottom(0)
	, m_nViewLeft(0)
	, m_nViewRight(0)
	, m_nViewTop(0)
	, m_nSpanH(0)
	, m_nSpanW(0)
	, m_nPageNum(0)
	, m_nCurPage(0)
	, m_nTotalNum(0)
	, m_isScrolling(false)
	, m_pListener(NULL)
	, m_pfnSelector(NULL)
	, m_PageFlagVisible(true)
{

}

SlideTable::~SlideTable()
{

}

bool SlideTable::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos = convertToNodeSpace(pTouch->getLocation());
	m_ScrollStartPos = pos;
	m_isScrolling = false;
	if(pos.x>=m_nViewLeft && pos.x<=m_nViewRight && pos.y>=m_nViewBottom && pos.y<=m_nViewTop )
	{
		m_prePosX = pos.x;
		m_nStartX = pos.x;
		return true;
	}
	return false;
}

void SlideTable::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos = convertToNodeSpace(pTouch->getLocation());
	if (abs(pos.x-m_ScrollStartPos.x)>EXACT_X||abs(pos.y-m_ScrollStartPos.y)>EXACT_Y)
	{
		m_isScrolling = true;
	}
	if(pos.x>=m_nViewLeft && pos.x<=m_nViewRight && pos.y>=m_nViewBottom && pos.y<=m_nViewTop )
	{
		float newX = m_pMovingNode->getPositionX()+pos.x-m_prePosX;
		if(newX<=20 && newX>=-(m_nPageNum-1)*(m_nSpanW*m_nLineSize)-20)
		{
			m_pMovingNode->setPositionX(newX);
			m_prePosX = pos.x;
		}
	}
}

void SlideTable::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint pos = convertToNodeSpace(pTouch->getLocation());
	m_isScrolling = false;
	float sensitive_distance = pos.x-m_nStartX;
	int curPage = m_nCurPage;
	if(sensitive_distance > 40 && m_nCurPage>0)
	{
		//slide towards right
		curPage--;	
	}
	else if(sensitive_distance < -40 && m_nCurPage<m_nPageNum-1)
	{
		//slide towards left
		curPage++;	
	}
	
	setCurPage(curPage);adjustPagePosition();
}

bool SlideTable::isScrolling()
{
	return m_isScrolling;
}

void SlideTable::addElement( CCNode* pElement )
{
	if (!pElement)
	{
		return;
	}
	bool isBtn = dynamic_cast<CCMenuItem*>(pElement)!=NULL;
	if(isBtn)
	{
		m_pMenu->addChild(pElement);
	}
	else
	{
		m_pNodeContainer->addChild(pElement);
	}
	//calculate the position of the element and put it on its position
	CCPoint position = ccpAdd(m_beginPos,ccp(m_nTotalNum/m_nPageSize*m_nLineSize*m_nSpanW+m_nTotalNum%m_nPageSize%m_nLineSize*m_nSpanW,-m_nTotalNum%m_nPageSize/m_nLineSize*m_nSpanH));
	pElement->setPosition(position);
	m_nTotalNum++;
	m_nPageNum = m_nTotalNum/m_nPageSize+(m_nTotalNum%m_nPageSize!=0);
	if(m_nPageNum>m_pPageFlags.size())
	{
		CCMenuItem* pItem = SystemData::getMenuItemImageByPlist("shop.btn.curpage");
		pItem->setPosition(ccp(299+(m_nPageNum-1)*40,11));
		addChild(pItem);
		pItem->setVisible(m_PageFlagVisible);
		m_pPageFlags.push_back(pItem);
		handlePageChanged();
	}
	adjustPagePosition();
	m_pPageFlags[0]->selected();
}

void SlideTable::clear()
{
	if(m_pMenu)
	{
		m_pMenu->removeAllChildren();
	}
	if(m_pNodeContainer)
	{
		m_pNodeContainer->removeAllChildren();
	}
	m_nPageNum = 0;
	m_nTotalNum = 0;
	m_nCurPage = 0;
	m_pMovingNode->setPositionX(0);
	for(int i=0; i<m_pPageFlags.size(); i++)
	{
		m_pPageFlags[i]->removeFromParent();
	}
	m_pPageFlags.clear();
}

void SlideTable::onEnter()
{
	setTouchEnabled(true);
	CCLayer::onEnter();
}

void SlideTable::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
}

void SlideTable::addCover()
{
	CCRect inner = CCRectMake(m_nViewLeft,m_nViewBottom,m_nViewRight-m_nViewLeft,m_nViewTop-m_nViewBottom);
	CCPoint origin = convertToNodeSpace(CCPointZero);
	CCRect outer = CCRectMake(origin.x,origin.y,SystemData::size_x,m_nViewTop-m_nViewBottom);
	TouchCover* pCover = TouchCover::create(inner,outer);
	pCover->setAnchorPoint(CCPointZero);
	pCover->setPosition(CCPointZero);
	addChild(pCover);
}

int SlideTable::getCurPage()
{
	return m_nCurPage;
}

void SlideTable::updatePageFlag(int curPage)
{
	if(curPage != m_nCurPage)
	{
		if(m_nCurPage>=0 && m_nCurPage<m_nPageNum)
		{
			m_pPageFlags[m_nCurPage]->unselected();
		}
		m_nCurPage = curPage;
		if(m_nCurPage>=0 && m_nCurPage<m_nPageNum)
		{
			m_pPageFlags[m_nCurPage]->selected();
		}
		handlePageChanged();
	}
}

void SlideTable::adjustPagePosition()
{
	int centerX = (m_nViewRight-m_nViewLeft)/2;
	int beginX = centerX-m_nPageNum/2*40+(m_nPageNum%2==0?20:0);
	for (unsigned int i=0; i<m_pPageFlags.size(); i++)
	{
		m_pPageFlags[i]->setPositionX(beginX+40*i);
	}
}

void SlideTable::setPageFlagVisible(bool pVisibility)
{
	if (m_PageFlagVisible==pVisibility)
		return;
	m_PageFlagVisible = pVisibility;
	for (std::vector<CCMenuItem*>::iterator iter=m_pPageFlags.begin();iter!=m_pPageFlags.end();iter++)  
	{  
		CCMenuItem* item = *iter;
		item->setVisible(pVisibility);
	} 
}
void SlideTable::setPageChangeTarget(CCObject *rec, SEL_MenuHandler selector)
{
	m_pListener = rec;
	m_pfnSelector = selector;
}
int SlideTable::getTotalPage()
{
	return m_pPageFlags.size();
}
void SlideTable::handlePageChanged()
{
	if (m_pListener && m_pfnSelector)
	{
		(m_pListener->*m_pfnSelector)(this);
	}
}
void SlideTable::setCurPage(int pPage)
{
	if (pPage<0||pPage>=getTotalPage())
	{
		return;
	}
	updatePageFlag(pPage);
	m_pMovingNode->stopAllActions();
	m_pMovingNode->runAction(CCMoveTo::create(0.3,ccp(-pPage*m_nSpanW*m_nLineSize,m_pMovingNode->getPositionY())));
}