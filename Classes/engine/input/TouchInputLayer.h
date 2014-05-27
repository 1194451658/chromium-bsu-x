

#ifndef __TOUCH_INPUT_LAYER_H__
#define __TOUCH_INPUT_LAYER_H__


#include "cocos2d.h"

USING_NS_CC;

class TouchInputLayer : public CCLayer
{
public:
	CREATE_FUNC(TouchInputLayer);


	bool init();

     virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
     virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) ;
     virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) ;
     virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) ;

private:
	CCPoint previousPos;
};

#endif