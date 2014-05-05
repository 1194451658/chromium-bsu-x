
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

#ifndef __CC_RAND_TEXTURE_COORD_H__
#define __CC_RAND_TEXTURE_COORD_H__

#include "cocos2d.h"

USING_NS_CC;

class CCRandTextureCoord : public CCActionInterval
{
public:

	static CCRandTextureCoord* create(float duration, float fixedHeight)
	{
		CCRandTextureCoord* seq = new CCRandTextureCoord();
		if(seq && seq->initWithDuration(duration, fixedHeight))
		{
			seq->autorelease();
			return seq;
		}

		return NULL;
	}


	bool initWithDuration(float duration, float fixedHeight)
	{
		if(CCActionInterval::initWithDuration(duration))
		{
			this->fixedHeight = fixedHeight;
			return true;
		}

		return false;
	}

	void update(float time)
	{
		//
		CCSprite* target = dynamic_cast<CCSprite*>(m_pTarget);

		if(target)
		{
			CCRect rect = target->getTextureRect();

			if(rect.getMaxY() - rect.getMinY() < fixedHeight)
			{
				fixedHeight = (rect.getMaxY() - rect.getMinY())/2;
			}

			float randStartHeight = (rect.getMaxY() - rect.getMinY() - fixedHeight) * CCRANDOM_0_1();

			CCRect randRect = CCRectMake(rect.getMinX(), rect.getMinY() + randStartHeight,
										rect.getMaxX() - rect.getMinX(), fixedHeight);

			target->setTextureCoords(randRect);
		}
	}

private:
	float fixedHeight;
};

#endif



