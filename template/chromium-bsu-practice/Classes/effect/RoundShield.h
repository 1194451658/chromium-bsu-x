

#ifndef __ROUND_SHIELD_H__
#define __ROUND_SHIELD_H__

#include "cocos2d.h"
#include "ccMacros.h"

#include "engine/CCRandomRotateBy.h"

USING_NS_CC;

class RoundShield : public CCNode
{
public:
	CREATE_FUNC(RoundShield);

	//static Explositon* create(int number, int numberVar, float x, float xVar, float y, float yVar)
	//{
	//	Explositon* exp = new Explositon();
	//	if(exp->init(number, numberVar, x, xVar, y, yVar))
	//	{
	//		exp->autorelease();
	//		return exp;
	//	}

	//	return NULL;
	//}

	bool init(int number = 4, int numberVar = 2, float x = 0, float xVar = 20, float y = 0, float yVar = 20)
	{
		// create sprite
		CCSprite* shield = CCSprite::create("png/heroShields.png");
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

		// remove
		CCRemoveSelf* remove = CCRemoveSelf::create();
		actionArray->addObject(remove);

		// final seq 
		CCSequence* finalSeq = CCSequence::create(actionArray);
		CCTargetedAction* targetedAction = CCTargetedAction::create(shield, finalSeq);

		// run action
		this->runAction(targetedAction);

		return true;
	}
};

#endif // !__EXPLOSION_H__



