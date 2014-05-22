
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

#include "TestAutoTiledMap.h"
#include "map/AutoTiledBackground.h"

//#include <stdlib.h>
//#include "engine/physics/GB2ShapeCache-x.h"
//#include "engine/xfl/XflParser.h"
//#include "map/Map.h"
//#include "engine/physics/PhysicsManager.h"

USING_NS_CC;

CCScene* TestAutoTiledMap::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestAutoTiledMap *layer = TestAutoTiledMap::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestAutoTiledMap::init()
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
	title->setString("Test Auto Tiled Map");
	title->setPosition(ccp(center.x, top - 50 ));
	addChild(title);

	//AutoTiledBackground* bg = AutoTiledBackground::create("png/ground/soil_dark_gravel_01_d.png");
	//AutoTiledBackground* bg = AutoTiledBackground::create("png/ground/gld01.png");
	//AutoTiledBackground* bg = AutoTiledBackground::create("png/ground/dirt.jpg");
	//AutoTiledBackground* bg = AutoTiledBackground::create("png/ground/084.jpg");
	//AutoTiledBackground* bg = AutoTiledBackground::create("png/ground/060.jpg");
	//AutoTiledBackground* bg = AutoTiledBackground::create("png/ground/011.jpg");
	AutoTiledBackground* bg = AutoTiledBackground::create("png/ground/012.png");
	if(bg) addChild(bg);

	// move action
	float time = 1;
	CCMoveBy* move = CCMoveBy::create(time, ccp(0,-40));
	CCRepeatForever* repeat = CCRepeatForever::create(move);
	if(bg) bg->runAction(repeat);

	return true;
}
