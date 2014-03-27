

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
		// newAmmo->shouldReleased = true;

		const CCPoint& aircraftPos = aircraft->getPosition();
		newAmmo->setPosition(aircraftPos);

		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}
}
