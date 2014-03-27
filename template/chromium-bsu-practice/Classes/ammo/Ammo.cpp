
#include "Ammo.h"

bool Ammo::init(CCNode* graphics, CCPoint& velocity, int physicsGroup)
{
	this->graphics = graphics;
	this->velocity = velocity;
	this->physicsGroup = physicsGroup;

	return GameObject::init();
}

Ammo* Ammo::create(CCNode* graphics, CCPoint& velocity, int physicsGroup)
{
	Ammo* newAmmo = new Ammo();

	if(newAmmo && newAmmo->init(graphics, velocity, physicsGroup))
	{
		newAmmo->autorelease();
		return newAmmo;
	}

	CC_SAFE_DELETE(newAmmo);
	return NULL;
}

CCNode* Ammo::initGraphics()
{
	return graphics;
}

b2Body* Ammo::initPhysics()
{
	if(graphics)
	{
		CCSize size = graphics->getContentSize();
		b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();

		// create the physics shape frome graphics content size
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.bullet = true;
		bodyDef.fixedRotation = true;
		bodyDef.linearVelocity.Set(velocity.x/PhysicsManager::PTM_RATIO, velocity.y/PhysicsManager::PTM_RATIO);
		b2Body* body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(size.width/2/PhysicsManager::PTM_RATIO,
				size.height/2/PhysicsManager::PTM_RATIO);
		body->CreateFixture(&shape, 1);


		// set fixture collide filter
		b2Filter filter;
		filter.groupIndex	= physicsGroup;
		filter.categoryBits = PhysicsManager::AMMO;
		filter.maskBits		= PhysicsManager::AIRCRAFT | PhysicsManager::AMMO;

		b2Fixture* fixtureList = body->GetFixtureList();

		while(NULL != fixtureList)
		{
			fixtureList->SetFilterData(filter);
			fixtureList = fixtureList->GetNext();
		}

		return body;
	}

	return NULL;
}

void Ammo::update(float time)
{
	// CCPoint curPos = getPosition();
	// curPos.x += velocity.x * time;
	// curPos.y += velocity.y * time;
	// setPosition(curPos);
}

