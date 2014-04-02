
#include "SineShotMethod.h"

void SineShotMethod::shot(Gun* gun)
{
	CCPoint gunPosInWorld = gun->convertToWorldSpace(CCPoint(0,0));

		Ammo* newAmmo = gun->createAmmo();
		newAmmo->setPosition(gunPosInWorld.x + relativePos.x * sin(currentAngle), gunPosInWorld.y + relativePos.y);
		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);

		currentAngle += angleStep;
}

SineShotMethod::SineShotMethod()
{
}

bool SineShotMethod::init(CCPoint& relativePos, int periodCount)
{
	this->relativePos = relativePos;
	this->periodCount = periodCount;

	// ensure periodCount
	if(this->periodCount < 0)
	{
		this->periodCount = -this->periodCount;
	}
	if(this->periodCount == 0)
	{
		this->periodCount = 1;
	}

	// 
	currentAngle = 0;
	angleStep =  3.1425926 / this->periodCount;

	return ShotMethod::init();
}

SineShotMethod* SineShotMethod::create(CCPoint& relativePos, int periodCount)
{

	SineShotMethod* newShotMethod = new SineShotMethod();

	if(newShotMethod && newShotMethod->init(relativePos, periodCount))
	{
		newShotMethod->autorelease();
		return newShotMethod;
	}

	CC_SAFE_DELETE(newShotMethod);

	return NULL;
}

