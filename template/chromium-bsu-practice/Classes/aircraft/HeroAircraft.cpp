
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


#include "HeroAircraft.h"
#include "input/InputManager.h"
#include "physics/GB2ShapeCache-x.h"

HeroAircraft* HeroAircraft::create()
{
	HeroAircraft* hero = new HeroAircraft();

	if(hero && hero->init())
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

HeroAircraft::HeroAircraft()
{
}

bool HeroAircraft::init()
{
	// init base class
	if(Aircraft::init())
	{
		name = "HeroAircraft";

		// create gun
		defaultGun = Gun::createHeroDefaultGun();
		defaultGun->retain();

		//defaultGun = Gun::createGunExample1();
		//defaultGun->retain();

		//defaultGun = Gun::createGunSwapLateralExample();
		//defaultGun->retain();

		//defaultGun = Gun::createGunSinExample();
		//defaultGun->retain();

		//defaultGun = Gun::createGunStrafeExample();
		//defaultGun->retain();

		defaultGun->setOwnerAircraft(this);
		addChild(defaultGun);

		return true;
	}

	return false;
}

HeroAircraft::~HeroAircraft()
{
	CC_SAFE_RELEASE_NULL(graphics);
}

void HeroAircraft::update(float dt)
{
	// move
	InputManager* input = InputManager::sharedInstance();

	if(input->arrowState[input->ARROW_UP] == InputManager::ARROW_PRESSED)
		setPositionY(getPositionY() + 10);

	if(input->arrowState[input->ARROW_DOWN] == InputManager::ARROW_PRESSED)
		setPositionY(getPositionY() - 10);

	if(input->arrowState[input->ARROW_LEFT] == InputManager::ARROW_PRESSED)
		setPositionX(getPositionX() - 10);

	if(input->arrowState[input->ARROW_RIGHT] == InputManager::ARROW_PRESSED)
		setPositionX(getPositionX() + 10);

	if(input->arrowState[input->FIRE] == InputManager::ARROW_PRESSED)
	{
		defaultGun->trigger(true);
	}
	else
	{
		defaultGun->trigger(false);
	}
}

CCNode* HeroAircraft::initGraphics()
{
	// create the graphics
	CCSprite* sprite = CCSprite::create("png/airCraft/hero.png");

	return sprite;
}

b2Body* HeroAircraft::initPhysics()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	// physics world
	b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();

	// body 
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.allowSleep = false;
	bodyDef.fixedRotation = true;
	bodyDef.position.Set(screenSize.width/2/PhysicsManager::PTM_RATIO, screenSize.height/2/PhysicsManager::PTM_RATIO);

	b2Body *body = world->CreateBody(&bodyDef);

	// b2PolygonShape shape;
	// shape.SetAsBox(160.0 / PTM_RATIO, 160.0 / PTM_RATIO);
	// body->CreateFixture(&shape, 1);
    
	// add the fixture 
	GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(body, "hero");

	// set fixture collide filter
	b2Filter filter;
	filter.groupIndex	= PhysicsManager::PHYSICS_GROUP_JUSTICE;
	filter.categoryBits = PhysicsManager::AIRCRAFT;
	filter.maskBits		= PhysicsManager::AIRCRAFT | 
					PhysicsManager::AMMO;

	b2Fixture* fixtureList = body->GetFixtureList();

	while(NULL != fixtureList)
	{
		fixtureList->SetFilterData(filter);
		fixtureList = fixtureList->GetNext();
	}

	return body;
}
