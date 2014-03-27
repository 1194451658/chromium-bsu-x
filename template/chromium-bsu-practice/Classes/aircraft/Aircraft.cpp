

#include "Aircraft.h"


bool Aircraft::init()
{
	hp = 900;
	damageToHit = 0;
	return GameObject::init();
}


void Aircraft::damage(float damage)
{
	if(damage < 0) damage = 0;
	damageToHit += damage;
}

void Aircraft::update(float dt)
{
	if(hp < 0)
	{
		removeFromParent();
		shouldReleased = true;
	}

	if(damageToHit > 0)
	{
		hp -= damageToHit;
	}
}
