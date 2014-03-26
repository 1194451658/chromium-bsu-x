
#ifndef __HEROAIRCRAFT_H__
#define __HEROAIRCRAFT_H__

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

class HeroAircraft : public GameObject, public CCKeypadDelegate
{
public:
	static HeroAircraft* create();

public:
    // update
    virtual void update(float dt) ;
    void updateFire();

private: 
    HeroAircraft();
    ~HeroAircraft();

    virtual CCNode* initGraphics();
    virtual b2Body* initPhysics();

private:
    bool init();

public:

private:

};

#endif
