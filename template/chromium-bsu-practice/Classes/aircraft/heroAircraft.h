
#ifndef __HEROAIRCRAFT_H__
#define __HEROAIRCRAFT_H__

#include "cocos2d.h"

USING_NS_CC;

class HeroAircraft : public CCObject, public CCKeypadDelegate
{
public:
	static HeroAircraft* create();

    // update
    virtual void update(float dt) ;

    void updateFire();

private: 
    HeroAircraft();
    ~HeroAircraft();

public:
    CCNode* graphics;

private:
};

#endif
