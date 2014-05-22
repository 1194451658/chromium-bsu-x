
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


#include "EnemyStraight.h"
#include "math.h"

int EnemyStraight::serialNumber = 0;

EnemyStraight* EnemyStraight::create(AircraftDef def)
{
	EnemyStraight* hero = new EnemyStraight();

	if(hero && hero->init(def))
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

EnemyStraight::EnemyStraight()
{
}

bool EnemyStraight::init(AircraftDef def)
{
	// init base class
	if(Aircraft::init(def))
	{
		serialNumber++;
		std::stringstream nameStr;
		nameStr<<"EnemeyStraight"<<serialNumber;
		name = nameStr.str();

		// create gun
		defaultGun = Gun::createEnemyStraightGun();
		addChild(defaultGun);
		defaultGun->setOwnerAircraft(this);
		CC_SAFE_RETAIN(defaultGun);

		return true;
	}

	return false;
}

EnemyStraight::~EnemyStraight()
{

}

void EnemyStraight::move(float dt)
{
	setPositionY(getPositionY() + aircraftDef.straightYVelocity * dt);
}

void EnemyStraight::shot(float dt)
{
	static int frame = 0;
	frame ++;

	//if(frame % 60 == 0)
	//	defaultGun->trigger(true);
	//else
	//{
	//	defaultGun->trigger(false);
	//}

	defaultGun->trigger(true);
}

void EnemyStraight::update(float dt)
{
	Aircraft::update(dt);

	// move
	move(dt);

	// shot
	shot(dt);
}
