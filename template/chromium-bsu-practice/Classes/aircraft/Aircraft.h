
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



#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "cocos2d.h"
#include "GameObject.h"

USING_NS_CC;

class Aircraft : public GameObject
{

public:
	bool init() ;
	void damage(float damage);
	void update(float dt) ;

	void setCurHp(float newHp);

	// hp bar
	void hpBarInit(float width, float height, float maxValue, float initialValue);
	void hpBarUpdate(float percentage);

private:
	virtual CCSpriteWithShadow* getShadowSprite();

private:
	float maxHp;
	float curHp;
	float damageToHit;

	// hp bar
	CCLayerColor* hpBarBg;
	CCLayerColor* hpBarFg;
	float hpBarMaxValue;
	float hpBarCurValue;
	float hpBarWidth;
	float hpBarHeight;
	
};

#endif
