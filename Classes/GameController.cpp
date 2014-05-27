
#include "GameController.h"
#include "scene/GameScene.h"
#include "aircraft/HeroAircraft.h"

GameController* GameController::_sharedInstance = NULL;

GameController* GameController::sharedInstance()
{
	if(GameController::_sharedInstance == NULL)
	{
		GameController::_sharedInstance = new GameController();
	}

	return GameController::_sharedInstance;
}

GameController::GameController()
{
	playerAircraft = NULL;
	shadowLayer = NULL;
	explosionLayer = NULL;
	aircraftLayer = NULL;


	newGame();
}

void GameController::resetAll()
{
	CC_SAFE_RELEASE_NULL(playerAircraft);
	CC_SAFE_RELEASE_NULL(shadowLayer);
	CC_SAFE_RELEASE_NULL(explosionLayer);
	CC_SAFE_RELEASE_NULL(aircraftLayer);
}

GameController::~GameController()
{
	CC_SAFE_RELEASE(playerAircraft);
	CC_SAFE_RELEASE(shadowLayer);
	CC_SAFE_RELEASE(aircraftLayer);
	CC_SAFE_RELEASE(explosionLayer);
}


void GameController::setPlayerAircraft(Aircraft* player)
{
	if(playerAircraft != player)
	{
		CC_SAFE_RELEASE_NULL(playerAircraft);
		playerAircraft = player;
		playerAircraft->retain();
	}
}

Aircraft* GameController::getPlayerAircraft()
{
	if(playerAircraft && playerAircraft->shouldReleased)
	{
		CC_SAFE_RELEASE_NULL(playerAircraft);
	}

	return playerAircraft;
}

void GameController::setDrawShadowLayer(CCDrawGameObjectShadowNode* shadowLayer)
{
	if(this->shadowLayer != shadowLayer)
	{
		CC_SAFE_RELEASE(this->shadowLayer);
		this->shadowLayer = shadowLayer;
		shadowLayer->retain();
	}
}

void GameController::setExplosionLayer(CCNode* explosionLayer)
{
	if(this->explosionLayer != explosionLayer)
	{
		CC_SAFE_RELEASE(this->explosionLayer);
		this->explosionLayer = explosionLayer;
		explosionLayer->retain();
	}
}

void GameController::addExplosion(CCNode* explosion)
{
	// pos in world
	CCPoint posInWorld = explosion->getPosition();

	if(explosionLayer)
	{
		CCPoint posInExplosionLayer = explosionLayer->convertToNodeSpace(posInWorld);
		explosion->setPosition(posInExplosionLayer);
		explosionLayer->addChild(explosion);
	}
}

//CCDrawGameObjectShadowNode* GameController::getDrawShadowLayer()
//{ 
//	return this->shadowLayer;
//}

void GameController::addAircraft(Aircraft* aircraft)
{
	// pos in world
	CCPoint posInWorld = aircraft->getPosition();

	if(aircraftLayer)
	{
		CCPoint posInAircraftLayer = aircraftLayer->convertToNodeSpace(posInWorld);
		aircraft->setPosition(posInAircraftLayer);
		aircraftLayer->addChild(aircraft);

		// add it to the shadow layer
		if(shadowLayer)
		{
			shadowLayer->addGameObject(aircraft);
		}
	}
}

void GameController::setAircraftLayer(CCNode* aircraftLayer)
{
	if(this->aircraftLayer != aircraftLayer)
	{
		CC_SAFE_RELEASE(this->aircraftLayer);
		aircraftLayer->retain();
		this->aircraftLayer = aircraftLayer;
	}
}

void GameController::heroDead()
{
	if(heroLife > 0)
	{
		// create new hero
		heroLife--;
		createHero();
		//playerAircraft->setInvinsible(4);
	}
	else
	{
		// game over
		gameOver();
	}
}

void GameController::createHero()
{
	Aircraft* hero = Aircraft::createHeroAircraft();
	// set position
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	hero->setPosition(screenSize.width/2, 40);

	GameController::sharedInstance()->addAircraft(hero);
	GameController::sharedInstance()->setPlayerAircraft(hero);

	HeroAircraft* heroAircraft = dynamic_cast<HeroAircraft*>(hero);
	if(heroAircraft)
	{
		heroAircraft->playNewLifeAction();
		heroAircraft->setInvinsible(4);
	}
}

void GameController::newGame()
{
	heroLife = 2;
	resetAll();
}

void GameController::gameOver()
{
	GameScene* gameScene = dynamic_cast<GameScene*>(CCDirector::sharedDirector()->getRunningScene());
	if(gameScene)
	{
		gameScene->gameOver();
	}
}
