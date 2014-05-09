
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

#ifndef __TEST_PHYSICS_MANAGER_H__
#define __TEST_PHYSICS_MANAGER_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

class TestPhysicsManager : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(TestPhysicsManager);


private:
	void draw();
	void stepForPhysicsManager(float time);
};

#endif // __HELLOWORLD_SCENE_H__
