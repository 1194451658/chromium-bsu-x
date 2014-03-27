
#ifndef __ENEMY_AIRCRAFT0_H__
#define __ENEMY_AIRCRAFT0_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Aircraft.h"

#include "gun/HeroDefaultGun.h"

USING_NS_CC;

class EnemyAircraft0 : public Aircraft, public CCKeypadDelegate
{
public:
	static EnemyAircraft0* create();
	~EnemyAircraft0();

public:
    // update
    virtual void update(float time);
protected:

private: 
    EnemyAircraft0();
    virtual CCNode* initGraphics();
    virtual b2Body* initPhysics();

private:
    bool init();

public:

private:
    HeroDefaultGun* defaultGun;
};

#endif
