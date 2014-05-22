
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

#ifndef __CC_RAND_TEXTURE_FOR_AMMO_H__
#define __CC_RAND_TEXTURE_FOR_AMMO_H__

#include "AppMacros.h"

USING_NS_CC;

class CCRandTextureForAmmo : public CCActionInterval
{
public:

	static CCRandTextureForAmmo* create(float duration)
	{
		CCRandTextureForAmmo* seq = new CCRandTextureForAmmo();
		if(seq && seq->initWithDuration(duration))
		{
			seq->iterateNumber = 0;
			seq->autorelease();
			return seq;
		}

		return NULL;
	}

	void update(float time)
	{

		iterateNumber ++;

		//
		CCSpriteExt* target = dynamic_cast<CCSpriteExt*>(m_pTarget);

		CCRect newRect;

		if(target)
		{
			CCRect rect = target->getTextureRect();

			switch(iterateNumber%4)
			{
			case 0:
				newRect.setRect(rect.getMinX(), rect.getMaxY(),
							rect.getMaxX() - rect.getMinX() ,
							-(rect.getMaxY() - rect.getMinY()));
				break;
			case 1:
				newRect.setRect(rect.getMaxX(), rect.getMaxY(), 
							-(rect.getMaxY() - rect.getMinY()), 
							-(rect.getMaxX() - rect.getMinX()));
				break;
			case 2:
				newRect = rect; 
				break;
			case 3:
				newRect.setRect(rect.getMaxX(), rect.getMinY(), 
							-(rect.getMaxX() - rect.getMinX()), 
							rect.getMaxY() - rect.getMinY());
				break;
			}

			target->setTextureCoords(newRect);
		}
	}

private:
	int iterateNumber;
};

#endif



