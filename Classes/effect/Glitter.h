
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

#ifndef __GLITTER_H__
#define __GLITTER_H__


#include "ccMacros.h"

#include "engine/action/CCRandTextureCoord.h"
#include "CocoStudio/Action/CCActionEaseEx.h"

#include "AppMacros.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Glitter : public CCNode
{
public:
	CREATE_FUNC(Glitter);

	bool init()
	{
		// create sprite
		CCSpriteExt* sprite = CCSpriteExt::create("png/glitter.png");
		addChild(sprite);

		float scaleY = 4;
		float scaleX = 0.8;

		sprite->setColor(ccc3(255,255,255*0.7));
		sprite->setScaleY(scaleY);
		sprite->setScaleX(0.8);

		float time = 0.6;
		CCArray* actionArray = CCArray::create();
		CCFadeOut* fadeOut = CCFadeOut::create(time);
		CCScaleTo* scaleXAction = CCScaleTo::create(time, 0, scaleY);
		CCEaseQuadraticActionOut* quadraticScale = CCEaseQuadraticActionOut::create(scaleXAction);
		CCMoveBy* moveBy = CCMoveBy::create(time, ccp(0,-200));

		actionArray->addObject(fadeOut);
		// actionArray->addObject(scaleX);
		actionArray->addObject(quadraticScale);
		actionArray->addObject(moveBy);

		CCSpawn* spawn = CCSpawn::create(actionArray);
		CCTargetedAction* targetedSpawn = CCTargetedAction::create(sprite, spawn);

		CCRemoveSelf* remove = CCRemoveSelf::create();
		CCSequence* finalSeq = CCSequence::createWithTwoActions(targetedSpawn, remove);

		sprite->runAction(finalSeq);

		return true;
	}
};


#endif // !__EXPLOSION_H__



