
#ifndef __REVERSE_Z_ORDER_NODE_H__
#define __REVERSE_Z_ORDER_NODE_H__


#include "cocos2d.h"

USING_NS_CC;

class ReverseZOrderNode : public CCNode
{
public:
	CREATE_FUNC(ReverseZOrderNode);
	virtual void sortAllChildren();
};



#endif