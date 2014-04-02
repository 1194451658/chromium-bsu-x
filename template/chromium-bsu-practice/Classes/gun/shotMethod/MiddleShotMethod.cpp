
#include "MiddleShotMethod.h"

void MiddleShotMethod::shot(Gun* gun)
{
	CCPoint gunPosInWorld = gun->convertToWorldSpace(CCPoint(0,0));

	{
		Ammo* newAmmo = gun->createAmmo();
		newAmmo->setPosition(gunPosInWorld.x + relativePos.x, gunPosInWorld.y + relativePos.y);
		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}
}

MiddleShotMethod::MiddleShotMethod()
{
}

bool MiddleShotMethod::init(CCPoint& relativePos)
{
	this->relativePos = relativePos;
	return ShotMethod::init();
}

MiddleShotMethod* MiddleShotMethod::create(CCPoint& relativePos)
{

	MiddleShotMethod* newShotMethod = new MiddleShotMethod();

	if(newShotMethod && newShotMethod->init(relativePos))
	{
		newShotMethod->autorelease();
		return newShotMethod;
	}

	CC_SAFE_DELETE(newShotMethod);

	return NULL;
}

