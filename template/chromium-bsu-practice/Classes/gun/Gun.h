
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

#ifndef __GUN_H__
#define __GUN_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Ammo.h"
#include "ShotMethod.h"
#include "aircraft/Aircraft.h"

USING_NS_CC;

class ShotMethod;

class Gun : public GameObject
{
public:
	static Gun* create(Ammo* prototypeAmmo, ShotMethod* shotMethod);
	~Gun();

	void trigger(bool press) { triggerPressed = press;};
	virtual void update(float time);

	Ammo* getPrototypeAmmo() { return prototypeAmmo;}
	Ammo* createAmmo();

	void setOwnerAircraft(Aircraft* aircraft) 
	{ 
		physicsGroup = aircraft->getOnePhysicsGroup(); 

		//cout<<name<< " setOwnerAircraft called "<<endl;
		//cout<<"physicsGroup: "<< physicsGroup<<endl;
	}

protected:
	Gun();
	bool init(Ammo* prototypeAmmo, ShotMethod* shotMethod);

private:
	
	bool triggerPressed;

	// code time
	float coldTime;
	float curTimeToCold;

	// prototype ammo
	Ammo* prototypeAmmo;

	// shot method
	ShotMethod* shotMethod;

	int physicsGroup;
};
#endif

