#ifndef __IGhostVisitor_h__
#define __IGhostVisitor_h__

class Ghost;
class IGhostVisitor
{
public:
	virtual ~IGhostVisitor(){}

	virtual void visit(Ghost *ghost) = 0;
};

////////WhoGhostVisitor////////////////////////////////////////////////////
class WhoGhostVisitor : public IGhostVisitor
{
public:
	WhoGhostVisitor();
	~WhoGhostVisitor();

public:
	virtual void visit(Ghost *ghost);
};
#endif //__IGhostVisitor_h__