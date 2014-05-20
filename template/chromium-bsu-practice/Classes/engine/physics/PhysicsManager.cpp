
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


#include "PhysicsManager.h"
#include "engine/GameObject.h"


static PhysicsManager* _sharedInstance = NULL;

float PhysicsManager::PTM_RATIO	= 32;
//b2Vec2 PhysicsManager::gravity = b2Vec2(0.0, -10.0);
b2Vec2 PhysicsManager::gravity = b2Vec2(0.0, 0.0);

PhysicsManager*  PhysicsManager::sharedInstance()
{
	if(NULL == _sharedInstance)
	{
		PhysicsManager* newInstance = new PhysicsManager();

		if(newInstance && newInstance->init(PhysicsManager::gravity))
		{
			_sharedInstance = newInstance;
		} else
		{
			CC_SAFE_DELETE(newInstance);
		}
	}

	return _sharedInstance;
}

PhysicsManager::PhysicsManager()
{
	world = NULL;
	stepCallbacks = NULL;

	stepCallbacksToAdd = NULL;
	stepCallbacksToDelete = NULL;
	stepCallbacksLocked = NULL;

	// step iteration number
	velocityInteration = 10;
	positionIteration = 10;

	// debug draw
	debugDraw = NULL;
	debugDrawLayer = NULL;

	flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
}

PhysicsManager::~PhysicsManager()
{
	CC_SAFE_RELEASE(stepCallbacks);
	CC_SAFE_RELEASE(stepCallbacksToAdd);
	CC_SAFE_RELEASE(stepCallbacksToDelete);
	CC_SAFE_DELETE(world);

	CC_SAFE_RELEASE(debugDrawLayer);
	CC_SAFE_DELETE(debugDraw);
}

bool PhysicsManager::init(b2Vec2& gravity)
{
	velocityInteration	= 8;
	positionIteration	= 1;
	stepCallbacksLocked	= false;

	stepCallbacks 		= CCArray::create();
	stepCallbacksToAdd	= CCArray::create();
	stepCallbacksToDelete	= CCArray::create();

	// create world
	// step first a time
	world = new b2World(gravity);
	world->Step(1, velocityInteration, positionIteration);

	world->SetContactListener(this);

	stepCallbacks->retain();
	stepCallbacksToAdd->retain();
	stepCallbacksToDelete->retain();

	// create debug draw
	debugDraw = new GLESDebugDraw(PTM_RATIO);
	debugDraw->SetFlags(flags);
	world->SetDebugDraw(debugDraw);

	debugDrawLayer = DebugDrawBox2dLayer::create();
	debugDrawLayer->retain();

	return true;
}

void PhysicsManager::enableDebugDraw(bool enable)
{
	if(enable)
	{
			CCDirector::sharedDirector()->setNotificationNode(debugDrawLayer);
	}
	else
	{
		// disable
		if(CCDirector::sharedDirector()->getNotificationNode() == debugDrawLayer)
		{
			CCDirector::sharedDirector()->setNotificationNode(NULL);
		}
	}
}

void addStepCallbackHandler(PhysicsStepCallbackHandler* handler);

