
#include "heroAircraft.h"
#include "input/InputManager.h"

HeroAircraft* HeroAircraft::create()
{
	HeroAircraft* hero = new HeroAircraft();
	hero->autorelease();
	return hero;
}

HeroAircraft::HeroAircraft()
{
	// create the graphics
	graphics = new CCNode();
	CCSprite* sprite = CCSprite::create("png/hero.png");
	graphics->addChild(sprite);
}

HeroAircraft::~HeroAircraft()
{
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

