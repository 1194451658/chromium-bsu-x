
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

#ifndef __CCRANDOMROTATEBY_H__
#define __CCRANDOMROTATEBY_H__

#include "AppMacros.h"

USING_NS_CC;

class CCRandomRotateBy : public CCActionInterval
{
public:

	static CCRandomRotateBy* create(float duration, float angleVar)
	{
		CCRandomRotateBy* seq = new CCRandomRotateBy();
		if(seq && seq->initWithDuration(duration, angleVar))
		{

			seq->autorelease();
			return seq;
		}

		return NULL;
	}


	bool initWithDuration(float duration, float angleVar)
	{
		if(CCActionInterval::initWithDuration(duration))
		{
			this->angleVar = angleVar;
			return true;
		}

		return false;
	}

	void update(float time)
	{
		float angle = CCRANDOM_MINUS1_1() * angleVar;
		this->m_pTarget->setRotation(angle);
	}

private:
	float angleVar;
};

#endif



