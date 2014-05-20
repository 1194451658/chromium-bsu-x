
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

#include "TestShotMethod.h"

#include "test/engine/TestKeyUpDown.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

#include "aircraft/Aircraft.h"
#include "engine/input/InputManager.h"

#include "engine/physics/GB2ShapeCache-x.h"
#include "engine/physics/GLES-Render.h"

#include "engine/physics/PhysicsManager.h"

#include "SimpleAudioEngine.h"

#include <stdlib.h>

#include "cocos-ext.h"

#include "map/AutoTiledBackground.h"

#include "engine/CCDrawGameObjectShadowNode.h"

#include "GameController.h"

#include "gun/shotMethod/LateralShotMethod.h"
#include "gun/shotMethod/MiddleShotMethod.h"
#include "gun/shotMethod/SineShotMethod.h"
#include "gun/shotMethod/StrafeShotMethod.h"
#include "gun/shotMethod/SwapLateralShotMethod.h"
#include "gun/shotMethod/TargetHeroShotMethod.h"


USING_NS_CC_EXT;

USING_NS_CC;
using namespace CocosDenshion;

#define PTM_RATIO  32

CCScene* TestShotMethod::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestShotMethod *layer = TestShotMethod::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestShotMethod::init()
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
	schedule(schedule_selector(TestShotMethod::stepForPhysicsManager));

	// -----------------
	// Init Audio
	// ------------
	SimpleAudioEngine::sharedEngine()->preloadEffect("wav/exploStd.wav");

	// ------------
	// Hero Aircraft
	// -----------
	Aircraft* hero = Aircraft::createHeroAircraft();
	addChild(hero);
	hero->setDebugUnDestoryable(true);

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	hero->setPosition(screenSize.width/2, screenSize.height/2);

	GameController::sharedInstance()->setPlayerAircraft(hero);

	// ------------
	// create menu
	// -------------
	CCMenu* menu = CCMenu::create();

	// lateral
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("lateral shot method", this, menu_selector(TestShotMethod::menuItemCallback));
		menu->addChild(menuItem);
	}

	// middle 
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("middle shot method", this, menu_selector(TestShotMethod::menuItemCallback));
		menu->addChild(menuItem);
	}

	// sine
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("sine shot method", this, menu_selector(TestShotMethod::menuItemCallback));
		menu->addChild(menuItem);
	}

	// strafe
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("strafe shot method", this, menu_selector(TestShotMethod::menuItemCallback));
		menu->addChild(menuItem);
	}

	// swap
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("swap lateral shot method", this, menu_selector(TestShotMethod::menuItemCallback));
		menu->addChild(menuItem);
	}

	// target hero
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("target hero method", this, menu_selector(TestShotMethod::menuItemCallback));
		menu->addChild(menuItem);
	}

	menu->alignItemsVertically();
	addChild(menu);

	menu->setPositionX(menu->getPositionX() + 200);

	return true;
}

void TestShotMethod::menuItemCallback(CCObject* menuItem)
{
	CCMenuItemLabel* menuItemLabel = dynamic_cast<CCMenuItemLabel*>(menuItem);

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	if(menuItemLabel)
	{
		CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(menuItemLabel->getLabel());

		if(!label)
			return;

		string labelString = label->getString();

		Gun* heroGun = GameController::sharedInstance()->getPlayerAircraft()->getDefaultGun();

		if(labelString == "lateral shot method")
		{
			if(heroGun)
			{
				CCPoint pos = ccp(30, 10);
				LateralShotMethod* shotMethod = LateralShotMethod::create(pos);
				heroGun->setShotMethod(shotMethod);
			}
		}
		else if(labelString == "middle shot method")
		{
			if(heroGun)
			{
				CCPoint pos = ccp(0, 10);
				MiddleShotMethod* shotMethod = MiddleShotMethod::create(pos);
				heroGun->setShotMethod(shotMethod);
			}
		}
		else if(labelString == "sine shot method")
		{
			if(heroGun)
			{
				CCPoint pos = ccp(30, 10);
				SineShotMethod* shotMethod = SineShotMethod::create(pos, 5);
				heroGun->setShotMethod(shotMethod);
			}
		}
		else if(labelString == "strafe shot method")
		{
			if(heroGun)
			{
				CCPoint pos = ccp(0, 10);
				StrafeShotMethod* shotMethod = StrafeShotMethod::create(pos,45,20);
				heroGun->setShotMethod(shotMethod);
			}
		}

		else if(labelString == "swap lateral shot method")
		{
			if(heroGun)
			{
				CCPoint pos = ccp(30, 10);
				SwapLateralShotMethod* shotMethod = SwapLateralShotMethod::create(pos);
				heroGun->setShotMethod(shotMethod);
			}
		}
		else if(labelString == "target hero method")
		{
			// add enemy
			Aircraft* enemy = Aircraft::createEnemyOmni();
			addChild(enemy);
			enemy->setPosition(screenSize.width/2, screenSize.height/2+ 200);
		}
	}
}

void TestShotMethod::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}

void TestShotMethod::draw()
{
	CCLayer::draw();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();
	b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();
	world->DrawDebugData();
	kmGLPopMatrix();
}
