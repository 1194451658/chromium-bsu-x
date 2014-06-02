
#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "aircraft/Aircraft.h"
#include "engine/CCDrawGameObjectShadowNode.h"

class GameController
{
public:

	static GameController* sharedInstance();
	~GameController();

public:

	// specify which aircraft is hero aircraft
	void setPlayerAircraft(Aircraft* player);
	Aircraft* getPlayerAircraft();

	// speciy draw shadow layer
	void setDrawShadowLayer(CCDrawGameObjectShadowNode* shadowLayer);
	//CCDrawGameObjectShadowNode* getDrawShadowLayer();

	// set explosion layer
	void setExplosionLayer(CCNode* explosionLayer);
	void addExplosion(CCNode* explosion);

	// add aircraft layer
	void addAircraft(Aircraft* aircraft);
	void setAircraftLayer(CCNode* aircraftLayer);


	// about hero
	void heroDead();
	void createHero();
	int getHeroLife(){ return heroLife;}

	// about game
	void newGame();
	void gameOver();

	// reset all
	void resetAll();


private:
	static void cleanup();
	static GameController* _sharedInstance;
	GameController();

	Aircraft* playerAircraft;
	CCDrawGameObjectShadowNode* shadowLayer;
	CCNode* explosionLayer;
	CCNode* aircraftLayer;


private:
	int heroLife;

};

#endif // !__GAME_CONTROLLER_H__
