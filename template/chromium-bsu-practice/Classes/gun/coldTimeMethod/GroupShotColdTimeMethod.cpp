
#include "GroupShotColdTimeMethod.h"
#include "math.h"

bool GroupShotColdTimeMethod::isTimeToShot(float dt)
{
	curCycleTime += dt;
	curTimeToNextShot -= dt;

	if(curTimeToNextShot <= 0)
	{
		shotted();
		return true;
	}

	notShotted();
	return false;
}

 void GroupShotColdTimeMethod::shotted()
 {
	 if(curCycleTime >= oneCycleTime)
	 {
		 curNotShotedCount = shotCount;
	 }

	 curNotShotedCount--;

	 if(curNotShotedCount == shotCount-1)
	 {
		 // just after first shot
		 curCycleTime = 0;
	 }

	 if(curNotShotedCount == 0)
	 {
		 curTimeToNextShot = oneCycleTime - curCycleTime;
		 curNotShotedCount = shotCount;
	 }
	 else
	 {
		 curTimeToNextShot = smallColdTime;
	 }
}
 void GroupShotColdTimeMethod::notShotted()
{
	if(curCycleTime >= oneCycleTime)
	{
		curNotShotedCount = shotCount;
	}

	if(curTimeToNextShot < 0) curTimeToNextShot = 0;
}

GroupShotColdTimeMethod::GroupShotColdTimeMethod()
{
}

bool GroupShotColdTimeMethod::init(float smallColdTime, int shotCount, float greatColdTime)
{
	this->smallColdTime = smallColdTime;
	this->shotCount = shotCount;
	this->greatColdTime = greatColdTime;

	if(this->smallColdTime < 0) this->smallColdTime = 0;
	if(this->shotCount < 1) this->shotCount = 1;
	if(this->greatColdTime < 0) this->greatColdTime = 0;


	oneCycleTime = (shotCount-1) * this->smallColdTime + this->greatColdTime;

	curCycleTime = 0;
	curTimeToNextShot = 0;
	curNotShotedCount = shotCount;

	return ColdTimeMethod::init();
}

GroupShotColdTimeMethod* GroupShotColdTimeMethod::create(float smallColdTime, int continueShotCount, float greatColdTime)
{

	GroupShotColdTimeMethod* newColdTimeMethod = new GroupShotColdTimeMethod();

	if(newColdTimeMethod && newColdTimeMethod->init(smallColdTime, continueShotCount, greatColdTime))
	{
		newColdTimeMethod->autorelease();
		return newColdTimeMethod;
	}

	CC_SAFE_DELETE(newColdTimeMethod);

	return NULL;
}

