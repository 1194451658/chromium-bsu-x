
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

#include "TestEnterScreenTrigger.h"
#include <stdlib.h>


CCScene* TestEnterScreenTrigger::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestEnterScreenTrigger *layer = TestEnterScreenTrigger::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestEnterScreenTrigger::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	float top = origin.y + visibleSize.height;
	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	// ----------
	// init graphics
	// ------------


	// -----
	// title
	// -------
	CCLabelTTF* title = CCLabelTTF::create();
	title->setString("Test Trigger");
	title->setPosition(ccp(center.x, top - 50 ));
	addChild(title);

	//// ---------
	//// init xfl parser
	//// ----------------
	//XflParser::sharedInstance()->initialLoad();



	//Map* map = Map::create();




	return true;
}
