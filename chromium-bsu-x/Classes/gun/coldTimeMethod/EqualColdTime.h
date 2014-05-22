
#ifndef __EQUAL_COLD_TIME_H__
#define __EQUAL_COLD_TIME_H__

#include "gun/ColdTimeMethod.h"
#include "AppMacros.h"

USING_NS_CC;

class EqualColdTime : public ColdTimeMethod
{
public:
	virtual bool isTimeToShot(float dt);
	virtual void shotted();
	virtual void notShotted();

	static EqualColdTime* create(float coldTime);

protected:
	bool init(float coldTime);
	EqualColdTime();

private:
	float coldTime;
	float curTimeToShot;
};

#endif