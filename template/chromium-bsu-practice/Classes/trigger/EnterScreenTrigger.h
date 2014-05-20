
#ifndef __ENTER_SCREEN_TRIGGER_H__
#define __ENTER_SCREEN_TRIGGER_H__

#include "GameObject.h"
#include "cocos2d.h"

USING_NS_CC;

class EnterScreenTrigger;



class EnterScreenTriggerCreateGraphicsVisitor : public tinyxml2::XMLVisitor
{
public:

	EnterScreenTriggerCreateGraphicsVisitor(EnterScreenTrigger* triggerToControl)
	{
		this->triggerToControl = triggerToControl;
	}

	// parse tinyxml2
	virtual bool VisitEnter (const tinyxml2::XMLElement & element, const  tinyxml2::XMLAttribute * attribute);

private:
	EnterScreenTrigger* triggerToControl;
};

class EnterScreenTriggerCreateInstanceVisitor : public tinyxml2::XMLVisitor
{
public:

	EnterScreenTriggerCreateInstanceVisitor(EnterScreenTrigger* triggerToControl)
	{
		this->triggerToControl = triggerToControl;
	}

	// parse tinyxml2
	virtual bool VisitEnter (const tinyxml2::XMLElement & element, const  tinyxml2::XMLAttribute * attribute);

private:
	EnterScreenTrigger* triggerToControl;
};


class EnterScreenTrigger : public GameObject, public b2ContactListener
{

public:
	static EnterScreenTrigger* create(tinyxml2::XMLDocument* xmlDef);

	EnterScreenTrigger();
	~EnterScreenTrigger();

	bool init(tinyxml2::XMLDocument* xmlDef);

	// game object
	virtual CCNode* initGraphics();
	virtual b2Body* initPhysics();

	// contact listener
	virtual void BeginContact(b2Contact* contact) ;
	virtual void EndContact(b2Contact* contact) {};
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {};
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {};

	// game object
	void postPhysicsStep(float time, PhysicsManager* manager);



private:
	tinyxml2::XMLDocument* xmlDef;

	friend EnterScreenTriggerCreateGraphicsVisitor;
	friend EnterScreenTriggerCreateInstanceVisitor;

	bool triggered;
};

#endif