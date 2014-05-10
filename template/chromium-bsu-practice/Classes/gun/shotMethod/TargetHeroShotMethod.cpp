

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
		CCPoint heroPos = hero->getPositionInWorldSpace();
		CCPoint dir = heroPos - gunPosInWorld;
		Ammo* newAmmo = gun->createAmmo();
		newAmmo->setPosition(gunPosInWorld.x + relativePos.x, gunPosInWorld.y + relativePos.y);
		newAmmo->setDirection(dir);
		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}
}

TargetHeroShotMethod::TargetHeroShotMethod()
{
}

bool TargetHeroShotMethod::init(CCPoint& relativePos)
{
	this->relativePos = relativePos;
	return ShotMethod::init();
}

TargetHeroShotMethod* TargetHeroShotMethod::create(CCPoint& relativePos)
{

	TargetHeroShotMethod* newShotMethod = new TargetHeroShotMethod();

	if(newShotMethod && newShotMethod->init(relativePos))
	{
		newShotMethod->autorelease();
		return newShotMethod;
	}

	CC_SAFE_DELETE(newShotMethod);

	return NULL;
}

