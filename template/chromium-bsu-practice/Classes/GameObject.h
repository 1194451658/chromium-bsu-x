

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


#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "physics/PhysicsManager.h"


class GameObject : public CCNode, public PhysicsStepCallbackHandler
{

public:
	~GameObject();
	void preStep(float time, PhysicsManager* manager);
	void postStep(float time, PhysicsManager* manager);
	virtual void update(float dt) {CCLOG("GameObject::update called !");} ;

protected:
	virtual CCNode* initGraphics() { return NULL; };
	virtual b2Body* initPhysics() { return NULL; };
	virtual void onEnter() ;
	virtual void onExit() ;

	bool init();

public:
	CCNode* graphics;
	b2Body* physics;

public:
	bool shouldReleased;	// indicate that this object is useless, should deleted !!
				// if others once before retain an class, and some time later 
				// see shouldReleased == true, then should release it, and let it go.
};

#endif
