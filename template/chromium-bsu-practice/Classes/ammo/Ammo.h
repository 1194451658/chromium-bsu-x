
#ifndef __AMMO_H__
#define __AMMO_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "GameObject.h"

USING_NS_CC;

struct AmmoDef
{
	// AmmoDef(CCPoint& velocity, int physicsGroup, float demage)
	// 	: velocity(velocity), 
	// 	physicsGroup(physicsGroup),
	// 	demage(demage)
	// {}

	CCPoint& velocity;
	int physicsGroup;
	float demage;
};

class Ammo : public GameObject, public b2ContactListener
{
public:
	static Ammo* create(CCNode* graphics, CCPoint& velocity, int physicsGroup);
	static Ammo* create(CCNode* graphics, AmmoDef& def);

	~Ammo();

	virtual CCNode* initGraphics();
	virtual b2Body* initPhysics();
	virtual void update(float dt) ;

    virtual void BeginContact(b2Contact* contact) ;
    virtual void EndContact(b2Contact* contact) {};
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {};
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {};

protected:
	bool init(CCNode* graphics, CCPoint& velocity, int physicsGroup);
	bool init(CCNode* graphics, AmmoDef& def);

	void doDamageToGameObject(GameObject* g);

private:
	Ammo();
	CCPoint velocity;
	int physicsGroup;
	float damage;

	bool shouldExplode;
};

#endif
