
#include "HeroDefaultGun.h"
#include "ammo/Ammo.h"

HeroDefaultGun::HeroDefaultGun()
{
}

HeroDefaultGun::~HeroDefaultGun()
{
}

bool HeroDefaultGun::init(Aircraft* aircraft, CCPoint& velocity, int physicsGroup)
{
	currentColdTime = 0;
	coldTime = 0.3;
	triggerPressed = false;

	this->velocity = velocity;
	this->physicsGroup = physicsGroup;

	this->aircraft = aircraft;
	return true;
}

HeroDefaultGun* HeroDefaultGun::create(Aircraft* aircraft, CCPoint& velocity, int physicsGroup)
{
	HeroDefaultGun* newGun = new HeroDefaultGun();

	if(newGun && newGun->init(aircraft, velocity, physicsGroup))
	{
		newGun->autorelease();
		return newGun;
	}

	CC_SAFE_RELEASE(newGun);
	return NULL;
}

void HeroDefaultGun::update(float time)
{
	currentColdTime -= time;
	if(currentColdTime < 0) currentColdTime = 0;

	if(triggerPressed && currentColdTime == 0)
	{
		currentColdTime = coldTime;
		// fire
		// CCLOG("default gun fired !!!");

		// create ammo
		CCSprite* ammoSprite = CCSprite::create("png/heroAmmo00.png");
		// CCSprite* ammoSprite = CCSprite::create("png/hero.png");

		if(velocity.y < 0) 
			ammoSprite->setFlipY(true);


		Ammo* newAmmo = Ammo::create(ammoSprite, velocity, physicsGroup);

		const CCPoint& aircraftPos = aircraft->getPosition();
		newAmmo->setPosition(aircraftPos);

		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}
}
