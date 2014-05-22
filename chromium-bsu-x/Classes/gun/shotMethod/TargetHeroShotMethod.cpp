

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

#include "TargetHeroShotMethod.h"
#include "GameController.h"

void TargetHeroShotMethod::shot(Gun* gun)
{
	CCPoint gunPosInWorld = gun->convertToWorldSpace(CCPoint(0,0));
	Aircraft* hero = GameController::sharedInstance()->getPlayerAircraft();

	if(hero)
	{
		// if retarget hero
		if(curTargetPeriodCount == targetPeriodCount)
		{
			curTargetPeriodCount = targetPeriodCount;
			CCPoint heroPos = hero->getPositionInWorldSpace();
			previousDir = heroPos - gunPosInWorld;
		}

		if(curTargetPeriodCount >= 0)
		{
			Ammo* newAmmo = gun->createAmmo();
			newAmmo->setPosition(gunPosInWorld.x + relativePos.x, gunPosInWorld.y + relativePos.y);
			CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
			newAmmo->setDirection(previousDir);
		}

		curTargetPeriodCount--;

		if(curTargetPeriodCount <= -8)
		{
			curTargetPeriodCount = targetPeriodCount;
		}
	}
}

TargetHeroShotMethod::TargetHeroShotMethod()
{
	targetPeriodCount = 0;
	curTargetPeriodCount = 0;
}

bool TargetHeroShotMethod::init(CCPoint& relativePos, int targetPeriodCount)
{
	this->relativePos = relativePos;
	this->targetPeriodCount = targetPeriodCount;
	curTargetPeriodCount = targetPeriodCount;
	return ShotMethod::init();
}

TargetHeroShotMethod* TargetHeroShotMethod::create(CCPoint& relativePos, int targetPeriodCount)
{

	TargetHeroShotMethod* newShotMethod = new TargetHeroShotMethod();

	if(newShotMethod && newShotMethod->init(relativePos, targetPeriodCount))
	{
		newShotMethod->autorelease();
		return newShotMethod;
	}

	CC_SAFE_DELETE(newShotMethod);

	return NULL;
}

