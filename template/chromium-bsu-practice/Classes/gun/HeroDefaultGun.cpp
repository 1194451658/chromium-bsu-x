
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

HeroDefaultGun::HeroDefaultGun()
{
}

HeroDefaultGun::~HeroDefaultGun()
{
}

bool HeroDefaultGun::init(Aircraft* aircraft, CCPoint& velocity, int physicsGroup)
{
	if(GameObject::init())
	{
		name = "HeroDefaultGun";
		currentColdTime = 0;
		coldTime = 0.3;
		triggerPressed = false;

		this->velocity = velocity;
		this->physicsGroup = physicsGroup;

		this->aircraft = aircraft;

		gunPosLeft = CCPoint(-10, 0);
		gunPosRight = CCPoint(10, 0);

		return true;
	}

	return false;
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
		{
			Ammo* newAmmo = createAmmo();

			float posX = aircraft->getPositionX();
			posX += gunPosLeft.x;

			float posY = aircraft->getPositionY();
			posY += gunPosLeft.y;

			newAmmo->setPosition(posX, posY);
			CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
		}

		{
			Ammo* newAmmo = createAmmo();
			newAmmo->setPosition(aircraft->getPositionX() + gunPosRight.x, aircraft->getPositionY() + gunPosRight.y );
			CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
		}
	}
}

Ammo* HeroDefaultGun::createAmmo()
{
	// create ammo
	//CCSprite* ammoSprite = CCSprite::create("png/heroAmmo00.png");
	//if(velocity.y < 0) 
	//	ammoSprite->setFlipY(true);

	Ammo* newAmmo = Ammo::create("png/heroAmmo00.png", velocity, physicsGroup);

	return newAmmo;
}
