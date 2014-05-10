
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


#include "HeroAircraft.h"
#include "input/InputManager.h"


HeroAircraft* HeroAircraft::create(AircraftDef def)
{
	HeroAircraft* hero = new HeroAircraft();

	if(hero && hero->init(def))
	{
		hero->autorelease();
		return hero;
	}

	CC_SAFE_DELETE(hero);

	return NULL;
}

HeroAircraft::HeroAircraft()
{
}

bool HeroAircraft::init(AircraftDef def)
{
	// init base class
	if(Aircraft::init(def))
	{
		name = "HeroAircraft";

		defaultGun = Gun::createEnemyBoss00Gun1();
		defaultGun->prototypeAmmo->ammoDef.direction = ccp(0,1);
		defaultGun->retain();

		defaultGun->setOwnerAircraft(this);
		addChild(defaultGun);

		return true;
	}

	return false;
}

HeroAircraft::~HeroAircraft()
{
	CC_SAFE_RELEASE_NULL(graphics);
}

void HeroAircraft::update(float dt)
{
	Aircraft::update(dt);

	// move
	InputManager* input = InputManager::sharedInstance();

	if(input->arrowState[input->ARROW_UP] == InputManager::ARROW_PRESSED)
		setPositionY(getPositionY() + 10);

	if(input->arrowState[input->ARROW_DOWN] == InputManager::ARROW_PRESSED)
		setPositionY(getPositionY() - 10);

	if(input->arrowState[input->ARROW_LEFT] == InputManager::ARROW_PRESSED)
		setPositionX(getPositionX() - 10);

	if(input->arrowState[input->ARROW_RIGHT] == InputManager::ARROW_PRESSED)
		setPositionX(getPositionX() + 10);

	if(input->arrowState[input->FIRE] == InputManager::ARROW_PRESSED)
	{
		defaultGun->trigger(true);
	}
	else
	{
		defaultGun->trigger(false);
	}
}
