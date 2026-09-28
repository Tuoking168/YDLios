#include "CCTabelViewEx.h"
#include "TouchCover.h"

CCTableViewEx::CCTableViewEx()
: m_pScrollBar(NULL)
, m_bShowScrollBar(false)
, m_bAdjust(false)
,m_iCurPage(0)
,m_CurPoint(CCPointZero)
,m_iSpeed(0)
,m_bAddSpeed(false)
{

}

CCTableViewEx* CCTableViewEx::create( CCTableViewDataSource* dataSource, CCSize size, CCScrollViewDirection direction, CCTableViewDelegate* tableDelegate )
{
	return create(dataSource,size,direction,tableDelegate,NULL);
}

CCTableViewEx* CCTableViewEx::create( CCTableViewDataSource* dataSource, CCSize size, CCScrollViewDirection direction, CCTableViewDelegate* tableDelegate, CCNode *container )
{
	CCTableViewEx *table = new CCTableViewEx();
	table->initWithViewSize(size,container);
	table->autorelease();
	table->setDataSource(dataSource);
	table->setDirection(direction);
	table->setDelegate(tableDelegate);
	table->_updateCellPositions();
	table->_updateContentSize();

	return table;
}

bool CCTableViewEx::initWithViewSize( CCSize size, CCNode* container /* = NULL */ )
{
	if(!CCTableView::initWithViewSize(size,container))
	{
		return false;
	}

	return true;
}

bool CCTableViewEx::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	/*CCPoint pos=touch->getLocation();
	CCRect rect=CCRectMake(this->getPositionX(),this->getPositionY(),m_tViewSize.width,m_tViewSize.height);
	if (rect.containsPoint( this->convertToNodeSpace(pos)))
	{
		return CCTableView::ccTouchBegan(touch,event);
	}*/
	/*if (CCTableView::ccTouchBegan(touch,event))
	{
		/ *CCPoint pos=touch->getLocation();
		CCRect rect=CCRectMake(this->getPositionX(),this->getPositionY(),m_tViewSize.width,m_tViewSize.height);
		if (rect.containsPoint( this->convertToNodeSpace(pos)))
		{
			return true;
		}* /
		return true;
	}*/
	return CCTableView::ccTouchBegan(touch,event);
}

void CCTableViewEx::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	const CCPoint &pt = convertTouchToNodeSpace(touch);
	if(getDirection() == kCCScrollViewDirectionVertical)
	{
		m_iSpeed = pt.y -  m_CurPoint.y;
	}
	else if(getDirection() == kCCScrollViewDirectionHorizontal)
	{
		m_iSpeed = pt.x - m_CurPoint.x;
	}
	m_CurPoint=pt;
	CCTableView::ccTouchMoved(touch,event);
}

void CCTableViewEx::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	CCTableView::ccTouchEnded(touch,event);
	if (m_bAdjust)
	{
		adjustScroll();
	}
	m_iSpeed = 0;
	m_CurPoint=CCPointZero;
	//adjustScroll();
}

void CCTableViewEx::scrollViewDidScroll( CCScrollView* view )
{
	CCTableView::scrollViewDidScroll(this);
	adjustScrollBar();
	m_pTableViewDelegate->scrollViewDidScroll(view);
}

void CCTableViewEx::setScrollBar( CCScale9Sprite* scrollbar )
{
	CCNode::addChild(scrollbar,100,-1);
	m_pScrollBar = scrollbar;
	m_bShowScrollBar = true;
	if(getDirection() == kCCScrollViewDirectionVertical)
	{
		m_pScrollBar->setAnchorPoint(ccp(1,1));
		m_pScrollBar->setPosition(ccp(getViewSize().width-5,getViewSize().height));
		adjustScrollBar();
	}
	else if(getDirection() == kCCScrollViewDirectionHorizontal)
	{
		m_pScrollBar->setPosition(CCPointZero);
	}
}

