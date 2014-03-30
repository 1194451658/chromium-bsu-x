
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

bool Gun::init(Ammo* prototypeAmmo, ShotMethod* shotMethod)
{
	if(GameObject::init())
	{
		name = "Gun";

		physicsGroup = PhysicsManager::UNKNOWN;

		this->prototypeAmmo = prototypeAmmo;
		prototypeAmmo->retain();

		this->shotMethod = shotMethod;
		shotMethod->retain();

		coldTime = 1;
		curTimeToCold = 0;
		triggerPressed = false;

		return true;
	}

	return false;
}

Gun::Gun()
{
}

Gun::~Gun()
{
	CC_SAFE_RELEASE(prototypeAmmo);
	CC_SAFE_RELEASE(shotMethod);
}

Gun* Gun::create(Ammo* prototypeAmmo, ShotMethod* shotMethod)
{
	Gun* newGun = new Gun();

	if(newGun && newGun->init(prototypeAmmo, shotMethod))
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

