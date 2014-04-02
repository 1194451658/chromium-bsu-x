
#ifndef __SWAP_LATERAL_SHOT_H__
#define __SWAP_LATERAL_SHOT_H__

#include "gun/ShotMethod.h"
#include "gun/Gun.h"

class SwapLateralShotMethod : public ShotMethod
{
public:
	virtual void shot(Gun* gun);
	static SwapLateralShotMethod* create(CCPoint& relativePos);

protected:
	bool init(CCPoint& relativePos);
	SwapLateralShotMethod();

private:
	bool swapFlag;
	CCPoint relativePos;
};

#endif
