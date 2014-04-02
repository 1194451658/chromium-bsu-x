
#include "StrafeShotMethod.h"

void StrafeShotMethod::shot(Gun* gun)
{
	CCPoint gunPosInWorld = gun->convertToWorldSpace(CCPoint(0,0));

	{
		Ammo* newAmmo = gun->createAmmo();
		newAmmo->setDirection(CCPoint::forAngle(sin(currentAngle)*CC_DEGREES_TO_RADIANS(angleRangeDegree) + 3.1415/2));

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

