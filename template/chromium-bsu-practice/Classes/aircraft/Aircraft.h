
#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

class Aircraft : public GameObject
{

public:
	bool init() ;
	void damage(float damage);
	void update(float dt) ;

private:
	float hp; 
	float damageToHit;
};

#endif
