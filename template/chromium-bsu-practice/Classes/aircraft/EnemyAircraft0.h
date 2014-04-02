
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



#ifndef __ENEMY_AIRCRAFT0_H__
#define __ENEMY_AIRCRAFT0_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "Aircraft.h"
#include "gun/Gun.h"

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
    Gun* defaultGun;
};

#endif
