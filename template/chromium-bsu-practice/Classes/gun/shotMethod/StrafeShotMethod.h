
#ifndef __STRAFE_SHOT_H__
#define __STRAFE_LATERAL_SHOT_H__

#include "gun/ShotMethod.h"
#include "gun/Gun.h"

class StrafeShotMethod : public ShotMethod
{
public:
	virtual void shot(Gun* gun);
	static StrafeShotMethod* create(CCPoint& relativePos, float angleRangeDegree, float periodCount);

protected:
	bool init(CCPoint& relativePos, float angleRangeDegree, int periodCount);
	StrafeShotMethod();

private:
	CCPoint relativePos;
	float angleRangeDegree;
	int periodCount;

	float currentAngle;
	float angleStep;

};

#endif
