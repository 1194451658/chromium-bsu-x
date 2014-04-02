
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

#ifndef __GUN_H__
#define __GUN_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Ammo.h"
#include "aircraft/Aircraft.h"

USING_NS_CC;

class ShotMethod;

class Gun : public GameObject
{
public:
	static Gun* create(Aircraft* owner, Ammo* prototypeAmmo, ShotMethod* shotMethod);
	~Gun();

	void update(float time);
	Ammo* createAmmo();

	void trigger(bool pressed) { triggerPressed = pressed;}
	void setOwnerAircraft(Aircraft* owner);

	virtual void setDirection(CCPoint& d)
	{
		direction = d.normalize();
	}

	// create specific gun
	static Gun* createHeroDefaultGun();
	static Gun* createGunExample1();
	static Gun* createGunSwapLateralExample();
	static Gun* createGunSinExample();

protected:
	Gun();
	bool init(Aircraft* owner, Ammo* prototypeAmmo, ShotMethod* shotMethod);

private:
	CCPoint direction;
	int physicsGroup;

	float coldTime;
	float curTimeToCold;

	Ammo* prototypeAmmo;
	ShotMethod* shotMethod;
	
	bool triggerPressed;
	Aircraft* ownerAircraft;
};
#endif

