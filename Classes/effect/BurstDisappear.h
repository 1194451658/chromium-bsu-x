
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

#ifndef __BURST_DISAPPEAR_H__
#define __BURST_DISAPPEAR_H__


#include "ccMacros.h"

#include "engine/action/CCRandomRotateBy.h"
#include "AppMacros.h"

USING_NS_CC;

class BurstDisappear : public CCNode
{
public:
	CREATE_FUNC(BurstDisappear);

	bool init(int number = 4, int numberVar = 2, float x = 0, float xVar = 20, float y = 0, float yVar = 20)
	{
		// sprite
		CCSpriteExt* sprite1 = CCSpriteExt::create("png/powerUpTex.png");
		this->addChild(sprite1);

		CCSpriteExt* sprite2 = CCSpriteExt::create("png/powerUpTex.png");
		this->addChild((sprite2));

		CCArray* actionArray = CCArray::create();
		CCTargetedAction* sprite1Action = createAction(sprite1);
		CCTargetedAction* sprite2Action = createAction(sprite2);
		CCSpawn* twoSpriteAction = CCSpawn::createWithTwoActions(sprite1Action, sprite2Action);
		CCRemoveSelf* remove = CCRemoveSelf::create();

		//actionArray->addObject(sprite1Action);
		//actionArray->addObject(sprite2Action);
		actionArray->addObject(twoSpriteAction);
		actionArray->addObject(remove);
		CCSequence* seq = CCSequence::create(actionArray);

		this->runAction(seq);
		return true;
	}

	CCTargetedAction* createAction(CCSpriteExt* sprite)
	{
		CCArray* actions = CCArray::create();

		// init action
		CCArray* initialActions = CCArray::create();
		CCTintTo* tint = CCTintTo::create(0, 255, 255*0.95, 255*0.85);
		CCFadeTo* fade = CCFadeTo::create(0, 255*0.75);
		initialActions->addObject(tint);
		initialActions->addObject(fade);
		CCSpawn* spawn = CCSpawn::create(initialActions);
		actions->addObject(spawn);

		// target action
		{
			float time = 2;
			CCArray* targetActions = CCArray::create();
			CCScaleTo* scale = CCScaleTo::create(time, 0);
			CCTintTo* tint = CCTintTo::create(time, 255*0.5, 255*0.2, 255*0.1);
			CCFadeTo* fade = CCFadeTo::create(time, 0);
			CCRandomRotateBy* rotate = CCRandomRotateBy::create(time, 360);
			targetActions->addObject(scale);
			targetActions->addObject(tint);
			targetActions->addObject(fade);
			targetActions->addObject(rotate);
			CCSpawn* spawn = CCSpawn::create(targetActions);
			actions->addObject(spawn);
		}

		// seq
		CCSequence* seq = CCSequence::create(actions);
		CCTargetedAction* targetedSeq = CCTargetedAction::create(sprite, seq);

		return targetedSeq;
	}
};

#endif // !__EXPLOSION_H__



