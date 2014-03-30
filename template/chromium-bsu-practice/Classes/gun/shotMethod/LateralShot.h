
#ifndef __LATERAL_SHOT_H__
#define __LATERAL_SHOT_H__

#include "gun/ShotMethod.h"
#include "gun/Gun.h"

class LateralShotMethod : public ShotMethod
{
public:
	virtual void shot(Gun* gun);
	static LateralShotMethod* create(CCPoint& relativePos);

protected:
	bool init(CCPoint& relativePos);
	LateralShotMethod();

private:
	CCPoint relativePos;
};

#endif
