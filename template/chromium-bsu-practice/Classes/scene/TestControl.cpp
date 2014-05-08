#include "TestControl.h"

#include <stdlib.h>
#include "cocos-ext.h"

USING_NS_CC_EXT;

USING_NS_CC;

#define PTM_RATIO  32

CCScene* TestControl::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestControl *layer = TestControl::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestControl::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	// coordiante indicator
	CCLayerColor* layer = CCLayerColor::create(ccc4(255,0,0,255), 100, 100);
	layer->setPosition(center);
	addChild(layer);


	//// control button
	//{
	//	CCLabelTTF* label = CCLabelTTF::create();
	//	label->setString("controlButton 11111111");
	//	CCScale9Sprite* bg = CCScale9Sprite::create("png/menu_back.png");
	//	CCControlButton* controlButton = CCControlButton::create(label, bg);
	//	addChild(controlButton);
	//	controlButton->setPosition(center);
	//}

	// color picker
	{
		CCControlColourPicker* colorPicker = CCControlColourPicker::create();
		addChild(colorPicker);
		colorPicker->setPosition(center);
	}



	return true;
}

