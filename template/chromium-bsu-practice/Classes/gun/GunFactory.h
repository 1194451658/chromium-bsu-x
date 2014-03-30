
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

#ifndef __GUN_FACTORY_H__
#define __GUN_FACTORY_H__

#include "cocos2d.h"
#include "Gun.h"

USING_NS_CC;

class GunFactory : public CCObject
{
public:
	static GunFactory* sharedInstance();
	Gun* createGun(const char* gunName);

protected:
	GunFactory();

	// config
	struct HeroAmmo00Config
	{
		HeroAmmo00Config():
			ammoDef("png/heroAmmo00.png",
				CCPoint(0,100),
				PhysicsManager::UNKNOWN,
				100.0f)
		{}

		AmmoDef ammoDef;
	};
};

#endif
