
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

#include "TestCleanUp.h"
#include "map/AutoTiledBackground.h"

//#include <stdlib.h>
//#include "engine/physics/GB2ShapeCache-x.h"
//#include "engine/xfl/XflParser.h"
//#include "map/Map.h"
//#include "engine/physics/PhysicsManager.h"

USING_NS_CC;

CCScene* TestCleanUp::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestCleanUp *layer = TestCleanUp::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestCleanUp::init()
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
	title->setString("Test Clean Up");
	title->setPosition(ccp(center.x, top - 50 ));
	addChild(title);

	{
			CCLayerColor* sprite = CCLayerColor::create(ccc4(255,0,0,255));
			sprite->changeWidthAndHeight(100, 100);

			CCMoveBy* move = CCMoveBy::create(100, ccp(0,0));
			sprite->runAction(move);
			// check if has memory leak
	}




	return true;
}
