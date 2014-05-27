
#ifndef __ENTER_SCREEN_TRIGGER_H__
#define __ENTER_SCREEN_TRIGGER_H__

#include "engine/GameObject.h"
#include "AppMacros.h"

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
	static EnterScreenTrigger* create(string& prefabName, CCSize& prefabSize);

	EnterScreenTrigger();
	~EnterScreenTrigger();

	bool init(tinyxml2::XMLDocument* xmlDef);
	bool init(string& prefabName, CCSize& prefabSize);

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
	friend class EnterScreenTriggerCreateGraphicsVisitor;
	friend class EnterScreenTriggerCreateInstanceVisitor;

	bool triggered;

	enum TriggerModeEnum
	{
		TRIGGER_MODE_XFL_DEF,
		TRIGGER_MODE_SINGLE_PREFAB_STRING,
		TRIGGER_MODE_UNKNOWN
	};
private:
	TriggerModeEnum triggerMode;
	tinyxml2::XMLDocument* xmlDef;
	string prefabName;
	CCSize prefabSize;
};

#endif
