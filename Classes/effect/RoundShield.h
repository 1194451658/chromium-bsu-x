
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

#ifndef __ROUND_SHIELD_H__
#define __ROUND_SHIELD_H__


#include "ccMacros.h"

#include "engine/action/CCRandomRotateBy.h"

#include "AppMacros.h"

USING_NS_CC;

class RoundShield : public CCNode
{
public:
	CREATE_FUNC(RoundShield);

	bool init(int number = 4, int numberVar = 2, float x = 0, float xVar = 20, float y = 0, float yVar = 20)
	{
		// create sprite
		CCSpriteExt* shield = CCSpriteExt::create("png/heroShields.png");
		addChild(shield);

		// action
		CCArray* actionArray = CCArray::create();

		// init spawn
		{
			CCArray* initActions = CCArray::create();
			CCTintTo* tint = CCTintTo::create(0, 255, 255, 255);
			CCFadeTo* fade = CCFadeTo::create(0, 255*0.7);
			initActions->addObject(tint);
			initActions->addObject(fade);

			CCSpawn* initSpawn = CCSpawn::create(initActions);
			actionArray->addObject(initSpawn);
		}


		// follow actions
		{
			float time = 2;
			CCArray* finalActions = CCArray::create();
			CCTintTo* tint = CCTintTo::create(time, 0,0,255);
			CCFadeTo* fade = CCFadeTo::create(time, 0);
			CCRandomRotateBy* rotate = CCRandomRotateBy::create(time, 360);
			CCScaleTo* scale = CCScaleTo::create(time, 0.5);
			finalActions->addObject(tint);
			finalActions->addObject(fade);
			finalActions->addObject(rotate);
			finalActions->addObject(scale);

			CCSpawn* finalSpawn = CCSpawn::create(finalActions);
			actionArray->addObject(finalSpawn);
		}

		// final seq 
		CCSequence* actionSeq = CCSequence::create(actionArray);
		CCTargetedAction* targetedAction = CCTargetedAction::create(shield, actionSeq);

		// remove
		CCRemoveSelf* remove = CCRemoveSelf::create();

		CCSequence* finalSeq = CCSequence::createWithTwoActions(targetedAction, remove);

		// run action
		this->runAction(finalSeq);

		return true;
	}
};

#endif // !__EXPLOSION_H__



