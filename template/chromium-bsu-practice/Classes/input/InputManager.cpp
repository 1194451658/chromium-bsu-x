

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
