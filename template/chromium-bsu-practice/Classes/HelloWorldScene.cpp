#include "HelloWorldScene.h"

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

USING_NS_CC;
using namespace CocosDenshion;

#define PTM_RATIO  32

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                        menu_selector(HelloWorld::menuCloseCallback));
    
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
    // CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    // pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // this->addChild(pSprite, 0);

    test();
    
    return true;
}
void HelloWorld::test()
{
	// ------------
	// init input manager
	// ---------------
	InputManager* input = InputManager::sharedInstance();
	CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(input);

	// -------------
	// init physics
	// -----------
	b2World* physicsWorld = PhysicsManager::sharedInstance()->getPhysicsWorld();
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("png/physics.plist");

	// step
	schedule(schedule_selector(HelloWorld::stepForPhysicsManager));

	// debug draw
	GLESDebugDraw* debugDraw = new GLESDebugDraw(PTM_RATIO);
	physicsWorld->SetDebugDraw(debugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	// flags += b2Draw::e_aabbBit;
	// flags += b2Draw::e_pairBit;
	// flags += b2Draw::e_centerOfMassBit;
	debugDraw->SetFlags(flags);

	// -----------------
	// Init Audio
	// ------------
	SimpleAudioEngine::sharedEngine()->preloadEffect("wav/exploStd.wav");

	// ------------
	// Hero Aircraft
	// -----------
	HeroAircraft* hero = HeroAircraft::create();
	addChild(hero);

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	hero->setPosition(screenSize.width/2, screenSize.height/2);


	// -------------
	// Enemy Aircraft
	// ------------
	EnemyAircraft0* enemy = EnemyAircraft0::create();
	addChild(enemy);
	enemy->setPosition(screenSize.width/2, screenSize.height/2 + 150);
}

void HelloWorld::testPhysicsEditor()
{
    // CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    // CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


    // -----------------
    // physics world
    // ----------------

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("png/physics.plist");

    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);

    bool doSleep = true;

    physicsWorld = new b2World(gravity);
    physicsWorld->SetAllowSleeping(doSleep);
    physicsWorld->SetContinuousPhysics(true);

    // ----------
    // debug draw
    // -----------
    GLESDebugDraw* debugDraw = new GLESDebugDraw(PTM_RATIO);
    physicsWorld->SetDebugDraw(debugDraw);

   uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
     // flags += b2Draw::e_aabbBit;
    // flags += b2Draw::e_pairBit;
    // flags += b2Draw::e_centerOfMassBit;
    debugDraw->SetFlags(flags);
    

    
    // -----------
    // ground
    // --------

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(screenSize.width/2/PTM_RATIO,
                               screenSize.height/2/PTM_RATIO); // bottom-left corner

	b2Body* groundBody = physicsWorld->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;	
    // bottom
    groundBox.SetAsBox(screenSize.width/2/PTM_RATIO, 0, b2Vec2(0, -screenSize.height/2/PTM_RATIO), 0);
  groundBody->CreateFixture(&groundBox, 0);
    // top
    groundBox.SetAsBox(screenSize.width/2/PTM_RATIO, 0, b2Vec2(0, screenSize.height/2/PTM_RATIO), 0);
    groundBody->CreateFixture(&groundBox, 0);
    // left
    groundBox.SetAsBox(0, screenSize.height/2/PTM_RATIO, b2Vec2(-screenSize.width/2/PTM_RATIO, 0), 0);
    groundBody->CreateFixture(&groundBox, 0);
    // right
    groundBox.SetAsBox(0, screenSize.height/2/PTM_RATIO, b2Vec2(screenSize.width/2/PTM_RATIO, 0), 0);
    groundBody->CreateFixture(&groundBox, 0);




    {
    
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	    
	bodyDef.position.Set(screenSize.width/2/PTM_RATIO, screenSize.height/2/PTM_RATIO);
	//bodyDef.userData = sprite;
	b2Body *body = physicsWorld->CreateBody(&bodyDef);

	// b2PolygonShape shape;
	// shape.SetAsBox(160.0 / PTM_RATIO, 160.0 / PTM_RATIO);
	// body->CreateFixture(&shape, 1);
    
    // add the fixture definitions to the body
    GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, "hero");

    }




    {
	    // body
	    b2BodyDef bodyDef;
	    bodyDef.type = b2_dynamicBody;
	    bodyDef.position	= b2Vec2(screenSize.width/2/PTM_RATIO, screenSize.height/2/PTM_RATIO);
	    b2Body* body = physicsWorld->CreateBody(&bodyDef);

	    float bodyAngle = CC_DEGREES_TO_RADIANS(45);
	    body->SetTransform(body->GetPosition(), bodyAngle);

	    // shape 0
	    {
		    b2PolygonShape box;
		    // b2Vec2 center(30.0/PTM_RATIO, 30.0/PTM_RATIO);
		    // float angle = 0;
		    float width		= 40;
		    float height	= 60;
		    box.SetAsBox(width/PTM_RATIO, height/PTM_RATIO);
		    // fixture
		    body->CreateFixture(&box, 1);
	    }


	    // shape 1
	    {
		    b2PolygonShape box;
		    // b2Vec2 center(30.0/PTM_RATIO, 30.0/PTM_RATIO);
		    b2Vec2 center(0,0);

		    // float angle = CC_DEGREES_TO_RADIANS(45);
		     float angle = 0;

		    box.SetAsBox(30.0/PTM_RATIO, 30.0/PTM_RATIO, center, angle);
		    // fixture
		    body->CreateFixture(&box, 1);
	    }




    }

    // sprite->setAnchorPoint(sc->anchorPointForShape(name.c_str()));
    // schedule(schedule_selector(HelloWorld::tick));


    // init input manager
    InputManager* input = InputManager::sharedInstance();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(input);

//    // hero
//    HeroAircraft* hero = HeroAircraft::create();
//    addChild(hero->graphics);
//    hero->graphics->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
//	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(hero, 0, false);
}

void HelloWorld::stepForPhysicsManager(float time)
{
	PhysicsManager::sharedInstance()->step(time);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
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


void HelloWorld::tick(float dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/

	int velocityIterations = 8;
	int positionIterations = 1;
	    
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	physicsWorld->Step(dt, velocityIterations, positionIterations);

	////Iterate over the bodies in the physics world
	//for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	//{
	//	if (b->GetUserData() != NULL) {
	//		//Synchronize the AtlasSprites position and rotation with the corresponding body
	//		CCSprite* myActor = (CCSprite*)b->GetUserData();
	//		myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
	//		myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
	//	}	
	//}
}

void HelloWorld::draw()
{
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();
    //physicsWorld->DrawDebugData();

    b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();
    world->DrawDebugData();
    kmGLPopMatrix();
}


void HelloWorld::testKeyUpDown()
{
    // ----------------------
    // test key up down event
    // ----------------------
    TestKeyUpDown* keyHandler = new TestKeyUpDown();
    CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate(keyHandler);
}