void PhysicsManager::step(float time)
{
	stepCallbacksLocked = true;

	// check if game object should release
	CCObject* pObj = NULL;
	pObj = NULL;
	CCARRAY_FOREACH(stepCallbacks, pObj)
	{
		GameObject* go = dynamic_cast<GameObject*>(pObj);
		if(go && go->shouldReleased)
		{
			// CCLOG("should PhysicsManager::step should released !!");
			if(!stepCallbacksToDelete->containsObject(pObj))
				stepCallbacksToDelete->addObject(pObj);
		}
	}

	pObj = NULL;
	CCARRAY_FOREACH(stepCallbacksToDelete, pObj)
	{
		if(pObj)
			stepCallbacks->removeObject(pObj);
	}
	stepCallbacksToDelete->removeAllObjects();

	// pre step callback
	CCARRAY_FOREACH(stepCallbacks, pObj)
	{
		 PhysicsStepCallbackHandler* h = dynamic_cast<PhysicsStepCallbackHandler*>(pObj);
		if(h)
		{
			h->prePhysicsStep(time, this);
		}
	}

	// step
	world->Step(time, velocityInteration, positionIteration);

	// post step callback
	pObj = NULL;
	CCARRAY_FOREACH(stepCallbacks, pObj)
	{
		PhysicsStepCallbackHandler* h = dynamic_cast<PhysicsStepCallbackHandler*>(pObj);
		if(h)
		{
		      h->postPhysicsStep(time, this);
		}
	}

	stepCallbacksLocked = false;

	// add handler
	stepCallbacks->addObjectsFromArray(stepCallbacksToAdd);
	stepCallbacksToAdd->removeAllObjects();

	// remove handler
	pObj = NULL;
	CCARRAY_FOREACH(stepCallbacksToDelete, pObj)
	{
		if(pObj)
			stepCallbacks->removeObject(pObj);
	}

	stepCallbacksToDelete->removeAllObjects();
}

void PhysicsManager::addStepCallbackHandler(PhysicsStepCallbackHandler* handler)
{
	// CCObject* obj = (CCObject*)handler;
	CCObject* obj = dynamic_cast<CCObject*>(handler);

	if(NULL == obj) return ;

	if(stepCallbacksLocked)
	{
		if(!stepCallbacksToAdd->containsObject(obj))
			stepCallbacksToAdd->addObject(obj);
	}
	else
	{
		if(!stepCallbacks->containsObject(obj))
			stepCallbacks->addObject(obj);
	}
}

void PhysicsManager::deleteStepCallbackHandler(PhysicsStepCallbackHandler* handler)
{
	// CCObject* obj = (CCObject*)handler;
	CCObject* obj = dynamic_cast<CCObject*>(handler);
	if(NULL == obj) return;

	if(stepCallbacksLocked)
	{
		if(!stepCallbacksToDelete->containsObject(obj))
			stepCallbacksToDelete->addObject(obj);
	}
	else
	{
		if(!stepCallbacks->containsObject(obj))
			stepCallbacks->removeObject(obj);
	}
}

void PhysicsManager::BeginContact(b2Contact* contact)
{
	while(NULL != contact)
	{
		GameObject* ga = (GameObject*) (contact->GetFixtureA()->GetBody()->GetUserData());
		GameObject* gb = (GameObject*) (contact->GetFixtureB()->GetBody()->GetUserData());

		b2ContactListener* la = dynamic_cast<b2ContactListener*>(ga);
		b2ContactListener* lb = dynamic_cast<b2ContactListener*>(gb);

		if(la)
			la->BeginContact(contact);

		if(lb)
			lb->BeginContact(contact);

		contact = contact->GetNext();
	}
}

void PhysicsManager::createScreenCollider()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = ccp(size.width/2, size.height/2);

	b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();

	// create the physics shape from graphics content size
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.position = b2Vec2(pos.x/PhysicsManager::PTM_RATIO, pos.y/PhysicsManager::PTM_RATIO);
	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;
	shape.SetAsBox(size.width/2/PhysicsManager::PTM_RATIO,
		size.height/2/PhysicsManager::PTM_RATIO);
	body->CreateFixture(&shape, 0);

	// set fixture collide filter
	b2Filter filter;
	filter.groupIndex	= PhysicsManager::PHYSICS_GROUP_UNKNOWN;
	filter.categoryBits = PhysicsManager::SCREEN;
	filter.maskBits		= PhysicsManager::ONSCREEN_TRIGGER;

	b2Fixture* fixtureList = body->GetFixtureList();

	while(NULL != fixtureList)
	{
		fixtureList->SetFilterData(filter);
		fixtureList->SetSensor(true);
		fixtureList = fixtureList->GetNext();
	}
}

