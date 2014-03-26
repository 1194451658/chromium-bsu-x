
#include "heroAircraft.h"
#include "input/InputManager.h"

#include "util/GB2ShapeCache-x.h"


HeroAircraft* HeroAircraft::create()
{
	HeroAircraft* hero = new HeroAircraft();

	if(hero && hero->init())
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

HeroAircraft::HeroAircraft()
{
}

bool HeroAircraft::init()
{
	// init base class
	return GameObject::init();
}

HeroAircraft::~HeroAircraft()
{
	CCLOG("HeroAircraft::~HeroAircraft Called !");
	CC_SAFE_RELEASE_NULL(graphics);
}

void HeroAircraft::update(float dt)
{
	// CCLOG("hero aircraft update !");
	
	// move
	InputManager* input = InputManager::sharedInstance();

	if(input->arrowState[input->ARROW_UP] == InputManager::ARROW_PRESSED)
		graphics->setPositionY(graphics->getPositionY() + 10);

	if(input->arrowState[input->ARROW_DOWN] == InputManager::ARROW_PRESSED)
		graphics->setPositionY(graphics->getPositionY() - 10);

	if(input->arrowState[input->ARROW_LEFT] == InputManager::ARROW_PRESSED)
		graphics->setPositionX(graphics->getPositionX() - 10);

	if(input->arrowState[input->ARROW_RIGHT] == InputManager::ARROW_PRESSED)
		graphics->setPositionX(graphics->getPositionX() + 10);
}

void HeroAircraft::updateFire()
{
}

CCNode* HeroAircraft::initGraphics()
{
	// create the graphics
	CCSprite* sprite = CCSprite::create("png/hero.png");
	sprite->retain();
	return sprite;
}

b2Body* HeroAircraft::initPhysics()
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	// physics world
	b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();

	// body 
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(screenSize.width/2/PhysicsManager::PTM_RATIO, screenSize.height/2/PhysicsManager::PTM_RATIO);

	b2Body *body = world->CreateBody(&bodyDef);

	// b2PolygonShape shape;
	// shape.SetAsBox(160.0 / PTM_RATIO, 160.0 / PTM_RATIO);
	// body->CreateFixture(&shape, 1);
    
	// add the fixture 
	GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(body, "hero");

	return body;
}
