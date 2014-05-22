

/*
ufolr原创，转载请注明：
转载自ufolr的博客 原文连接：http://blog.csdn.net/ufolr/article/details/7624851
*/


#ifndef __TEST_FALLING_LEAF_H__
#define __TEST_FALLING_LEAF_H__

#include "AppMacros.h"

USING_NS_CC;

class TestFallingLeaf : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	void resetLeafPos(CCNode* sender);//叶片位置重置函数  
	void playLeafAnim(CCSpriteExt *spriteLeaf);//下落过程实现函数  

	// implement the "static node()" method manually
	CREATE_FUNC(TestFallingLeaf);
};

#endif // __HELLOWORLD_SCENE_H__
