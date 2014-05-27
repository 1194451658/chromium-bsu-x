
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
#include "engine/CCDrawGameObjectShadowNode.h"
#include "aircraft/Aircraft.h"
#include "GameController.h"

#include "engine/input/TouchInputLayer.h"
#include "engine/base_nodes/ReverseZOrderNode.h"

USING_NS_CC;


cocos2d::CCScene* ReplayTransitionScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	ReplayTransitionScene *layer = ReplayTransitionScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


void ReplayTransitionScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	scheduleUpdate();
}

void ReplayTransitionScene::update(float delta)
{
	unscheduleUpdate();
	float time = 0.5;
	GameScene* gs = GameScene::create();
	CCTransitionProgressVertical* transitionScene = CCTransitionProgressVertical::create(0.5, gs);
	CCDirector::sharedDirector()->replaceScene(transitionScene);
}

GameScene::GameScene()
{
	lifeLabel = NULL;
}

GameScene::~GameScene()
{
	CC_SAFE_RELEASE_NULL(lifeLabel);
	PhysicsManager::sharedInstance()->resetAll();
	GameController::sharedInstance()->resetAll();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if ( !CCScene::init() )
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
	//PhysicsManager::sharedInstance()->enableDebugDraw(true);
	PhysicsManager::sharedInstance()->createScreenCollider();
	schedule(schedule_selector(GameScene::stepForPhysicsManager));

	// --------
	// new game
	// ----------
	GameController::sharedInstance()->newGame();

	// -----------------------------------
	// create map && background layer
	// --------------------------
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

	// -----------------
	// create draw shadow layer
	// ---------------------
	CCDrawGameObjectShadowNode* shadowLayer = CCDrawGameObjectShadowNode::create();
	GameController::sharedInstance()->setDrawShadowLayer(shadowLayer);
	addChild(shadowLayer);

	// ----------------------
	// create aircraft layer
	// -----------------------
	CCNode* aircraftLayer = CCNode::create();
	GameController::sharedInstance()->setAircraftLayer(aircraftLayer);
	addChild(aircraftLayer);

	// ----------------------
	// create explosion layer
	// -----------------------
	ReverseZOrderNode* explosionLayer = ReverseZOrderNode::create();
	GameController::sharedInstance()->setExplosionLayer(explosionLayer);
	addChild(explosionLayer);

	// ----------------------
	// create touch input layer
	// ------------------------
	TouchInputLayer* inputLayer = TouchInputLayer::create();
	addChild(inputLayer);

	// -------------------
	// create HUD
	// ------------------
	createHUD();

	// ------------  
	// Hero Aircraft
	// -----------
	GameController::sharedInstance()->createHero();

	// schedule update
	scheduleUpdate();

	//// test game over
	//gameOver();

	return true;
}

void GameScene::createHUD()
{
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	// left up corner, life display
	CCSprite* heroSprite = CCSprite::create("png/airCraft/hero.png");
	lifeLabel = CCLabelTTF::create();
	lifeLabel->retain();
	lifeLabel->setString("x 999");
	lifeLabel->setFontSize(40);

	CCNode* node = CCNode::create();
	node->addChild(heroSprite);
	node->addChild(lifeLabel);

	float horInterval = 20;
	heroSprite->setAnchorPoint(ccp(0,1));
	lifeLabel->setAnchorPoint(ccp(0,1));
	lifeLabel->setPosition(ccp(heroSprite->getContentSize().width + horInterval, -(heroSprite->getContentSize().height - lifeLabel->getContentSize().height)/2));

	addChild(node);
	node->setPosition(ccp(origin.x, origin.y + visibleSize.height));

	// manual update
	updateHUD();
}

void GameScene::update(float delta)
{
	updateHUD();
}

void GameScene::updateHUD()
{
	if(lifeLabel)
	{
		// get left life
		int life = GameController::sharedInstance()->getHeroLife();
		stringstream toString;
		toString<<"x "<<life;
		lifeLabel->setString(toString.str().c_str());
	}
}

void GameScene::gameOver()
{
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	// create menu layer

	CCNode* layer = CCNode::create();

	CCLabelTTF* loseLabel = CCLabelTTF::create();
	loseLabel->setString("You Lose !");
	loseLabel->setFontSize(60);
	loseLabel->setPosition(ccp(origin.x + size.width/2, origin.y + size.height/2 + 50));
	addChild(loseLabel);

	// create replay menu
	CCMenuItemFont* menuItem = CCMenuItemFont::create("Click To Play Again !", this, SEL_MenuHandler(&GameScene::replayMenuHandler));
	CCMenu* menu = CCMenu::create(menuItem, NULL);
	// menu->addChild(menuItem);
	addChild(menu);
}

void GameScene::replayMenuHandler(CCObject* obj)
{
	float time = 0.5;
	 CCScene* replayScene = ReplayTransitionScene::scene();
	//CCScene* replayScene = GameScene::scene();
	CCTransitionProgressVertical* transitionScene = CCTransitionProgressVertical::create(0.5, replayScene);
	CCDirector::sharedDirector()->replaceScene(transitionScene);

	//CCScene* newScene = GameScene::scene();
	//CCDirector::sharedDirector()->replaceScene(newScene);
}

void GameScene::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}

