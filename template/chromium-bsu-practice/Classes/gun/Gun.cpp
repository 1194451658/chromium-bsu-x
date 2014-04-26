
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

#include "Gun.h"
#include "shotMethod/LateralShotMethod.h"
#include "shotMethod/MiddleShotMethod.h"
#include "shotMethod/SwapLateralShotMethod.h"
#include "shotMethod/SineShotMethod.h"
#include "shotMethod/StrafeShotMethod.h"

#include "coldTimeMethod/EqualColdTime.h"
#include "coldTimeMethod/GroupShotColdTimeMethod.h"


bool Gun::init(Aircraft* owner, Ammo* prototypeAmmo, ColdTimeMethod* coldTimeMethod, ShotMethod* shotMethod)
{
	if(GameObject::init())
	{
		name = "Gun";

		// physics group
		if(owner)
			physicsGroup = owner->getOnePhysicsGroup();
		else
			physicsGroup = PhysicsManager::PHYSICS_GROUP_UNKNOWN;

		this->prototypeAmmo = prototypeAmmo;
		prototypeAmmo->retain();

		this->coldTimeMethod = coldTimeMethod;
		coldTimeMethod->retain();

		this->shotMethod = shotMethod;
		shotMethod->retain();

		//
		direction = CCPoint(0,1);

		coldTime = 0.2;
		curTimeToCold = 0;
		triggerPressed = false;

		return true;
	}

	return false;
}

void Gun::setOwnerAircraft(Aircraft* owner)
{
	if(owner)
		physicsGroup = owner->getOnePhysicsGroup();
}

Gun::Gun()
{
}

Gun::~Gun()
{
	CC_SAFE_RELEASE(prototypeAmmo);
	CC_SAFE_RELEASE(shotMethod);
}

Gun* Gun::create(Aircraft* owner, Ammo* prototypeAmmo, ColdTimeMethod* coldTimeMethod, ShotMethod* shotMethod)
{
	Gun* newGun = new Gun();

	if(newGun && newGun->init(owner, prototypeAmmo, coldTimeMethod, shotMethod))
	{
		newGun->autorelease();
		return newGun;
	}

	CC_SAFE_DELETE(newGun);
	return NULL;
}

void Gun::update(float time)
{
	//curTimeToCold -= time;
	//if(curTimeToCold < 0) curTimeToCold = 0;

	//if(triggerPressed && curTimeToCold == 0)
	//{
	//	curTimeToCold = coldTime;
	//	shotMethod->shot(this);
	//}

	if(triggerPressed)
	{
		if(coldTimeMethod->isTimeToShot(time))
		{
			shotMethod->shot(this);
		}
	}
}

Ammo* Gun::createAmmo()
{
	Ammo* newAmmo = (Ammo*)prototypeAmmo->instance();



	newAmmo->setPhysicsGroup(physicsGroup);

	return newAmmo;
}

Gun* Gun::createHeroDefaultGun()
{
	// ammo
	AmmoDef	ammoDef("png/heroAmmo00.png",
		500,			// velocity
		CCPoint(0,1),	// direction
		false,
		PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		50.0f);

	Ammo* prototypeAmmo = Ammo::create(ammoDef);

	// cold time
	//ColdTimeMethod* coldTimeMethod = EqualColdTime::create(0.2);
	ColdTimeMethod* coldTimeMethod = GroupShotColdTimeMethod::create(0.1, 3, 0.4);

	// shot method
	CCPoint relativePos = CCPoint(10,0);
	ShotMethod* shotMethod = LateralShotMethod::create(relativePos);

	// create gun
	Gun* gun = Gun::create(NULL, prototypeAmmo,coldTimeMethod, shotMethod);

	return gun;
}

 Gun* Gun::createGunExample1()
{
	// ammo
	AmmoDef	ammoDef("png/heroAmmo00.png",
		500,
		CCPoint(0,1),	// direction
		false,
		PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		100.0f);

	Ammo* prototypeAmmo = Ammo::create(ammoDef);

	// cold time
	ColdTimeMethod* coldTimeMethod = EqualColdTime::create(0.2);

	// shot method
	CCPoint relativePos = CCPoint(0,10);
	ShotMethod* shotMethod = MiddleShotMethod::create(relativePos);

	// create gun
	Gun* gun = Gun::create(NULL, prototypeAmmo, coldTimeMethod, shotMethod);

	return gun;
}

Gun* Gun::createGunSwapLateralExample()
 {
	 // ammo
	 AmmoDef	ammoDef("png/heroAmmo00.png",
		 500,
		 CCPoint(0,1),
		 false,
		 PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		 100.0f);

	 Ammo* prototypeAmmo = Ammo::create(ammoDef);

	 // cold time
	 ColdTimeMethod* coldTimeMethod = EqualColdTime::create(0.2);

	 // shot method
	 CCPoint relativePos = CCPoint(10,0);
	 ShotMethod* shotMethod = SwapLateralShotMethod::create(relativePos);

	 // create gun
	 Gun* gun = Gun::create(NULL, prototypeAmmo, coldTimeMethod, shotMethod);
	 return gun;
 }

Gun* Gun::createGunSinExample()
{
	// ammo
	AmmoDef	ammoDef("png/heroAmmo00.png",
		500,
		CCPoint(0,1),
		false,
		PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		100.0f);

	Ammo* prototypeAmmo = Ammo::create(ammoDef);

	// cold time
	ColdTimeMethod* coldTimeMethod = EqualColdTime::create(0.2);

	// shot method
	CCPoint relativePos = CCPoint(30,0);
	ShotMethod* shotMethod = SineShotMethod::create(relativePos, 13);

	// create gun
	Gun* gun = Gun::create(NULL, prototypeAmmo, coldTimeMethod, shotMethod);
	return gun;
}

 Gun* Gun::createGunStrafeExample()
{
	// ammo
	AmmoDef	ammoDef("png/heroAmmo00.png",
		500,
		CCPoint(0,1),
		true,
		PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		100.0f);

	Ammo* prototypeAmmo = Ammo::create(ammoDef);

	// cold time
	ColdTimeMethod* coldTimeMethod = EqualColdTime::create(0.2);

	// shot method
	CCPoint relativePos = CCPoint(0,10);
	ShotMethod* shotMethod = StrafeShotMethod::create(relativePos, 45, 8);

	// create gun
	Gun* gun = Gun::create(NULL, prototypeAmmo, coldTimeMethod, shotMethod);
	return gun;
}