void CCTableViewEx::setScrollBarBackground( CCScale9Sprite* scrollbarbkg )
{
	CCNode::addChild(scrollbarbkg,99,-1);
	if(getDirection() == kCCScrollViewDirectionVertical)
	{
		scrollbarbkg->setAnchorPoint(ccp(1,1));
		scrollbarbkg->setPosition(ccp(getViewSize().width-5,getViewSize().height));
		scrollbarbkg->setScaleY((getViewSize().height-2)/scrollbarbkg->getContentSize().height);
	}
	else if(getDirection() == kCCScrollViewDirectionHorizontal)
	{
		scrollbarbkg->setAnchorPoint(CCPointZero);
		scrollbarbkg->setPosition(CCPointZero);
		scrollbarbkg->setScaleX((getViewSize().width-2)/scrollbarbkg->getContentSize().width);
	}
}

void CCTableViewEx::setShouldAddSpeed( bool flag )
{
	m_bAddSpeed=flag;
}

void CCTableViewEx::adjustScroll()
{
	if(getDirection() == kCCScrollViewDirectionVertical)
	{
		unscheduleAllSelectors();
		int y = getContentOffset().y;
		if(y>maxContainerOffset().y)
		{
			y = maxContainerOffset().y;
		}
		if(y<minContainerOffset().y)
		{
			y = minContainerOffset().y;
		}
		//CCLog("-------------table----view------------offset: %d",y);
		int h = m_pDataSource->cellSizeForTable(this).height;	
		int offset = 0;		
		if(h)
			offset = y%h; 
		else
			offset = 0;
		m_iCurPage =abs( (int) y / h);
		CCPoint adjustPos;
		// 调整动画时间   
		float adjustAnimDelay;  
		if(offset<-h/2)
		{
			adjustAnimDelay = (float) (h + offset) / 100/*ADJUST_ANIM_VELOCITY*/;  
			adjustPos = ccpSub(getContentOffset(),ccp(0,h+offset));
		}
		else
		{
			adjustAnimDelay = (float) abs(offset) / 100/*ADJUST_ANIM_VELOCITY*/;  
			adjustPos = ccpSub(getContentOffset(),ccp(0,offset));
		}
		if (y ==  minContainerOffset().y || y ==  maxContainerOffset().y)
		{
			adjustPos = ccp(0,y);
		}
		setContentOffsetInDuration(adjustPos,adjustAnimDelay);
	}
	else if (getDirection() == kCCScrollViewDirectionHorizontal)
	{
		unscheduleAllSelectors();       
		int x = getContentOffset().x;  
		if(x>maxContainerOffset().x)
		{
			x = maxContainerOffset().x;
		}
		if(x<minContainerOffset().x)
		{
			x = minContainerOffset().x;
		}
		int w = m_pDataSource->cellSizeForTable(this).width;	
		int offset = (int) x % w;  
		// 调整位置   
		CCPoint adjustPos = CCPointZero;  
		// 调整动画时间   
		float adjustAnimDelay;  		
		int m=50;

		int newoffset = m_iSpeed/4*w;
		if (!m_bAddSpeed)
		{
			newoffset=0;
		}
		if (offset + w/2 < 0) 
		{  
			//offset+=newoffset;
			// 计算下一页位置，时间   
			adjustPos = ccpSub(getContentOffset(), ccp(w + offset-newoffset, 0)); 
			adjustAnimDelay = (float) (w + offset) / 100/*ADJUST_ANIM_VELOCITY*/;  
		}  
		else 
		{  
			// offset+=newoffset;
			// 计算当前页位置，时间   
			adjustPos = ccpSub(getContentOffset(), ccp(offset-newoffset, 0));  
			// 这里要取绝对值，否则在第一页往左翻动时，保证adjustAnimDelay为正数   
			adjustAnimDelay = (float) abs(offset) / 100/*ADJUST_ANIM_VELOCITY*/;  
		}  
		// 调整位置   

		if (x ==  minContainerOffset().x || x ==  maxContainerOffset().x || adjustPos.x>=maxContainerOffset().x || adjustPos.x<minContainerOffset().x)
		{
			adjustPos = ccp(x,0);
		}
		m_iCurPage =abs(adjustPos.x / w) ;
		if (!m_bAddSpeed)
		{
			adjustAnimDelay=0.1f;
		}
		if ((int)(adjustPos.x) % w !=0 )
		{
			adjustPos = ccp(-m_iCurPage*w, getContentOffset().y); 
		}
		setContentOffsetInDuration(adjustPos, adjustAnimDelay); 
	}
}

