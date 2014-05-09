
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

#include "StrafeShotMethod.h"

void StrafeShotMethod::shot(Gun* gun)
{
	CCPoint gunPosInWorld = gun->convertToWorldSpace(CCPoint(0,0));

	{
		Ammo* newAmmo = gun->createAmmo();
		CCPoint dir = CCPoint::forAngle(sin(currentAngle)*CC_DEGREES_TO_RADIANS(angleRangeDegree) + 3.1415/2);
		newAmmo->setDirection(dir);

		newAmmo->setPosition(gunPosInWorld.x + relativePos.x, gunPosInWorld.y + relativePos.y);
		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}

	currentAngle += angleStep;
}

StrafeShotMethod::StrafeShotMethod()
{
}

bool StrafeShotMethod::init(CCPoint& relativePos, float angleRangeDegree, int periodCount)
{
	this->relativePos = relativePos;
	this->angleRangeDegree = angleRangeDegree;

	this->periodCount = periodCount;
	if(this->periodCount < 0) this->periodCount = 0;

	angleStep = 3.1415f / periodCount;
	currentAngle = 0;

	return ShotMethod::init();
}

StrafeShotMethod* StrafeShotMethod::create(CCPoint& relativePos, float angleRangeDegree, float periodCount)
{

	StrafeShotMethod* newShotMethod = new StrafeShotMethod();

	if(newShotMethod && newShotMethod->init(relativePos, angleRangeDegree, periodCount))
	{
		newShotMethod->autorelease();
		return newShotMethod;
	}

	CC_SAFE_DELETE(newShotMethod);

	return NULL;
}

