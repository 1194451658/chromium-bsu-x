
#include "AppMacros.h"

USING_NS_CC;

class TestKeyUpDown : public CCObject, public CCKeypadDelegate
{

public:

    virtual void keyBackClicked() 
    {
	    CCLOG("TestKeyUpDown::keyBackClicked called !");
    }

    // The menu key clicked. only available on wophone & android
    virtual void keyMenuClicked() {
    
	    CCLOG("TestKeyUpDown::keyMenuClicked called !");
    };

    virtual void keyDown_Extension(int key) {
	    CCLOG("TestKeyUpDown::keyDown_Extension %c", key);
    };
    virtual void keyUp_Extension(int key) {
    
	    CCLOG("TestKeyUpDown::keyUp_Extension %c", key);
    };
};
