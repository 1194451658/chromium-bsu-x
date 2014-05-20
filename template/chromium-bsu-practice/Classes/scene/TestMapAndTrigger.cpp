
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

#include "TestMapAndTrigger.h"

#include <stdlib.h>
#include "physics/GB2ShapeCache-x.h"

#include "engine/xfl/XflParser.h"
#include "map/Map.h"
#include "physics/PhysicsManager.h"

USING_NS_CC;

CCScene* TestMapAndTrigger::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestMapAndTrigger *layer = TestMapAndTrigger::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestMapAndTrigger::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}


	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float top = origin.y + visibleSize.height;
	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	// -----
	// title
	// -------
	CCLabelTTF* title = CCLabelTTF::create();
	title->setString("Test Map And Trigger");
	title->setPosition(ccp(center.x, top - 50 ));
	addChild(title);

	// ---------
	// init xfl parser
	// ----------------
	XflParser::sharedInstance()->initialLoad();

	// ----------
	// init physics
	// ------------
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("png/physics.plist");
	// PhysicsManager::sharedInstance()->enableDebugDraw(true);
	PhysicsManager::sharedInstance()->createScreenCollider();
	schedule(schedule_selector(TestMapAndTrigger::stepForPhysicsManager));

	// --------------
	// create map
	// ------------

	map<string, tinyxml2::XMLDocument*>::iterator mapDef = XflParser::sharedInstance()->mapDefs.find("map/testMap.xml");

	if(mapDef != XflParser::sharedInstance()->mapDefs.end())
	{
			Map* map = Map::create(mapDef->second);
			CCSize contentSize = map->getContentSize();
			map->setPosition(ccp(0,contentSize.height));
			addChild(map);

			//// move action
			//float time = 30;
			//CCMoveTo* move = CCMoveTo::create(time, ccp(0,0));
			//map->runAction(move);
	}

	return true;
}

void TestMapAndTrigger::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}

