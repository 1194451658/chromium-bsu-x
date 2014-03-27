
#ifndef __AMMO_H__
#define __AMMO_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "GameObject.h"

USING_NS_CC;

class Ammo : public GameObject
{
public:
	static Ammo* create(CCNode* graphics, CCPoint& velocity, int physicsGroup);

	virtual CCNode* initGraphics();
	virtual b2Body* initPhysics();
	virtual void update(float dt) ;

protected:
	bool init(CCNode* graphics, CCPoint& velocity, int physicsGroup);

private:
	CCPoint velocity;
	int physicsGroup;
};

#endif
