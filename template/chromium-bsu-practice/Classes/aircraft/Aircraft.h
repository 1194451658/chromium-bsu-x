
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

#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "cocos2d.h"
#include "GameObject.h"

#include <string>

using namespace std;

USING_NS_CC;

struct AircraftDef
{
	AircraftDef()
	{
		hp = 1000;
		graphicsFile = "png/airCraft/hero.png";
		physicsShapeName = "hero";

		groupIndex = PhysicsManager::PHYSICS_GROUP_JUSTICE;
		categoryBits = PhysicsManager::AIRCRAFT;
		maskBits		= PhysicsManager::AIRCRAFT | PhysicsManager::AMMO;
	}

	float hp;
	string graphicsFile;
	string physicsShapeName;

	//
	int groupIndex;
	int categoryBits;
	int maskBits;
};

class HeroAircraft;
class EnemyBoss00;

class Aircraft : public GameObject
{

public:
	bool init(AircraftDef def) ;
	void damage(float damage);
	void update(float dt) ;

	static Aircraft* create(AircraftDef& def);

	// game object
	virtual CCNode* initGraphics();
	virtual b2Body* initPhysics();

	void setCurHp(float newHp);

	// hp bar
	void hpBarInit(float width, float height, float maxValue, float initialValue);
	void hpBarUpdate(float percentage);

	static Aircraft* createHeroAircraft();
	static Aircraft* createEnemyAircraft01();
	static Aircraft* createBoss00();

private:
	virtual CCSpriteWithShadow* getShadowSprite();

private:
	AircraftDef aircraftDef;

	float maxHp;
	float curHp;
	float damageToHit;

	// hp bar
	CCLayerColor* hpBarBg;
	CCLayerColor* hpBarFg;
	float hpBarMaxValue;
	float hpBarCurValue;
	float hpBarWidth;
	float hpBarHeight;
	
};

#endif
