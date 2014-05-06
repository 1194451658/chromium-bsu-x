
#include "EqualColdTime.h"
#include "math.h"

bool EqualColdTime::isTimeToShot(float dt)
{
	curTimeToShot -= dt;

	if(curTimeToShot <= 0)
	{
		shotted();
		return true;
	}

	notShotted();
	return false;
}

 void EqualColdTime::shotted()
{
	curTimeToShot = coldTime;
}
 void EqualColdTime::notShotted()
{
	if(curTimeToShot < 0) curTimeToShot = 0;
}

EqualColdTime::EqualColdTime()
{
}

bool EqualColdTime::init(float coldTime)
{
	this->coldTime = coldTime;
	if(this->coldTime < 0) this->coldTime = 0;

	curTimeToShot = 0;

	return ColdTimeMethod::init();
}

EqualColdTime* EqualColdTime::create(float coldTime)
{

	EqualColdTime* newColdTimeMethod = new EqualColdTime();

	if(newColdTimeMethod && newColdTimeMethod->init(coldTime))
	{
		newColdTimeMethod->autorelease();
		return newColdTimeMethod;
	}

	CC_SAFE_DELETE(newColdTimeMethod);

	return NULL;
}
