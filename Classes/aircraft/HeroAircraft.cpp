
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


#include "HeroAircraft.h"
#include "engine/input/InputManager.h"
#include "GameController.h"


HeroAircraft* HeroAircraft::create(AircraftDef def)
{
	HeroAircraft* hero = new HeroAircraft();

	if(hero && hero->init(def))
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

HeroAircraft::HeroAircraft()
{
	inUserControl = true;
	boundMoveInScreen = true;
	//gunTriggerd = false;
}

HeroAircraft::~HeroAircraft()
{
	CC_SAFE_RELEASE_NULL(graphics);
}

bool HeroAircraft::init(AircraftDef def)
{
	// init base class
	if(Aircraft::init(def))
	{
		name = "HeroAircraft";

		defaultGun = Gun::createEnemyBoss00Gun1();
		defaultGun->prototypeAmmo->ammoDef.direction = ccp(0,1);
		defaultGun->retain();

		defaultGun->setOwnerAircraft(this);
		addChild(defaultGun);

		return true;
	}

	return false;
}



void HeroAircraft::update(float dt)
{
	Aircraft::update(dt);

	//// move
	//InputManager* input = InputManager::sharedInstance();

	//if(input->arrowState[input->ARROW_UP] == InputManager::ARROW_PRESSED)
	//	setPositionY(getPositionY() + 10);

	//if(input->arrowState[input->ARROW_DOWN] == InputManager::ARROW_PRESSED)
	//	setPositionY(getPositionY() - 10);

	//if(input->arrowState[input->ARROW_LEFT] == InputManager::ARROW_PRESSED)
	//	setPositionX(getPositionX() - 10);

	//if(input->arrowState[input->ARROW_RIGHT] == InputManager::ARROW_PRESSED)
	//	setPositionX(getPositionX() + 10);

	//if(input->arrowState[input->FIRE] == InputManager::ARROW_PRESSED)
	//{
	//	defaultGun->trigger(true);
	//}
	//else
	//{
	//	defaultGun->trigger(false);
	//}

	if(shouldReleased)
	{
		GameController::sharedInstance()->heroDead();
	}

	//if(gunTriggerd)
	//{
	//}
	//defaultGun->trigger(true);
}

void HeroAircraft::playNewLifeAction()
{
	//
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize graphicsSize = graphics->getContentSize();
	float screenCenterX = origin.x + visibleSize.width/2;

	setBoundMoveInScreen(false);
	setInUserControl(false);

	// initial pos
	setPosition(ccp(screenCenterX - 200, -graphicsSize.height));

	// move in action
	float moveFrontTime = 0.3;
	float moveBackTime = 0.5;
	float moveRightTime = moveFrontTime + moveBackTime;
	CCMoveTo* moveFront = CCMoveTo::create(moveFrontTime, ccp(screenCenterX - 100, graphicsSize.height*4));
	CCMoveTo* moveBack = CCMoveTo::create(moveBackTime, ccp(screenCenterX, graphicsSize.height*3));

	CCSequence* moveFrontBackSeq = CCSequence::createWithTwoActions(moveFront, moveBack);
	CCDelayTime* delay = CCDelayTime::create(0.3);
	CCCallFunc* finishCallback = CCCallFunc::create(this, SEL_CallFunc(&HeroAircraft::newLifeCallFuncSelector));

	
	CCSequence* finalSeq = CCSequence::create(moveFrontBackSeq, delay, finishCallback, NULL);
	runAction(finalSeq);
}

void HeroAircraft::newLifeCallFuncSelector()
{
	setBoundMoveInScreen(true);
	setInUserControl(true);
	if(defaultGun) defaultGun->trigger(true);
}
