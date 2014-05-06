

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


#ifndef __AMMO_H__
#define __AMMO_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameObject.h"

USING_NS_CC;
#include <string>

using namespace std;

struct AmmoDef
{
	AmmoDef()
	{
		graphicsFile = "png/heroAmmo00.png";
		velocity = 100;
		direction = ccp(0,1);
		directionAffectRotation = false;
		physicsGroup = PhysicsManager::PHYSICS_GROUP_UNKNOWN;
		damage = 100;
		randTex = false;
		scaleX = 1;
	}

	string graphicsFile;
	int physicsGroup;
	float velocity;
	CCPoint direction;
	bool directionAffectRotation;
	float damage;
	bool randTex;
	float scaleX;
};

class Ammo : public GameObject, public b2ContactListener
{
public:
	static Ammo* create(AmmoDef& def);

	~Ammo();

	virtual CCNode* initGraphics();
	virtual b2Body* initPhysics();
	virtual void update(float dt) ;

    virtual void BeginContact(b2Contact* contact) ;
    virtual void EndContact(b2Contact* contact) {};
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {};
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {};

    virtual GameObject* instance();

	void setDirection(CCPoint& direction)
	{
		ammoDef.direction = direction.normalize();

		if(ammoDef.directionAffectRotation)
			graphics->setRotation(90 - CC_RADIANS_TO_DEGREES(ammoDef.direction.getAngle()));

		physics->SetLinearVelocity(b2Vec2(ammoDef.direction.x * ammoDef.velocity/PhysicsManager::PTM_RATIO,
			ammoDef.direction.y * ammoDef.velocity/PhysicsManager::PTM_RATIO));
	}

	bool isOutScreen();

	static Ammo* createEnemyAmmo0();
	static Ammo* createEnemyAmmo1();
	static Ammo* createEnemyAmmo2();
	static Ammo* createEnemyAmmo3();


protected:
	bool init(AmmoDef& def);

	void doDamageToGameObject(GameObject* g);

private:
	Ammo();
	
	AmmoDef ammoDef;
	bool shouldExplode;
};

#endif
