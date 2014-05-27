
#include "TouchInputLayer.h"
#include "GameController.h"
#include "aircraft/HeroAircraft.h"

bool TouchInputLayer::init()
{
	setTouchEnabled(true);
	setTouchMode(kCCTouchesOneByOne);

	return true;
}

bool TouchInputLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) 
{
	//Aircraft* hero = GameController::sharedInstance().getPlayerAircraft();
	//HeroAircraft* heroAircraft = dynamic_cast<HeroAircraft*>(hero);
	//if(heroAircraft)
	//{
	//	if(heroAircraft->isInUserControl())
	//		return true;
	//}

	//return return false;
	return true;
}

void TouchInputLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) 
{
	CCPoint delta = pTouch->getDelta();

	Aircraft* hero = GameController::sharedInstance()->getPlayerAircraft();
	HeroAircraft* heroAircraft = dynamic_cast<HeroAircraft*>(hero);

	if(heroAircraft)
	{
		if(heroAircraft->isInUserControl())
			hero->setPosition(ccpAdd(hero->getPosition(), delta));
	}
}

void TouchInputLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) 
{

}

void TouchInputLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) 
{

}

