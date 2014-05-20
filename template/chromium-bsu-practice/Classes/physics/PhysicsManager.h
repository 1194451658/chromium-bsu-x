

// Copyright 2014 Wanwan Zhang

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.



#ifndef __PHYSICS_MANAGER_H__
#define __PHYSICS_MANAGER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "physics/GLES-Render.h"
#include "physics/DebugDrawBox2dLayer.h"

USING_NS_CC;

class PhysicsManager;

class PhysicsStepCallbackHandler
{
public:
	virtual ~PhysicsStepCallbackHandler(){}
	virtual void prePhysicsStep(float time, PhysicsManager* manager) { CCLOG("PhysicsStepCallbackHandler::preStep called ! Reimplement it !");};
	virtual void postPhysicsStep(float time, PhysicsManager* manager) { CCLOG("PhysicsStepCallbackHandler::postStep called ! Reimplement it !");};
};


class PhysicsManager : public CCObject, public b2ContactListener
{

public:
	static PhysicsManager* sharedInstance();
public:
	~PhysicsManager();
	void addStepCallbackHandler(PhysicsStepCallbackHandler* handler);
	void deleteStepCallbackHandler(PhysicsStepCallbackHandler* handler);

	virtual void BeginContact(b2Contact* contact) ;
	virtual void EndContact(b2Contact* contact) {};
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {};
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {};

	b2World* getPhysicsWorld() {return world;};
	void step(float time);

	// debug draw
	void enableDebugDraw(bool enable);

	// create screen collider
	void createScreenCollider();

private:
	bool init(b2Vec2& gravity);
	PhysicsManager();

public:
	static b2Vec2 gravity;
	static float PTM_RATIO	;

	enum  { PHYSICS_GROUP_UNKNOWN = 0,
			PHYSICS_GROUP_JUSTICE = -1,
			PHYSICS_GROUP_ENEMY = -2
	};

	enum Category { AIRCRAFT			= 1,
					AMMO				= 1 << 2,
					ONSCREEN_TRIGGER	= 1 << 3,
					SCREEN				= 1 << 4
	};

private:
	b2World* world;
	CCArray* stepCallbacks;

	CCArray* stepCallbacksToAdd;
	CCArray* stepCallbacksToDelete;
	bool	stepCallbacksLocked;

	// step iteration number
	int velocityInteration;
	int positionIteration;

	// debug draw
	GLESDebugDraw* debugDraw;
	DebugDrawBox2dLayer* debugDrawLayer;
	uint32 flags;

};

#endif
