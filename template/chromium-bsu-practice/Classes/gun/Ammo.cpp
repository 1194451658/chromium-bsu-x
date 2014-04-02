
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


#include "Ammo.h"
#include "aircraft/Aircraft.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

bool Ammo::init(AmmoDef& def)
{
	graphicsFile = def.graphicsFile;
	graphics = CCSprite::create(graphicsFile);
	physicsGroup = def.physicsGroup;
	velocity = def.velocity;
	direction = def.direction.normalize();
	physicsGroup = def.physicsGroup;

	directionAffectRotation = def.directionAffectRotation;

	if(directionAffectRotation)
	{
		this->graphics->setRotation(90 - CC_RADIANS_TO_DEGREES(this->direction.getAngle()));
	}

	if(GameObject::init())
	{
		name = "Ammo";

		damage = def.damage;
		shouldExplode = false;

		return true;
	}

	return false;
}

Ammo* Ammo::create(AmmoDef& def)
{
	Ammo* newAmmo = new Ammo();

	if(newAmmo && newAmmo->init(def))
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
		bodyDef.linearVelocity.Set(direction.x * velocity/PhysicsManager::PTM_RATIO,
									direction.y * velocity/PhysicsManager::PTM_RATIO);
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
	if(shouldReleased)
		return;
	
	if(shouldExplode)
	{
		SimpleAudioEngine::sharedEngine()->playEffect("wav/exploStd.wav");
		
		shouldReleased = true;
		removeFromParent();
	}
}

void Ammo::BeginContact(b2Contact* contact)
{
	if(NULL != contact)
	{
		GameObject* ga = (GameObject*) (contact->GetFixtureA()->GetBody()->GetUserData());
		GameObject* gb = (GameObject*) (contact->GetFixtureB()->GetBody()->GetUserData());
		
		if(ga == this || gb == this)
		{
			shouldExplode = true;

			doDamageToGameObject(ga);
			doDamageToGameObject(gb);
		}
	}
}

void Ammo::doDamageToGameObject(GameObject* go)
{
	Aircraft* aircraft = dynamic_cast<Aircraft*> (go);
	if(aircraft)
		aircraft->damage(damage);
}

Ammo::~Ammo()
{
	// CCLOG("Ammo::~Ammo Called !");
}

Ammo::Ammo()
{
	// CCLOG("Ammo::Ammo Called !");
}

GameObject* Ammo::instance()
{

	AmmoDef ammoDef((const char*)graphicsFile, velocity, direction, directionAffectRotation, physicsGroup, damage);

	Ammo* newAmmo = Ammo::create(ammoDef);
	newAmmo->damage = this->damage;

	return newAmmo;
}
