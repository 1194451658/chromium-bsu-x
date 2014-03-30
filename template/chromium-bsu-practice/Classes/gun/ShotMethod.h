
#ifndef __SHOT_METHOD_H__
#define __SHOT_METHOD_H__

#include "cocos2d.h"
#include "gun/Gun.h"

USING_NS_CC;

class Gun;

class ShotMethod : public CCObject
{
public:
	virtual void shot(Gun* gun) {}; // 
	bool init(){ return true;};
};

#endif

