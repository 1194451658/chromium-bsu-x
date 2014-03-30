
#include "LateralShot.h"

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
		newShotMethod->retain();
		return newShotMethod;
	}

	CC_SAFE_DELETE(newShotMethod);

	return NULL;
}

