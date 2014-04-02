
#include "SwapLateralShotMethod.h"

void SwapLateralShotMethod::shot(Gun* gun)
{
	CCPoint gunPosInWorld = gun->convertToWorldSpace(CCPoint(0,0));

	if(swapFlag == false)
	{
		swapFlag = true;
		Ammo* newAmmo = gun->createAmmo();
		newAmmo->setPosition(gunPosInWorld.x + relativePos.x, gunPosInWorld.y + relativePos.y);
		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}else
	{
		swapFlag = false;
		Ammo* newAmmo = gun->createAmmo();
		newAmmo->setPosition(gunPosInWorld.x - relativePos.x, gunPosInWorld.y + relativePos.y);
		CCDirector::sharedDirector()->getRunningScene()->addChild(newAmmo);
	}
}

SwapLateralShotMethod::SwapLateralShotMethod()
{
}

bool SwapLateralShotMethod::init(CCPoint& relativePos)
{
	this->relativePos = relativePos;
	swapFlag = false;
	return ShotMethod::init();
}

SwapLateralShotMethod* SwapLateralShotMethod::create(CCPoint& relativePos)
{

	SwapLateralShotMethod* newShotMethod = new SwapLateralShotMethod();

	if(newShotMethod && newShotMethod->init(relativePos))
	{
		newShotMethod->autorelease();
		return newShotMethod;
	}

	CC_SAFE_DELETE(newShotMethod);

	return NULL;
}

