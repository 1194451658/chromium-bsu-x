
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


#ifndef __ENEMY_BOSS_00_H__
#define __ENEMY_BOSS_00_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Aircraft.h"

//#include "gun/HeroDefaultGun.h"
#include "gun/Gun.h"

USING_NS_CC;

class EnemyBoss00 : public Aircraft
{
public:
	static EnemyBoss00* create(AircraftDef def);
	bool init(AircraftDef def);
	void move(float dt);
	void shot(float dt);
	~EnemyBoss00();

public:
	// update
	virtual void update(float time);

protected:

private: 
	EnemyBoss00();

private:
	Gun* lateralGun;
	Gun* middleGun;

};

#endif
