

#ifndef __PHYSICS_MANAGER_H__
#define __PHYSICS_MANAGER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class PhysicsManager;

class PhysicsStepCallbackHandler
{
public:
	virtual ~PhysicsStepCallbackHandler(){}
	virtual void preStep(float time, PhysicsManager* manager) { CCLOG("PhysicsStepCallbackHandler::preStep called ! Reimplement it !");};
	virtual void postStep(float time, PhysicsManager* manager) { CCLOG("PhysicsStepCallbackHandler::postStep called ! Reimplement it !");};
};


class PhysicsManager : public CCObject
{

public:
	static PhysicsManager* sharedInstance();
public:
	~PhysicsManager();
	void addStepCallbackHandler(PhysicsStepCallbackHandler* handler);
	void deleteStepCallbackHandler(PhysicsStepCallbackHandler* handler);

	b2World* getPhysicsWorld() {return world;};
	void step(float time);

private:
	bool init(b2Vec2& gravity);

public:
	static b2Vec2 gravity;
	static float PTM_RATIO	;

	enum Group { JUSTICE = -1, ENEMY = -2};
	enum Category { AIRCRAFT = 1,
			AMMO	= 1 << 2
	};

private:
	b2World* world;
	CCArray* stepCallbacks;

	CCArray* stepCallbacksToAdd;
	CCArray* stepCallbacksToDelete;

	bool	stepCallbacksLocked;

	int velocityInteration;
	int positionIteration;

};

#endif
