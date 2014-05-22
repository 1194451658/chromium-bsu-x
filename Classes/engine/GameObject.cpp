

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


#include "GameObject.h"
#include <iostream>

using namespace std;

bool GameObject::init()
{
	shouldReleased = false;

	graphics = initGraphics();
	physics = initPhysics();

	if(graphics)
	{
		graphics->retain();
		graphics->setUserData((void*)this);
		addChild(graphics);
	}

	if(physics)
	{
		physics->SetActive(false);
		physics->SetUserData((void*) this);
		PhysicsManager::sharedInstance()->addStepCallbackHandler(this);
	}

	return true;
}

GameObject::GameObject()
{
	graphics = NULL;
	physics = NULL;

	name = "GameObject";
}

GameObject::~GameObject()
{
	CC_SAFE_RELEASE_NULL(graphics);

	if(physics)
	{
		PhysicsManager::sharedInstance()->getPhysicsWorld()->DestroyBody(physics);
	}
}

void GameObject::prePhysicsStep(float time, PhysicsManager* manager) {
	
	const CCPoint& pos = getPositionInWorldSpace();
	float angle	= graphics->getRotation();		// puppose that GameObject doesn't rotate;

	b2Vec2 physicsPos(pos.x / PhysicsManager::PTM_RATIO, pos.y / PhysicsManager::PTM_RATIO);
	float physicsAngle = CC_DEGREES_TO_RADIANS(-angle);

	physics->SetTransform(physicsPos, physicsAngle);
};

void GameObject::postPhysicsStep(float time, PhysicsManager* manager) {

	b2Vec2 pos = physics->GetPosition();
	CCPoint posPoint = ccp(pos.x * PhysicsManager::PTM_RATIO, pos.y * PhysicsManager::PTM_RATIO);
	
	CCNode* parent = getParent();
	if(parent)
	{
		posPoint = parent->convertToNodeSpace(posPoint);
	}

	setPosition(posPoint);

	float angle = physics->GetAngle();
	graphics->setRotation(CC_RADIANS_TO_DEGREES(-angle));
};


void GameObject::onEnter()
{
	CCNode::onEnter();
	scheduleUpdate();
	
	if(physics)
		physics->SetActive(true);
}

void GameObject::onExit()
{
	CCNode::onExit();
	unscheduleUpdate();

	if(physics)
		physics->SetActive(false);
}

void GameObject::setPhysicsFilterData(b2Filter& filterData)
{
	if(physics)
	{
		b2Fixture* fixtureList = physics->GetFixtureList();

		while(NULL != fixtureList)
		{
			fixtureList->SetFilterData(filterData);
			fixtureList = fixtureList->GetNext();
		}
	}
}

void GameObject::setPhysicsGroup(int physicsGroup)
{
	b2Filter newFilterData;
	newFilterData.groupIndex = physicsGroup;

	if(physics)
	{
		b2Fixture* fixtureList = physics->GetFixtureList();

		while(NULL != fixtureList)
		{
			const b2Filter& filterData = fixtureList->GetFilterData();
			newFilterData.maskBits = filterData.maskBits;
			newFilterData.categoryBits = filterData.categoryBits;

			fixtureList->SetFilterData(newFilterData);
			fixtureList = fixtureList->GetNext();
		}
	}
}

int GameObject::getOnePhysicsGroup()
{
	if(physics)
	{
		b2Fixture* fixtureList = physics->GetFixtureList();
		b2Filter filterData = fixtureList->GetFilterData();

		return filterData.groupIndex;
	}

	return 0;
}

void GameObject::visitShadow()
{

	// quick return if not visible. children won't be drawn.
	if (!m_bVisible)
	{
		return;
	}
	kmGLPushMatrix();

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->beforeDraw();
	}

	this->transform();

	///////////////////////////////
	// visit game object 's shadow
	///////////////////////////////
	CCSpriteExtWithShadow* shadow = getShadowSprite();
	if(shadow)
	{
		shadow->visitShadow();
	}

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}

CCPoint GameObject::getPositionInWorldSpace()
{
	CCNode* parent = getParent();

	if(parent)
	{
			CCPoint posInWorld = parent->convertToWorldSpace(getPosition());
			return posInWorld;
	}

	return getPosition();
}

CCPoint GameObject::convertToParentSpace(CCPoint& pos)
{
	CCNode* parent = getParent();
	CCPoint posInParent = pos;

	if(parent)
	{

		CCPoint posInWorld = convertToWorldSpace(pos);
		posInParent = parent->convertToNodeSpace(posInWorld);
	}

	return posInParent;
}

bool GameObject::isOutScreen(float extraOutX , float extraOutY)
{
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	extraOutX = fabs(extraOutX);
	extraOutY = fabs(extraOutY);

	CCNode* parent = getParent();

	if(parent)
	{
		CCPoint posInWorld = parent->convertToWorldSpace(getPosition());

		if(posInWorld.x > origin.x + visibleSize.width + extraOutX || 
			posInWorld.x < origin.x - extraOutX ||
			posInWorld.y > origin.y + visibleSize.height + extraOutY || 
			posInWorld.y < origin.y - extraOutY)
		{
			return true;
		}
	}

	return false;
}

bool GameObject::isBelowScreen(float extraOutY)
{
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCNode* parent = getParent();

	if(parent)
	{
		CCPoint posInWorld = parent->convertToWorldSpace(getPosition());

		if(posInWorld.y < origin.y - extraOutY)
		{
			return true;
		}
	}

	return false;
}
