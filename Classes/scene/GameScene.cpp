
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

#include "GameScene.h"

#include <stdlib.h>
#include "engine/physics/GB2ShapeCache-x.h"

#include "engine/xfl/XflParser.h"
#include "map/Map.h"
#include "map/AutoTiledBackground.h"
#include "engine/physics/PhysicsManager.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameScene *layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
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
	title->setString("Game Scene");
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
	schedule(schedule_selector(GameScene::stepForPhysicsManager));

	// --------------
	// create map && background
	// ------------
	CCNode* mapAndGrondLayer = CCNode::create();
	addChild(mapAndGrondLayer);

	float time = 1;
	CCMoveBy* move = CCMoveBy::create(time, ccp(0,-60));
	CCRepeatForever* repeat = CCRepeatForever::create(move);
	mapAndGrondLayer->runAction(repeat);

	// create background
	AutoTiledBackground* background = AutoTiledBackground::create("png/ground/012.png");
	if(background)
		mapAndGrondLayer->addChild(background);

	// create map
	map<string, tinyxml2::XMLDocument*>::iterator mapDef = XflParser::sharedInstance()->mapDefs.find("map/map1.xml");

	if(mapDef != XflParser::sharedInstance()->mapDefs.end())
	{
		Map* map = Map::create(mapDef->second);
		CCSize contentSize = map->getContentSize();
		map->setPosition(ccp(0,contentSize.height));
		mapAndGrondLayer->addChild(map);
	}
	else
	{
		CCLog("GameScene::init Map not created !!");
	}




	return true;
}

void GameScene::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}

