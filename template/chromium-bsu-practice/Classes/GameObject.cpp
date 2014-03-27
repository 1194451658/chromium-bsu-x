
#include "GameObject.h"

bool GameObject::init()
{
	graphics = initGraphics();
	physics = initPhysics();

	if(graphics)
	{
		graphics->retain();
		addChild(graphics);
	}

	if(physics)
	{
		physics->SetUserData((void*) this);
		PhysicsManager::sharedInstance()->addStepCallbackHandler(this);
	}

	return true;
}

GameObject::~GameObject()
{
	CC_SAFE_RELEASE_NULL(graphics);
	deleted = true;
}

void GameObject::preStep(float time, PhysicsManager* manager) {
	
	const CCPoint& pos = getPosition();
	float angle	= getRotation();

	b2Vec2 physicsPos(pos.x / PhysicsManager::PTM_RATIO, pos.y / PhysicsManager::PTM_RATIO);
	float physicsAngle = CC_DEGREES_TO_RADIANS(-angle);

	physics->SetTransform(physicsPos, physicsAngle);
};

void GameObject::postStep(float time, PhysicsManager* manager) {

	b2Vec2 pos = physics->GetPosition();
	setPosition(pos.x * PhysicsManager::PTM_RATIO, pos.y * PhysicsManager::PTM_RATIO);

	float angle = physics->GetAngle();
	setRotation(CC_RADIANS_TO_DEGREES(-angle));
};


void GameObject::onEnter()
{
	CCNode::onEnter();
	scheduleUpdate();
}

void GameObject::onExit()
{
	CCNode::onExit();
	unscheduleUpdate();
}
