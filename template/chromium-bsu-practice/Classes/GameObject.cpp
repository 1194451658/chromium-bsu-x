

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

	name = "GameObject";

	return true;
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
	
	const CCPoint& pos = getPosition();			// suppose that GameObject Is In The Top Layer.
	float angle	= graphics->getRotation();		// puppose that GameObject doesn't rotate;

	b2Vec2 physicsPos(pos.x / PhysicsManager::PTM_RATIO, pos.y / PhysicsManager::PTM_RATIO);
	float physicsAngle = CC_DEGREES_TO_RADIANS(-angle);

	physics->SetTransform(physicsPos, physicsAngle);
};

void GameObject::postPhysicsStep(float time, PhysicsManager* manager) {

	b2Vec2 pos = physics->GetPosition();
	setPosition(pos.x * PhysicsManager::PTM_RATIO, pos.y * PhysicsManager::PTM_RATIO);

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
