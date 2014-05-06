
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

#include "Aircraft.h"
#include "physics/GB2ShapeCache-x.h"
#include "HeroAircraft.h"

bool Aircraft::init(AircraftDef def)
{
	aircraftDef = def;

	maxHp = def.hp;
	curHp = def.hp;
	damageToHit = 0;

	if(GameObject::init())
	{
		name = "Aircraft";
		hpBarInit(100, 10, maxHp, curHp);
		return true;
	}

	return false;
}

Aircraft* Aircraft::create(AircraftDef& def)
{
	Aircraft* aircraft = new Aircraft();

	if(aircraft && aircraft->init(def))
	{

		aircraft->autorelease();
		return aircraft;
	}

	return NULL;
}

CCNode* Aircraft::initGraphics()
{
	// create the graphics
	CCSpriteWithShadow* sprite = CCSpriteWithShadow::create(aircraftDef.graphicsFile.c_str());
	return sprite;
}

b2Body* Aircraft::initPhysics()
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
    
	// add the fixture 
	GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(body, aircraftDef.physicsShapeName.c_str());

	// collision filter
	b2Filter filter;
	filter.groupIndex	= aircraftDef.groupIndex;
	filter.categoryBits = aircraftDef.categoryBits;
	filter.maskBits		= aircraftDef.maskBits;

	b2Fixture* fixtureList = body->GetFixtureList();

	while(NULL != fixtureList)
	{
		fixtureList->SetFilterData(filter);
		fixtureList = fixtureList->GetNext();
	}

	return body;
}

void Aircraft::damage(float damage)
{
	if(damage < 0) damage = 0;
		damageToHit += damage;
}

void Aircraft::hpBarInit(float width, float height, float maxValue, float initialValue)
{
	CCLayerColor* bg = CCLayerColor::create(ccc4(255, 0, 0, 255));
	bg->changeWidthAndHeight(width, height);

	CCLayerColor* fg = CCLayerColor::create(ccc4(0, 255, 0, 255));
	float fgWidth = initialValue / maxValue * width;
	fg->changeWidthAndHeight(fgWidth, height);
	bg->addChild(fg);

	// center hp bar
	bg->setPosition(ccp(-bg->getContentSize().width/2, 30));

	hpBarMaxValue = maxValue;
	hpBarCurValue = initialValue;
	hpBarWidth = width;
	hpBarHeight = height;

	hpBarBg = bg;
	hpBarFg = fg;

	// add bar
	addChild(bg);
}

void Aircraft::hpBarUpdate(float percentage)
{
	if(percentage < 0) percentage = 0;
	hpBarFg->changeWidthAndHeight(hpBarWidth * percentage, hpBarHeight);
}

void Aircraft::update(float dt)
{
	if(curHp < 0)
	{
		removeFromParent();
		shouldReleased = true;
	}

	if(damageToHit > 0)
	{
		//curHp -= damageToHit;
		setCurHp(curHp-damageToHit);
		damageToHit = 0;
	}
}

void Aircraft::setCurHp(float newHp)
{
	curHp = newHp;
	hpBarUpdate(curHp / maxHp);
}

CCSpriteWithShadow* Aircraft::getShadowSprite()
{
	CCSpriteWithShadow* shadow = dynamic_cast<CCSpriteWithShadow*>(graphics);
	return shadow;
}

///////////////////////////

Aircraft* Aircraft::createHeroAircraft()
{
	AircraftDef aircraftDef;
	Aircraft* hero = HeroAircraft::create(aircraftDef);
	return hero;
}

Aircraft* Aircraft::createEnemyAircraft01()
{
	AircraftDef aircraftDef;
	aircraftDef.graphicsFile	= "png/airCraft/enemy00.png";
	aircraftDef.physicsShapeName = "enemy00";
	aircraftDef.hp				= 99999;
	aircraftDef.groupIndex		= PhysicsManager::PHYSICS_GROUP_ENEMY;
	aircraftDef.categoryBits	= PhysicsManager::AIRCRAFT;
	aircraftDef.maskBits		= PhysicsManager::AIRCRAFT | PhysicsManager::AMMO;
	Aircraft* craft = Aircraft::create(aircraftDef);
	return craft;
}
