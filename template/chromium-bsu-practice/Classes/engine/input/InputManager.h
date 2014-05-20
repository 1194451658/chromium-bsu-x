

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
    enum ArrowType { ARROW_UP = 0,
		 ARROW_DOWN, 
		 ARROW_LEFT,
		 ARROW_RIGHT,
		 FIRE,
		 NUMBER_OF_ARROW};
    enum ArrowState { ARROW_RELEASED = 0, ARROW_PRESSED};
    ArrowState arrowState[NUMBER_OF_ARROW];

private:
    InputManager();
};
#endif
