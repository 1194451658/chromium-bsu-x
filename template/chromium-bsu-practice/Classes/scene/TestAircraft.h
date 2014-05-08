#ifndef __TEST_AIRCRAFT__H__
#define __TEST_AIRCRAFT__H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

class TestAircraft : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(TestAircraft);

	void menuItemCallback(CCObject* menuItem);


private:
	void draw();
	void stepForPhysicsManager(float time);
};

#endif // __HELLOWORLD_SCENE_H__
