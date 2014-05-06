
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


#include "TestEffect.h"
#include "test/engine/TestKeyUpDown.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "aircraft/HeroAircraft.h"
#include "input/InputManager.h"
#include "physics/GB2ShapeCache-x.h"
#include "physics/GLES-Render.h"
#include "physics/PhysicsManager.h"
#include "SimpleAudioEngine.h"
#include <stdlib.h>
#include "cocos-ext.h"
#include "map/AutoTiledBackground.h"
#include "engine/CCDrawGameObjectShadowNode.h"
#include "effect/Explosion.h"
#include "effect/RoundShield.h"
#include "effect/BurstDisappear.h"
#include "effect/Electric.h"
#include "effect/Glitter.h"
#include "effect/GlitterEmitter.h"
#include "effect/SuperShield.h"
#include "effect/SuperBomb.h"

USING_NS_CC_EXT;

USING_NS_CC;
using namespace CocosDenshion;

#define PTM_RATIO  32

CCScene* TestEffectScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestEffectScene *layer = TestEffectScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestEffectScene::init()
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
		menu_selector(TestEffectScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y + pCloseItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);


	// hello world label
	CCLabelTTF* pLabel = CCLabelTTF::create("Test Effect ", "Arial", 24);
	pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	// CCSprite* pSprite = CCSprite::create("HelloWorld.png");
	// pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	// this->addChild(pSprite, 0);

	testExplosion();


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("png/airCraft/aircrafts.plist");

	//CCSprite* testAir = CCSprite::createWithSpriteFrameName("enemy03.png");
	//testAir->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	//CCRect textureSize = testAir->getTextureRect();
	//testAir->setTextureRect(textureSize, true, textureSize.size);
	//addChild(testAir);

	return true;
}

void TestEffectScene::menuCloseCallback(CCObject* pSender)
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

void TestEffectScene::testExplosion()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCMenu* pMenu = CCMenu::create();
	addChild(pMenu);

	{
		// menu play explosion effect
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("replay explosion");
		CCMenuItemLabel* playExplosion = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playEffectCallback));
		pMenu->addChild(playExplosion);
	}

	{
		// menu play shield effect
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("replay shield effect");
		CCMenuItemLabel* playShield = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playShieldCallback));
		pMenu->addChild(playShield);
	}

	// burst disappear
	{
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("replay Burst disappear");
		CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playBurstDisappear));
		pMenu->addChild(item);
	}


	// electric
	{
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("electric");
		CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playElectric));
		pMenu->addChild(item);
	}

	// single glitter
	{
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("single glitter");
		CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playSingleGlitter));
		pMenu->addChild(item);
	}

	// glitter emitter
	{
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("glitter emitter");
		CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playGlitterEmitter));
		pMenu->addChild(item);
	}

	// super shield
	{
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("super shield");
		CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playSuperShield));
		pMenu->addChild(item);
	}

	// super bomb
	{
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("super bomb");
		CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playSuperBomb));
		pMenu->addChild(item);
	}

	pMenu->setPosition(ccp(origin.x + visibleSize.width/2 + 100, origin.y + visibleSize.height/2));
	pMenu->alignItemsVertically();

	return ;
}

void TestEffectScene::playEffectCallback(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	Explositon* ex = Explositon::create();
	addChild(ex);

	ex->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}

void TestEffectScene::playShieldCallback(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	RoundShield* effect = RoundShield::create();
	addChild(effect);

	effect->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}

void TestEffectScene::playBurstDisappear(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	BurstDisappear* burst = BurstDisappear::create();
	addChild(burst);

	burst->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}

void TestEffectScene::playElectric(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	Electric* effect = Electric::create();
	addChild(effect);

	effect->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}

void TestEffectScene::playSingleGlitter(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	Glitter* effect = Glitter::create();
	addChild(effect);

	effect->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}

void TestEffectScene::playGlitterEmitter(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	GlitterEmitter* effect = GlitterEmitter::create();
	addChild(effect);

	effect->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}

void TestEffectScene::playSuperShield(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	SuperShield* shield = SuperShield::create();
	addChild(shield);

	shield->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}

void TestEffectScene::playSuperBomb(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	SuperBomb* bomb = SuperBomb::create();
	addChild(bomb);

	bomb->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}
