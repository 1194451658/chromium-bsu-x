
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

#include "TestArmatureScene.h"

#include "test/engine/TestKeyUpDown.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

#include "aircraft/HeroAircraft.h"
#include "engine/input/InputManager.h"

#include "engine/physics/GB2ShapeCache-x.h"
#include "engine/physics/GLES-Render.h"

#include "engine/physics/PhysicsManager.h"
#include "SimpleAudioEngine.h"

#include <stdlib.h>

#include "cocos-ext.h"

#include "map/AutoTiledBackground.h"

#include "engine/CCDrawGameObjectShadowNode.h"

USING_NS_CC_EXT;

USING_NS_CC;
using namespace CocosDenshion;

#define PTM_RATIO  32

CCScene* TestArmatureScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestArmatureScene *layer = TestArmatureScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestArmatureScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // coordiante indicator
    CCLayerColor* layer = CCLayerColor::create(ccc4(255,0,0,255), 100, 100);
    addChild(layer);

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // close button
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(TestArmatureScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    
    // hello world label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    // CCSpriteExt* pSprite = CCSpriteExt::create("HelloWorld.png");
    // pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // this->addChild(pSprite, 0);

	testDragon();
    
    return true;
}

void TestArmatureScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void TestArmatureScene::testDragon()
{
	// load texture
	// CCTextureCache::sharedTextureCache()->addImage("anim/DragonBones_Tutorial_MultiBehavior_output/DragonBones_Tutorial_MultiBehavior.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("anim/DragonBones_Tutorial_MultiBehavior_output/DragonBones_Tutorial_MultiBehavior.plist");

	// load armature
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("anim/DragonBones_Tutorial_MultiBehavior_output/DragonBones_Tutorial_MultiBehavior.xml");
	CCArmature* armature = CCArmature::create("Dragon");

	addChild(armature);
	armature->getAnimation()->play("stand");

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	armature->setPosition(CCPoint(visibleSize.width/2, 0*visibleSize.height/2));

	return ;
}
