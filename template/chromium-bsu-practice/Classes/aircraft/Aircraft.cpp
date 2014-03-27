
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
