
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


bool Gun::init(Aircraft* owner, Ammo* prototypeAmmo, ShotMethod* shotMethod)
{
	if(GameObject::init())
	{
		name = "Gun";

		if(owner)
			physicsGroup = owner->getOnePhysicsGroup();
		else
			physicsGroup = PhysicsManager::PHYSICS_GROUP_UNKNOWN;

		this->prototypeAmmo = prototypeAmmo;
		prototypeAmmo->retain();

		this->shotMethod = shotMethod;
		shotMethod->retain();

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

Gun* Gun::create(Aircraft* owner, Ammo* prototypeAmmo, ShotMethod* shotMethod)
{
	Gun* newGun = new Gun();

	if(newGun && newGun->init(owner, prototypeAmmo, shotMethod))
	{
		newGun->autorelease();
		return newGun;
	}

	CC_SAFE_DELETE(newGun);
	return NULL;
}

void Gun::update(float time)
{
	curTimeToCold -= time;
	if(curTimeToCold < 0) curTimeToCold = 0;

	if(triggerPressed && curTimeToCold == 0)
	{
		curTimeToCold = coldTime;
		shotMethod->shot(this);
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
		CCPoint(0,500),
		PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		100.0f);

	Ammo* prototypeAmmo = Ammo::create(ammoDef);

	// shot method
	CCPoint relativePos = CCPoint(10,0);
	ShotMethod* shotMethod = LateralShotMethod::create(relativePos);

	// create gun
	Gun* gun = Gun::create(NULL, prototypeAmmo, shotMethod);

	return gun;
}

 Gun* Gun::createGunExample1()
{
	// ammo
	AmmoDef	ammoDef("png/heroAmmo00.png",
		CCPoint(0,500),
		PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		100.0f);

	Ammo* prototypeAmmo = Ammo::create(ammoDef);

	// shot method
	CCPoint relativePos = CCPoint(0,10);
	ShotMethod* shotMethod = MiddleShotMethod::create(relativePos);

	// create gun
	Gun* gun = Gun::create(NULL, prototypeAmmo, shotMethod);

	return gun;
}

Gun* Gun::createGunSwapLateralExample()
 {
	 // ammo
	 AmmoDef	ammoDef("png/heroAmmo00.png",
		 CCPoint(0,500),
		 PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		 100.0f);

	 Ammo* prototypeAmmo = Ammo::create(ammoDef);

	 // shot method
	 CCPoint relativePos = CCPoint(10,0);
	 ShotMethod* shotMethod = SwapLateralShotMethod::create(relativePos);

	 // create gun
	 Gun* gun = Gun::create(NULL, prototypeAmmo, shotMethod);
	 return gun;
 }

Gun* Gun::createGunSinExample()
{
	// ammo
	AmmoDef	ammoDef("png/heroAmmo00.png",
		CCPoint(0,500),
		PhysicsManager::PHYSICS_GROUP_UNKNOWN,
		100.0f);

	Ammo* prototypeAmmo = Ammo::create(ammoDef);

	// shot method
	CCPoint relativePos = CCPoint(30,0);
	ShotMethod* shotMethod = SineShotMethod::create(relativePos, 13);

	// create gun
	Gun* gun = Gun::create(NULL, prototypeAmmo, shotMethod);
	return gun;
}
