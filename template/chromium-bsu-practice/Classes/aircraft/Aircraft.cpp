
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

#include "Aircraft.h"

bool Aircraft::init()
{
	maxHp = 900;
	curHp = 900;
	damageToHit = 0;

	if(GameObject::init())
	{
		name = "Aircraft";

		hpBarInit(100, 10, maxHp, curHp);
		return true;
	}

	return false;
}


void Aircraft::damage(float damage)
{
	if(damage < 0) damage = 0;
	// damageToHit += damage;
}

void Aircraft::hpBarInit(float width, float height, float maxValue, float initialValue)
{
	CCLayerColor* bg = CCLayerColor::create(ccc4(0, 255, 0, 255));
	bg->changeWidthAndHeight(width, height);

	CCLayerColor* fg = CCLayerColor::create(ccc4(255, 0, 0, 255));
	float fgWidth = initialValue / maxValue * width;
	fg->changeWidthAndHeight(fgWidth, height);
	bg->addChild(fg);

	// center hp bar
	bg->setPosition(ccp(-bg->getContentSize().width/2, 30));

	hpBarMaxValue = maxValue;
	hpBarCurValue = initialValue;
	hpBarWidth = width;
	hpBarHeight = height;

	hpBarBg = bg;
	hpBarFg = fg;

	// add bar
	addChild(bg);
}

void Aircraft::hpBarUpdate(float percentage)
{
	if(percentage < 0) percentage = 0;
	hpBarFg->changeWidthAndHeight(hpBarWidth * percentage, hpBarHeight);
}

void Aircraft::update(float dt)
{
	if(curHp < 0)
	{
		removeFromParent();
		shouldReleased = true;
	}

	if(damageToHit > 0)
	{
		//curHp -= damageToHit;
		setCurHp(curHp-damageToHit);
		damageToHit = 0;
	}
}

void Aircraft::setCurHp(float newHp)
{
	curHp = newHp;
	hpBarUpdate(curHp / maxHp);
}

CCSpriteWithShadow* Aircraft::getShadowSprite()
{
	CCSpriteWithShadow* shadow = dynamic_cast<CCSpriteWithShadow*>(graphics);
	return shadow;
}
