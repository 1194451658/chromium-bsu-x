
#ifndef __COLD_TIME_METHOD_H__
#define __COLD_TIME_METHOD_H__

#include "cocos2d.h"
#include "gun/Gun.h"

USING_NS_CC;

class Gun;

class ColdTimeMethod : public CCObject
{
public:
	virtual bool isTimeToShot(float dt) {return false;}; //

	virtual void shotted(){};
	virtual void notShotted(){};

	bool init(){ return true;};
};

#endif