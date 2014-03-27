
#ifndef __HERO_DEFAULT_GUN_H__
#define __HERO_DEFAULT_GUN_H__

#include "cocos2d.h"

#include "aircraft/Aircraft.h"

USING_NS_CC;

class HeroDefaultGun : public GameObject
{

public:
	static HeroDefaultGun* create(Aircraft* aircraft, CCPoint& velocity, int physicsGroup);
	~HeroDefaultGun();
	virtual void update(float time);
	void trigger(bool press) { triggerPressed = press;};

protected:
	HeroDefaultGun();
	bool init(Aircraft* aircraft, CCPoint& velocity, int physicsGroup);

private:
	float coldTime;
	float currentColdTime;
	bool triggerPressed;

	CCPoint velocity;
	int physicsGroup;

	Aircraft* aircraft;
};

#endif
