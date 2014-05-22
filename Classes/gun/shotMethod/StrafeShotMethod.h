
// Copyright 2014 Wanwan Zhang

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __STRAFE_LATERAL_SHOT_H__
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
