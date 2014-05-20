
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

#include "TestPhysicsManager.h"

#include "test/engine/TestKeyUpDown.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

#include "aircraft/Aircraft.h"
#include "input/InputManager.h"

#include "physics/GB2ShapeCache-x.h"
#include "physics/GLES-Render.h"

#include "physics/PhysicsManager.h"

#include "SimpleAudioEngine.h"

#include <stdlib.h>

#include "cocos-ext.h"

#include "map/AutoTiledBackground.h"

#include "engine/CCDrawGameObjectShadowNode.h"

#include "GameController.h"

USING_NS_CC_EXT;

USING_NS_CC;
using namespace CocosDenshion;

#define PTM_RATIO  32

CCScene* TestPhysicsManager::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestPhysicsManager *layer = TestPhysicsManager::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestPhysicsManager::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// ------------
	// init input manager
	// ---------------
	InputManager* input = InputManager::sharedInstance();
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(input);

	// -------------
	// init physics
	// -----------
	PhysicsManager::sharedInstance()->enableDebugDraw(true);
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("png/physics.plist");

	// step
	schedule(schedule_selector(TestPhysicsManager::stepForPhysicsManager));


	// -----------------
	// Init Audio
	// ------------
	SimpleAudioEngine::sharedEngine()->preloadEffect("wav/exploStd.wav");


	// ------------
	// Hero Aircraft
	// -----------
	Aircraft* hero = Aircraft::createHeroAircraft();
	addChild(hero);

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	hero->setPosition(screenSize.width/2, screenSize.height/2);

	GameController::sharedInstance()->setPlayerAircraft(hero);

	//// -------------
	//// Enemy Aircraft
	//// ------------
	//Aircraft* enemy = Aircraft::createEnemyAircraft01();
	//addChild(enemy); 
	//shadowLayer->addGameObject(enemy);
	//enemy->setPosition(screenSize.width/2, screenSize.height/2 + 150);

	// enemy boss
	Aircraft* boss = Aircraft::createBoss00();
	addChild(boss);
	boss->setPosition(screenSize.width/2, screenSize.height/2 + 150);



	return true;
}

void TestPhysicsManager::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}