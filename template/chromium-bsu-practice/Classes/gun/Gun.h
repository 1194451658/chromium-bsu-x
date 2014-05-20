
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
#include "engine/GameObject.h"
#include "Ammo.h"
#include "aircraft/Aircraft.h"
#include "ColdTimeMethod.h"

USING_NS_CC;

class ShotMethod;
class ColdTimeMethod;

class Gun : public GameObject
{
public:
	static Gun* create(Aircraft* owner, Ammo* prototypeAmmo, ColdTimeMethod* coldTimeMethod, ShotMethod* shotMethod);
	~Gun();

	void update(float time);
	Ammo* createAmmo();

	void trigger(bool pressed) { triggerPressed = pressed;}
	void setOwnerAircraft(Aircraft* owner);

	virtual void setDirection(CCPoint& d)
	{
		direction = d.normalize();
		prototypeAmmo->ammoDef.direction  = direction;
	}

	void setShotMethod(ShotMethod* shotMethod);

	// create specific gun
	static Gun* createHeroDefaultGun();
	static Gun* createGunExample1();
	static Gun* createGunSwapLateralExample();
	static Gun* createGunSinExample();
	static Gun* createGunStrafeExample();

	// boss gun
	static Gun* createEnemyBoss00Gun0();
	static Gun* createEnemyBoss00Gun1();

	static Gun* createEnemyStraightGun();
	static Gun* createEnemyOmniGun();
	static Gun* createEnemyRayGun();
	static Gun* createEnemyTankGun();

protected:
	Gun();
	bool init(Aircraft* owner, Ammo* prototypeAmmo, ColdTimeMethod* coldTimeMethod, ShotMethod* shotMethod);

private:
	CCPoint direction;
	int physicsGroup;

	float coldTime;
	float curTimeToCold;
public:
	Ammo* prototypeAmmo;
	ColdTimeMethod* coldTimeMethod;
	ShotMethod* shotMethod;
private:
	
	bool triggerPressed;
	Aircraft* ownerAircraft;

private:
	static int serialNumber;
};
#endif

