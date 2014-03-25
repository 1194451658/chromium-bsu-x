
#ifndef __INPUT_MANAGER__
#define __INPUT_MANAGER__

#include "cocos2d.h"

USING_NS_CC;


class InputManager : public CCObject, public CCKeypadDelegate
{
public:
	static InputManager* sharedInstance();

	// key pad
    virtual void keyBackClicked() ;
    virtual void keyMenuClicked();
    virtual void keyDown_Extension(int key) ;
    virtual void keyUp_Extension(int key);

public:
    enum ArrowType { ARROW_UP = 0, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT, NUMBER_OF_ARROW};
    enum ArrowState { ARROW_RELEASED = 0, ARROW_PRESSED};
    ArrowState arrowState[NUMBER_OF_ARROW];

private:
    InputManager();
};
#endif
