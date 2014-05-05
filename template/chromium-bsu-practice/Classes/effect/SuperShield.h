
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

#ifndef __SUPER_SHIELD_H__
#define __SUPER_SHIELD_H__

#include "cocos2d.h"
#include "ccMacros.h"

#include "engine/action/CCRandomRotateBy.h"

USING_NS_CC;

class SuperShield : public CCNode
{
public:
	CREATE_FUNC(SuperShield);

	bool init()
	{
		// create sprite
		CCSprite* shield = CCSprite::create("png/heroSuper.png");
		addChild(shield);

		// create action
		float time = 2;
		CCRandomRotateBy* randRotate = CCRandomRotateBy::create(time, 360);
		CCRepeatForever* repeat = CCRepeatForever::create(randRotate);
		shield->runAction(repeat);

		// create glitter emitter
		{
			GlitterEmitter* emitter = GlitterEmitter::create();
			emitter->setPositionX(-20);
			addChild(emitter);
		}

		// create glitter emitter
		{
			GlitterEmitter* emitter = GlitterEmitter::create();
			emitter->setPositionX(20);
			addChild(emitter);
		}

		return true;
	}
};


#endif // !__EXPLOSION_H__



