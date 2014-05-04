#include "TestEffect.h"

#include "test/engine/TestKeyUpDown.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"

#include "aircraft/HeroAircraft.h"
#include "input/InputManager.h"

#include "physics/GB2ShapeCache-x.h"
#include "physics/GLES-Render.h"

#include "physics/PhysicsManager.h"
#include "aircraft/EnemyAircraft0.h"

#include "SimpleAudioEngine.h"

#include <stdlib.h>

#include "cocos-ext.h"

#include "map/AutoTiledBackground.h"

#include "engine/CCDrawGameObjectShadowNode.h"

#include "effect/Explosion.h"
#include "effect/RoundShield.h"
#include "effect/BurstDisappear.h"

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

	{
		// menu play shield effect
		CCLabelTTF* label = CCLabelTTF::create();
		label->setString("replay Burst disappear");
		CCMenuItemLabel* item = CCMenuItemLabel::create(label, this, menu_selector(TestEffectScene::playBurstDisappear));
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

	BurstDisappear* burst = BurstDisappear::create();
	addChild(burst);

	burst->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}

void TestEffectScene::playBurstDisappear(CCObject* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	RoundShield* effect = RoundShield::create();
	addChild(effect);

	effect->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
}
