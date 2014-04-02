

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

struct AmmoDef
{
	AmmoDef(const char* graphicsFile,
		CCPoint velocity,
		int physicsGroup,
		float damage
	       ):graphicsFile(graphicsFile),
		velocity(velocity),
		physicsGroup(physicsGroup),
		damage(damage)
	{
	}

	const char* graphicsFile;
	CCPoint velocity;
	int physicsGroup;
	float damage;
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

protected:
	bool init(AmmoDef& def);

	void doDamageToGameObject(GameObject* g);

private:
	Ammo();
	CCPoint velocity;
	int physicsGroup;
	float damage;
	const char* graphicsFile;

	bool shouldExplode;
};

#endif
