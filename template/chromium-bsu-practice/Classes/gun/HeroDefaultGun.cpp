
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

bool HeroDefaultGun::init(Aircraft* ownerAircraft)
{
	if(Gun::init())
	{
		name = "HeroDefaultGun";

		velocity = 400;
		currentColdTime = 0;
		coldTime = 0.3;
		gunPosLeft = CCPoint(-10, 0);
		gunPosRight = CCPoint(10, 0);
		physicsGroup = PhysicsManager::GROUP_UNKNOWN;

		this->ownerAircraft = ownerAircraft;

		if(ownerAircraft)
		{
			this->physicsGroup = ownerAircraft->getOnePhysicsGroup();
		}

		return true;
	}

	return false;
}

HeroDefaultGun* HeroDefaultGun::create(Aircraft* aircraft)
{
	HeroDefaultGun* newGun = new HeroDefaultGun();

	if(newGun && newGun->init(aircraft))
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

		CCPoint posInWorld = this->convertToWorldSpace(CCPoint(0,0));

		// fire
		{
			Ammo* newAmmo = createAmmo();
			float posX = posInWorld.x + gunPosLeft.x;
			float posY = posInWorld.y + gunPosLeft.y;
			newAmmo->setPosition(posX, posY);
			CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
		}

		{
			Ammo* newAmmo = createAmmo();
			newAmmo->setPosition(posInWorld.x + gunPosRight.x, posInWorld.y + gunPosRight.y );
			CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
		}
	}
}

Ammo* HeroDefaultGun::createAmmo()
{
	float damage = 100;
	CCPoint ammoVelocity = CCPoint(direction.x * velocity, direction.y * velocity);
	AmmoDef ammoDef("png/heroAmmo00.png", ammoVelocity, physicsGroup, damage);
	Ammo* newAmmo = Ammo::create(ammoDef);

	return newAmmo;
}

void HeroDefaultGun::setOwnerAircraft(Aircraft* owner)
{
	Gun::setOwnerAircraft(owner);

	if(owner)
	{
		physicsGroup = owner->getOnePhysicsGroup();
	}
};
