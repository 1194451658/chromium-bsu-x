
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

#include "TestAircraft.h"

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

CCScene* TestAircraft::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestAircraft *layer = TestAircraft::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestAircraft::init()
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
	schedule(schedule_selector(TestAircraft::stepForPhysicsManager));

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

	// ------------
	// create menu
	// -------------
	CCMenu* menu = CCMenu::create();

	// straight menu item
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("straight", this, menu_selector(TestAircraft::menuItemCallback));
		menu->addChild(menuItem);
	}

	// omni 
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("omni", this, menu_selector(TestAircraft::menuItemCallback));
		menu->addChild(menuItem);
	}

	// ray gun 
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("ray gun", this, menu_selector(TestAircraft::menuItemCallback));
		menu->addChild(menuItem);
	}

	// tank
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("tank", this, menu_selector(TestAircraft::menuItemCallback));
		menu->addChild(menuItem);
	}

	// boss00
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("boss00", this, menu_selector(TestAircraft::menuItemCallback));
		menu->addChild(menuItem);
	}

	// boss01
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("boss01", this, menu_selector(TestAircraft::menuItemCallback));
		menu->addChild(menuItem);
	}

	// hero
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("hero", this, menu_selector(TestAircraft::menuItemCallback));
		menu->addChild(menuItem);
	}

	menu->alignItemsVertically();
	addChild(menu);

	menu->setPositionX(menu->getPositionX() + 200);



	return true;
}

void TestAircraft::menuItemCallback(CCObject* menuItem)
{
	CCMenuItemLabel* menuItemLabel = dynamic_cast<CCMenuItemLabel*>(menuItem);

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	if(menuItemLabel)
	{
		CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(menuItemLabel->getLabel());

		if(!label)
			return;

		string labelString = label->getString();

		if(labelString == "straight")
		{
			// straight
			{
				Aircraft* enemy = Aircraft::createEnemyStraight();
				addChild(enemy);
				enemy->setPosition(screenSize.width/2, screenSize.height/2 + 150);
			}
		}
		else if(labelString == "omni")
		{
			// enemy omni
			{
				Aircraft* omni = Aircraft::createEnemyOmni();
				addChild(omni);
				omni->setPosition(screenSize.width/2, screenSize.height/2 + 150);
			}
		}
		else if(labelString == "ray gun")
		{
			// ray gun
			{
				Aircraft* enemy = Aircraft::createEnemyRayGun();
				addChild(enemy);
				enemy->setPosition(screenSize.width/2, screenSize.height/2 + 150);
			}
		}
		else if(labelString == "tank")
		{
			// tank
			{
				Aircraft* enemy = Aircraft::createEnemyTank();
				addChild(enemy);
				enemy->setPosition(screenSize.width/2, screenSize.height/2 + 150);
			}
		}

		else if(labelString == "boss00")
		{

			// enemy boss
			Aircraft* boss = Aircraft::createBoss00();
			addChild(boss);
			boss->setPosition(screenSize.width/2, screenSize.height/2 + 150);
		}

		else if(labelString == "boss01")
		{
			// boss 01
			{
				Aircraft* enemy = Aircraft::createBoss01();
				addChild(enemy);
				enemy->setPosition(screenSize.width/2, screenSize.height/2 + 150);
			}
		}

		else if(labelString == "hero")
		{
			Aircraft* hero = Aircraft::createHeroAircraft();
			addChild(hero);
			hero->setPosition(screenSize.width/2, screenSize.height/2);
			GameController::sharedInstance()->setPlayerAircraft(hero);
		}
	}
}

void TestAircraft::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}

void TestAircraft::draw()
{
	CCLayer::draw();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();
	b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();
	// world->DrawDebugData();
	kmGLPopMatrix();
}