bool CCTableViewEx::isNodeVisibleInView( CCNode * node )
{
	const CCSize  size   = this->getViewSize();
	const float   scale  = this->getZoomScale();

	CCPoint pos = this->convertToWorldSpace(CCPointZero);
	CCRect viewRect = CCRectMake(pos.x/scale, pos.y/scale, size.width/scale, size.height/scale); 

	CCPoint begin = node->convertToWorldSpace(CCPointZero);
	CCRect noderect = CCRectMake(begin.x,begin.y,node->getContentSize().width,node->getContentSize().height);

	return viewRect.intersectsRect(noderect);
}

void CCTableViewEx::adjustScrollBar()
{
	if(m_bShowScrollBar)
	{
		float ratio = 1;
		float scaleFactor = 1;
		if(getDirection() == kCCScrollViewDirectionVertical)
		{
			scaleFactor = getViewSize().height/m_pScrollBar->getContentSize().height;
			float invisible_length = getContentSize().height-getViewSize().height;
			if(invisible_length>0)
			{
				ratio = fabs(m_pContainer->getPositionY())/invisible_length;
				if(ratio>1)
				{
					ratio = 1;
				}
				if(m_pContainer->getPositionY() > 0)
				{
					ratio = 0;
				}
				scaleFactor = getViewSize().height*getViewSize().height/getContentSize().height/m_pScrollBar->getContentSize().height;
			}
			//m_pScrollBar->setContentSize(CCSizeMake(m_pScrollBar->getContentSize().width,m_pScrollBar->getContentSize().height*scaleFactor));
			//m_pScrollBar->setScaleY(scaleFactor);
			m_pScrollBar->setPositionY((getViewSize().height-m_pScrollBar->getContentSize().height)*ratio+m_pScrollBar->getContentSize().height);
		}
		else if(getDirection() == kCCScrollViewDirectionHorizontal)
		{
			m_pScrollBar->setPositionX(getViewSize().width*ratio);
		}
	}
}

void CCTableViewEx::showTop()
{	
	int offsetY = getViewSize().height-getContentSize().height;
	if(offsetY>0)
	{
		offsetY = 0;
	}
	setContentOffset(ccp(0,offsetY));
}

void CCTableViewEx::showBottom()
{
	setContentOffset(CCPointZero);
}

void CCTableViewEx::setIsadjust( bool flag )
{
	m_bAdjust=flag;
}

int  CCTableViewEx::getCurPage()
{
	return m_iCurPage;
}

void CCTableViewEx::setCurPage(int page)
{
	if ( page<0 )
	{
		return;
	}
	m_iCurPage=page;
	CCPoint adjustPos; 
	if(getDirection() == kCCScrollViewDirectionVertical)//纵向
	{
		int h = m_pDataSource->cellSizeForTable(this).height;
		adjustPos = ccp(getContentOffset().x ,-m_iCurPage*h ); 
	}
	else if (getDirection() == kCCScrollViewDirectionHorizontal)
	{
		int w = m_pDataSource->cellSizeForTable(this).width; 
		adjustPos = ccp(-m_iCurPage*w, getContentOffset().y); 
	}
	setContentOffsetInDuration(adjustPos,0.1f); 
}

void CCTableViewEx::setCurPageWithInit( int page )
{
	if ( page<0 )
	{
		return;
	}
	m_iCurPage=page;
	CCPoint adjustPos; 
	if(getDirection() == kCCScrollViewDirectionVertical)//纵向
	{
		int h = m_pDataSource->cellSizeForTable(this).height;
		adjustPos = ccp(getContentOffset().x ,-m_iCurPage*h ); 
	}
	else if (getDirection() == kCCScrollViewDirectionHorizontal)
	{
		int w = m_pDataSource->cellSizeForTable(this).width; 
		adjustPos = ccp(-m_iCurPage*w, getContentOffset().y); 
	}
	setContentOffsetInDuration(adjustPos,0); 
}
