

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



#include "input/InputManager.h"

static InputManager* _sharedInstance = NULL;

InputManager::InputManager()
{
	// Reset Arrow
	for(int i=0;i<NUMBER_OF_ARROW;i++)
	{
		arrowState[i] = ARROW_RELEASED;
	}
}

InputManager* InputManager::sharedInstance()
{
	if(_sharedInstance == NULL)
	{
		_sharedInstance = new InputManager();
	}

	return _sharedInstance;
}

void InputManager::keyBackClicked() 
{
}

void InputManager::keyMenuClicked() {

};

void InputManager::keyDown_Extension(int key) {

	// CCLOG("hero aircraft key down %c", key);

	if(key == 'A')
		arrowState[ARROW_LEFT] = ARROW_PRESSED;
	else if(key == 'S')
		arrowState[ARROW_DOWN] = ARROW_PRESSED;
	else if(key == 'D')
		arrowState[ARROW_RIGHT] = ARROW_PRESSED;
	else if(key == 'W')
		arrowState[ARROW_UP] = ARROW_PRESSED;
	else if(key == 'J')
		arrowState[FIRE]	= ARROW_PRESSED;

};
void InputManager::keyUp_Extension(int key) {

	// CCLOG("hero aircraft key up %c", key);

	if(key == 'A')
		arrowState[ARROW_LEFT] = ARROW_RELEASED;
	else if(key == 'S')
		arrowState[ARROW_DOWN] = ARROW_RELEASED;
	else if(key == 'D')
		arrowState[ARROW_RIGHT] = ARROW_RELEASED;
	else if(key == 'W')
		arrowState[ARROW_UP] = ARROW_RELEASED;
	else if(key == 'J')
		arrowState[FIRE]	= ARROW_RELEASED;
};
