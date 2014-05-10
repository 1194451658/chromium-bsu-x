
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

#include "effect/Explosion.h"
#include "engine/action/CCRandTextureForAmmo.h"

using namespace CocosDenshion;

bool Ammo::init(AmmoDef& def)
{
	ammoDef = def;
	ammoDef.direction = def.direction.normalize();

	graphics = CCSprite::create(ammoDef.graphicsFile.c_str());

	if(ammoDef.directionAffectRotation)
	{
		this->graphics->setRotation(90 - CC_RADIANS_TO_DEGREES(ammoDef.direction.getAngle()));
	}

	if(GameObject::init())
	{
		name = "Ammo";
		shouldExplode = false;

		// scale
		setScaleX(def.scaleX);

		if(def.randTex)
		{
			// create rand texture action
			CCRandTextureForAmmo* randTextureAct = CCRandTextureForAmmo::create(1);
			CCRepeatForever* repeatAct = CCRepeatForever::create(randTextureAct);
			graphics->runAction(repeatAct);
		}

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
		bodyDef.linearVelocity.Set(ammoDef.direction.x * ammoDef.velocity/PhysicsManager::PTM_RATIO,
									ammoDef.direction.y * ammoDef.velocity/PhysicsManager::PTM_RATIO);
		b2Body* body = world->CreateBody(&bodyDef);

		b2PolygonShape shape;
		shape.SetAsBox(size.width/2/PhysicsManager::PTM_RATIO,
				size.height/2/PhysicsManager::PTM_RATIO);
		body->CreateFixture(&shape, 1);

		// set fixture collide filter
		b2Filter filter;
		filter.groupIndex	= ammoDef.physicsGroup;
		filter.categoryBits = PhysicsManager::AMMO;
		filter.maskBits		= PhysicsManager::AIRCRAFT | PhysicsManager::AMMO;

		b2Fixture* fixtureList = body->GetFixtureList();

		while(NULL != fixtureList)
		{
			fixtureList->SetFilterData(filter);
			fixtureList->SetSensor(true);
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
		// SimpleAudioEngine::sharedEngine()->playEffect("wav/exploStd.wav");
		
		shouldReleased = true;
		removeFromParent();
	}

	if(isOutScreen())
	{
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
	{
		aircraft->damage(ammoDef.damage);

		CCNode* parent = aircraft->getParent();
		if(parent)
		{
			Explositon* exp = Explositon::create(1,0,0,0,20,10);
			exp->setPosition(this->getPosition());
			parent->addChild(exp);
		}
	}
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
	Ammo* newAmmo = Ammo::create(ammoDef);

	return newAmmo;
}

Ammo* Ammo::createEnemyAmmo0()
{
	// ammo
	AmmoDef ammoDef;
	ammoDef.graphicsFile = "png/enemyAmmo00.png";
	ammoDef.velocity	= 400;
	ammoDef.direction	= ccp(0,-1);
	ammoDef.directionAffectRotation = false;
	ammoDef.physicsGroup = PhysicsManager::PHYSICS_GROUP_UNKNOWN;
	ammoDef.damage = 50;
	ammoDef.randTex = true;
	ammoDef.scaleX = 0.4;

	Ammo* prototypeAmmo = Ammo::create(ammoDef);
	return prototypeAmmo;
}

Ammo*  Ammo::createEnemyAmmo1()
{
	// ammo
	AmmoDef ammoDef;
	ammoDef.graphicsFile = "png/enemyAmmo01.png";
	ammoDef.velocity	= 400;
	ammoDef.direction	= ccp(0,1);
	ammoDef.directionAffectRotation = false;
	ammoDef.physicsGroup = PhysicsManager::PHYSICS_GROUP_UNKNOWN;
	ammoDef.damage = 50;
	ammoDef.randTex = true;

	Ammo* prototypeAmmo = Ammo::create(ammoDef);
	return prototypeAmmo;
}

Ammo*  Ammo::createEnemyAmmo2()
{
	// ammo
	AmmoDef ammoDef;
	ammoDef.graphicsFile = "png/enemyAmmo02.png";
	ammoDef.velocity	= 400;
	ammoDef.direction	= ccp(0,1);
	ammoDef.directionAffectRotation = false;
	ammoDef.physicsGroup = PhysicsManager::PHYSICS_GROUP_UNKNOWN;
	ammoDef.damage = 50;
	ammoDef.randTex = true;

	Ammo* prototypeAmmo = Ammo::create(ammoDef);
	return prototypeAmmo;
}

Ammo*  Ammo::createEnemyAmmo3()
{
	// ammo
	AmmoDef ammoDef;
	ammoDef.graphicsFile = "png/enemyAmmo03.png";
	ammoDef.velocity	= 2000;
	ammoDef.direction	= ccp(0,-1);
	ammoDef.directionAffectRotation = false;
	ammoDef.physicsGroup = PhysicsManager::PHYSICS_GROUP_UNKNOWN;
	ammoDef.damage = 50;
	ammoDef.randTex = true;
	ammoDef.scaleX = 0.4;

	Ammo* prototypeAmmo = Ammo::create(ammoDef);
	return prototypeAmmo;
}
