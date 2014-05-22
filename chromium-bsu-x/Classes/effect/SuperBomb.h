
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

#ifndef __SUPER_BOMB_H__
#define __SUPER_BOMB_H__

#include "ccMacros.h"
#include "engine/action/CCRandTextureCoord.h"
#include "AppMacros.h"

USING_NS_CC;

class SuperBomb : public CCNode
{
public:
	CREATE_FUNC(SuperBomb);

	bool init()
	{
		// create sprite
		CCSpriteExt* sprite = CCSpriteExt::create("png/superBomb.png");
		addChild(sprite);

		// create action
		float time = 5;

		CCArray* actionArray = CCArray::create();
		CCRandomRotateBy* randTex = CCRandomRotateBy::create(time, 6);
		CCScaleTo* scale = CCScaleTo::create(time, 5);

		actionArray->addObject(randTex);
		actionArray->addObject(scale);

		CCSpawn* spawn = CCSpawn::create(actionArray);
		CCTargetedAction* targetAction = CCTargetedAction::create(sprite, spawn);

		// remove
		CCRemoveSelf* remove = CCRemoveSelf::create();
		CCSequence* seq = CCSequence::createWithTwoActions(targetAction, remove);
		this->runAction(seq);
		
		//CCRepeatForever* repeat = CCRepeatForever::create(randTex);
		//sprite->runAction(repeat);

		return true;
	}
};


#endif // !__EXPLOSION_H__



