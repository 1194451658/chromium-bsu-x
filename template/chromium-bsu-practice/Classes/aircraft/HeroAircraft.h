
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


#ifndef __HEROAIRCRAFT_H__
#define __HEROAIRCRAFT_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Aircraft.h"

//#include "gun/HeroDefaultGun.h"
#include "gun/Gun.h"

USING_NS_CC;

class HeroAircraft : public Aircraft, public CCKeypadDelegate
{
public:
	static HeroAircraft* create(AircraftDef def);
	bool init(AircraftDef def);
	~HeroAircraft();

public:
    // update
    virtual void update(float time);
	
protected:

private: 
    HeroAircraft();
};

#endif
