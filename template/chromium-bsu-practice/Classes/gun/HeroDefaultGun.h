
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


#ifndef __HERO_DEFAULT_GUN_H__
#define __HERO_DEFAULT_GUN_H__

#include "cocos2d.h"

#include "aircraft/Aircraft.h"
#include "Gun.h"
#include "Ammo.h"

USING_NS_CC;

class HeroDefaultGun : public Gun
{

public:
	static HeroDefaultGun* create(Aircraft* ownerAircraft);
	~HeroDefaultGun();
	virtual void update(float time);
	virtual void setOwnerAircraft(Aircraft* owner);

	Ammo* createAmmo();

protected:
	HeroDefaultGun();
	bool init(Aircraft* aircraft);

private:
	float coldTime;
	float currentColdTime;

	 float velocity;
	 int physicsGroup;

	CCPoint gunPosLeft;
	CCPoint gunPosRight;


};

#endif
