
#ifndef __GROUP_SHOT_COLD_TIME_METHOD_H__
#define __GROUP_SHOT_COLD_TIME_METHOD_H__

#include "cocos2d.h"
#include "gun/ColdTimeMethod.h"

USING_NS_CC;

class GroupShotColdTimeMethod : public ColdTimeMethod
{
public:
	virtual bool isTimeToShot(float dt);
	virtual void shotted();
	virtual void notShotted();

	static GroupShotColdTimeMethod* create(float smallColdTime, int continueShotCount, float greatColdTime);

protected:
	bool init(float smallColdTime, int continueShotCount, float greatColdTime);
	GroupShotColdTimeMethod();

private:
	float smallColdTime;
	float greatColdTime;

	int shotCount;
	int curNotShotedCount;

	float oneCycleTime;
	float curCycleTime;

	float curTimeToNextShot;
};

#endif