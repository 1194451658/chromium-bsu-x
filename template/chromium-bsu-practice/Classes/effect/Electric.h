
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

#ifndef __ELECTRIC_H__
#define __ELECTRIC_H__

#include "cocos2d.h"
#include "ccMacros.h"

#include "engine/action/CCRandTextureCoord.h"

USING_NS_CC;

class Electric : public CCNode
{
public:
	CREATE_FUNC(Electric);

	bool init()
	{
		// create sprite
		CCSprite* sprite = CCSprite::create("png/electric.png");
		addChild(sprite);

		// create action
		CCRandTextureCoord* randTex = CCRandTextureCoord::create(2.0, 6);
		CCRepeatForever* repeat = CCRepeatForever::create(randTex);

		sprite->runAction(repeat);
		
		return true;
	}
};


#endif // !__EXPLOSION_H__



