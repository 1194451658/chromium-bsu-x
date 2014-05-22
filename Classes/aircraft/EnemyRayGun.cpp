
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


#include "EnemyRayGun.h"
#include "math.h"
#include "GameController.h"

EnemyRayGun* EnemyRayGun::create(AircraftDef def)
{
	EnemyRayGun* hero = new EnemyRayGun();

	if(hero && hero->init(def))
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

EnemyRayGun::EnemyRayGun()
{
	lastMoveX = 0;
	lastMoveY = 0;
	time = 0;
	shiftX = 200;
	yDistance = 400;
}

bool EnemyRayGun::init(AircraftDef def)
{
	// init base class
	if(Aircraft::init(def))
	{
		name = "EnemyRayGun";

		// create gun
		defaultGun = Gun::createEnemyBoss00Gun1();
		addChild(defaultGun);
		defaultGun->setOwnerAircraft(this);
		CC_SAFE_RETAIN(defaultGun);

		return true;
	}

	return false;
}

EnemyRayGun::~EnemyRayGun()
{

}

void EnemyRayGun::move(float dt)
{
	time += dt;

	// get hero
	Aircraft* hero = GameController::sharedInstance()->getPlayerAircraft();

	if(hero)
	{
		CCPoint pos = hero->getPositionInWorldSpace();
		CCPoint selfPos = getPositionInWorldSpace();

		CCPoint distance = pos - selfPos;

		distance.x += shiftX * sin(3.151*2 * time / 2);
		lastMoveX = lastMoveX * 0.97 + distance.x * 0.0003;

		distance.y += yDistance;
		lastMoveY = lastMoveY * 0.97 + distance.y * 0.0003;

		setPositionX(getPositionX() + lastMoveX);
		setPositionY(getPositionY() + lastMoveY);
	}
}

void EnemyRayGun::shot(float dt)
{
	// get hero
	Aircraft* hero = GameController::sharedInstance()->getPlayerAircraft();

	if(hero)
	{
		CCPoint pos = hero->getPositionInWorldSpace();
		CCPoint selfPos = getPositionInWorldSpace();

		if(fabs(selfPos.x - pos.x) < 50)
		{
			defaultGun->trigger(true);
		}
		else
		{
			defaultGun->trigger(false);
		}
	}else
	{
		defaultGun->trigger(false);
	}
}

void EnemyRayGun::update(float dt)
{
	Aircraft::update(dt);

	// move
	move(dt);

	// shot
	shot(dt);
}
