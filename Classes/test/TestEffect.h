
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


#ifndef __TEST_EFFECT_SCENE_H__
#define __TEST_EFFECT_SCENE_H__

#include "Box2D/Box2D.h"
#include "AppMacros.h"

class TestEffectScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	void playEffectCallback(CCObject* pSender);
	void playShieldCallback(CCObject* pSender);
	void playBurstDisappear(CCObject* pSender);
	void playElectric(CCObject* pSender);
	void playSingleGlitter(CCObject* pSender);
	void playGlitterEmitter(CCObject* pSender);
	void playSuperShield(CCObject* pSender);
	void playSuperBomb(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(TestEffectScene);


private:
	void testExplosion();
};

#endif // __HELLOWORLD_SCENE_H__
