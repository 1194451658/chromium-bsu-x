

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

#include "LateralShotMethod.h"
#include "math.h"

void LateralShotMethod::shot(Gun* gun)
{
	CCPoint gunPosInWorld = gun->convertToWorldSpace(CCPoint(0,0));

	{
		Ammo* newAmmo = gun->createAmmo();
		newAmmo->setPosition(gunPosInWorld.x + relativePos.x, gunPosInWorld.y + relativePos.y);
		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}

	{
		Ammo* newAmmo = gun->createAmmo();
		newAmmo->setPosition(gunPosInWorld.x - relativePos.x, gunPosInWorld.y + relativePos.y);
		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}
}

LateralShotMethod::LateralShotMethod()
{
}

bool LateralShotMethod::init(CCPoint& relativePos)
{
	this->relativePos = relativePos;
	return ShotMethod::init();
}

LateralShotMethod* LateralShotMethod::create(CCPoint& relativePos)
{

	LateralShotMethod* newShotMethod = new LateralShotMethod();

	if(newShotMethod && newShotMethod->init(relativePos))
	{
		newShotMethod->autorelease();
		return newShotMethod;
	}

	CC_SAFE_DELETE(newShotMethod);

	return NULL;
}

