
#ifndef __MIDDLE_SHOT_H__
#define __MIDDLE_SHOT_H__

#include "gun/ShotMethod.h"
#include "gun/Gun.h"

class MiddleShotMethod : public ShotMethod
{
public:
	virtual void shot(Gun* gun);
	static MiddleShotMethod* create(CCPoint& relativePos);

protected:
	bool init(CCPoint& relativePos);
	MiddleShotMethod();

private:
	CCPoint relativePos;
};

#endif
