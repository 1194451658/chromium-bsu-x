
#ifndef __SINE_SHOT_H__
#define __SINE_SHOT_H__

#include "gun/ShotMethod.h"
#include "gun/Gun.h"

class SineShotMethod : public ShotMethod
{
public:
	virtual void shot(Gun* gun);
	static SineShotMethod* create(CCPoint& relativePos, int periodCount);

protected:
	bool init(CCPoint& relativePos, int periodCount);
	SineShotMethod();

private:
	CCPoint relativePos;
	int periodCount;

	// 
	float currentAngle;
	float angleStep;
};

#endif
