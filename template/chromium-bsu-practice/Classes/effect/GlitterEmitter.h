
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

#ifndef __GLITTER_EMITTER_H__
#define __GLITTER_EMITTER_H__

#include "cocos2d.h"
#include "ccMacros.h"

#include "effect/Glitter.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GlitterEmitter : public CCNode
{
public:
	CREATE_FUNC(GlitterEmitter);

	bool init()
	{
		scheduleUpdate();
		return true;
	}

	void update(float delta)
	{
		// create glitter

		static int frameCount = 0;
		frameCount++;

		switch (frameCount%5)
		{
		case 0:
			addGlitter();
			break;
		case 1:
			break;
		case 2:
			addGlitter();
			addGlitter();
			break;
		default:
			break;
		}
	}

	void addGlitter()
	{
		float xVar = 3 * CCRANDOM_MINUS1_1();
		CCNode* parent = this->getParent();
		Glitter* g = Glitter::create();
		g->setPosition(getPosition().x + xVar, getPosition().y);
		parent->addChild(g);
	}
};


#endif // !__EXPLOSION_H__



