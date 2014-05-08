
#include "GameController.h"

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
}


void GameController::setPlayerAircraft(Aircraft* player)
{
	CC_SAFE_RELEASE_NULL(playerAircraft);
	player->retain();
	playerAircraft = player;
}

Aircraft* GameController::getPlayerAircraft()
{
	if(playerAircraft && playerAircraft->shouldReleased)
	{
		CC_SAFE_RELEASE_NULL(playerAircraft);
	}

	return playerAircraft;
}