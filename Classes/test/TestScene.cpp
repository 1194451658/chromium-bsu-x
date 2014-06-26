
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

#include "TestScene.h"
#include "TestMapAndTrigger.h"

USING_NS_CC_EXT;
USING_NS_CC;


CCScene* TestScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestScene *layer = TestScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	// ------------
	// create menu
	// -------------
	CCMenu* menu = CCMenu::create();

	// lateral
	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("Test Map And Trigger Scene", this, menu_selector(TestScene::menuItemCallback));
		menu->addChild(menuItem);
	}

	menu->alignItemsVertically();
	addChild(menu);

	menu->setPositionX(menu->getPositionX() + 200);

	return true;
}

void TestScene::menuItemCallback(CCObject* menuItem)
{
	CCMenuItemLabel* menuItemLabel = dynamic_cast<CCMenuItemLabel*>(menuItem);

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	if(menuItemLabel)
	{
		CCLabelTTF* label = dynamic_cast<CCLabelTTF*>(menuItemLabel->getLabel());

		if(!label)
			return;

		string labelString = label->getString();

		if(labelString == "Test Map And Trigger Scene")
		{
			CCDirector::sharedDirector()->pushScene(TestMapAndTrigger::scene());
		}
	}
}
