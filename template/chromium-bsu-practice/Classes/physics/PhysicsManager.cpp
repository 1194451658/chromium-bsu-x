
#include "physics/PhysicsManager.h"
#include "aircraft/heroAircraft.h"

static PhysicsManager* _sharedInstance = NULL;

float PhysicsManager::PTM_RATIO	= 32;
// b2Vec2 PhysicsManager::gravity = b2Vec2(0.0, -10.0);
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

bool PhysicsManager::init(b2Vec2& gravity)
{
	velocityInteration	= 8;
	positionIteration	= 1;
	stepCallbacksLocked	= false;

	stepCallbacks 		= CCArray::create();
	stepCallbacksToAdd	= CCArray::create();
	stepCallbacksToDelete	= CCArray::create();

	world = new b2World(gravity);
	world->SetContactListener(this);

	stepCallbacks->retain();
	stepCallbacksToAdd->retain();
	stepCallbacksToDelete->retain();

	return true;
}

PhysicsManager::~PhysicsManager()
{
	CC_SAFE_RELEASE(stepCallbacks);
	CC_SAFE_RELEASE(stepCallbacksToAdd);
	CC_SAFE_RELEASE(stepCallbacksToDelete);
	CC_SAFE_DELETE(world);
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
			h->preStep(time, this);
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
		      h->postStep(time, this);
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

