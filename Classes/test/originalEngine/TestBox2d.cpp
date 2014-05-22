
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

#include "TestBox2d.h"
#include "engine/physics/PhysicsManager.h"
#include <stdlib.h>

#include "cocos-ext.h"


USING_NS_CC_EXT;

USING_NS_CC;

#define PTM_RATIO  32.0

CCScene* TestBox2d::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestBox2d *layer = TestBox2d::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestBox2d::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	testShapeCenter();

	return true;
}

void TestBox2d::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}

void TestBox2d::testShapeCenter()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	// center indicator
	CCLayerColor* centerIndicator = CCLayerColor::create(ccc4(255,0,0,100));
	centerIndicator->changeWidthAndHeight(100,100);
	centerIndicator->setPosition(center);
	addChild(centerIndicator);

	// -------------
	// init physics
	// -----------
	PhysicsManager::sharedInstance()->enableDebugDraw(true);

	// step
	schedule(schedule_selector(TestBox2d::stepForPhysicsManager));

	b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();


	// create dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(center.x/PTM_RATIO, center.y/PTM_RATIO);
	// bodyDef.angle = 3.14/4;
	b2Body* body = world->CreateBody(&bodyDef);


	{
		// create fixture
		b2PolygonShape shape;
		b2Vec2 center(-40/PTM_RATIO, -40/PTM_RATIO);
		shape.SetAsBox(40.0/PTM_RATIO, 40.0/PTM_RATIO, center, 0);
		body->CreateFixture(&shape, 0);
	}

	//{
	//	// create fixture
	//	b2PolygonShape shape;
	//	b2Vec2 center(40/PTM_RATIO, 0/PTM_RATIO);
	//	shape.SetAsBox(40.0/PTM_RATIO, 40.0/PTM_RATIO, center, 0);
	//	body->CreateFixture(&shape, 1);
	//}
}