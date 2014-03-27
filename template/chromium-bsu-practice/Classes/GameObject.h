
#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "physics/PhysicsManager.h"


class GameObject : public CCNode, public PhysicsStepCallbackHandler
{

public:
	~GameObject();
	void preStep(float time, PhysicsManager* manager);
	void postStep(float time, PhysicsManager* manager);
	virtual void update(float dt) {CCLOG("GameObject::update called !");} ;

protected:
	virtual CCNode* initGraphics() { return NULL; };
	virtual b2Body* initPhysics() { return NULL; };
	virtual void onEnter() ;
	virtual void onExit() ;

	bool init();

public:
	CCNode* graphics;
	b2Body* physics;

	bool deleted;
};

#endif
