
#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "aircraft/Aircraft.h"

class GameController
{
public:

	static GameController* sharedInstance();

public:
	void setPlayerAircraft(Aircraft* player);
	Aircraft* getPlayerAircraft();


private:
	static GameController* _sharedInstance;
	GameController();

	Aircraft* playerAircraft;

};

#endif // !__GAME_CONTROLLER_H__
