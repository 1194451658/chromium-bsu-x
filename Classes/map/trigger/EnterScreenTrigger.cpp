
#include "EnterScreenTrigger.h"
#include "engine/tinyxml2/tinyxml2utils.h"
#include "engine/xfl/XflParser.h"
#include "aircraft/Aircraft.h"
#include "GameController.h"


EnterScreenTrigger* EnterScreenTrigger::create(tinyxml2::XMLDocument* xmlDef)
{
	EnterScreenTrigger* newIns = new EnterScreenTrigger();

	if(newIns->init(xmlDef))
	{
		newIns->autorelease();
		return newIns;
	}

	return NULL;
}

EnterScreenTrigger* EnterScreenTrigger::create(string& prefabName, CCSize& prefabSize)
{
	EnterScreenTrigger* newTrigger = new EnterScreenTrigger();

	if(newTrigger->init(prefabName, prefabSize))
	{
		newTrigger->autorelease();
		return newTrigger;
	}

	return NULL;
}

EnterScreenTrigger::EnterScreenTrigger()
{
	triggered = false;

	triggerMode = TRIGGER_MODE_UNKNOWN;
	xmlDef = NULL;
}
EnterScreenTrigger::~EnterScreenTrigger()
{

}

bool EnterScreenTrigger::init(tinyxml2::XMLDocument* xmlDef)
{
	//
	triggerMode = TRIGGER_MODE_XFL_DEF;
	this->xmlDef = xmlDef;
	return GameObject::init();
}

bool EnterScreenTrigger::init(string& prefabName, CCSize& prefabSize)
{
	triggerMode = TRIGGER_MODE_SINGLE_PREFAB_STRING;
	this->prefabName = prefabName;
	this->prefabSize = prefabSize;
	return GameObject::init();
}

 void EnterScreenTrigger::BeginContact(b2Contact* contact)
 {
	 if(graphics)
	 {
		 CCLayerColor* layerColor = dynamic_cast<CCLayerColor*>(graphics);

		 if(layerColor)
		 {
			 layerColor->setColor(ccc3(255,0,0));
		 }
	 }

	 shouldReleased = true;
	 triggered = true;
 }

void EnterScreenTrigger::postPhysicsStep(float time, PhysicsManager* manager)
{
	GameObject::postPhysicsStep(time, manager);

	if(triggered)
	{
		triggered = false;


		if(TRIGGER_MODE_XFL_DEF == triggerMode)
		{
			EnterScreenTriggerCreateInstanceVisitor createInstanceVisitor(this);
			xmlDef->Accept(&createInstanceVisitor);
		}

		else if(TRIGGER_MODE_SINGLE_PREFAB_STRING == triggerMode)
		{
			// create prefab
			Aircraft* enemy = NULL;
			if(prefabName == "prefab/enemy/enemyBoss00.xml")
				enemy = Aircraft::createBoss00();
			else if(prefabName == "prefab/enemy/enemyBoss01.xml")
				enemy = Aircraft::createBoss01();
			else if(prefabName == "prefab/enemy/enemyOmni.xml")
				enemy = Aircraft::createEnemyOmni();
			else if(prefabName == "prefab/enemy/enemyRayGun.xml")
				enemy = Aircraft::createEnemyRayGun();
			else if(prefabName == "prefab/enemy/enemyStraight.xml")
				enemy = Aircraft::createEnemyStraight();
			else if(prefabName == "prefab/enemy/enemyTank.xml")
				enemy = Aircraft::createEnemyTank();

			if(enemy)
			{
				CCNode* parent = getParent();
				if(parent)
				{
					enemy->setPosition(getPositionInWorldSpace());
					GameController::sharedInstance()->addAircraft(enemy);
				}
			}
		}

		// remove self
		this->shouldReleased = true;
		this->removeFromParent();
	}
}

CCNode* EnterScreenTrigger::initGraphics()
{
	if(triggerMode == TRIGGER_MODE_XFL_DEF && xmlDef)
	{
		// parse trigger collision indicator's graphics region
		EnterScreenTriggerCreateGraphicsVisitor createGraphicsVisitor(this);
		xmlDef->Accept(&createGraphicsVisitor);
	}

	else if(triggerMode == TRIGGER_MODE_SINGLE_PREFAB_STRING)
	{

		CCLayerColor* collider = CCLayerColor::create(ccc4(0,255,0,100));
		collider->changeWidthAndHeight(prefabSize.width, prefabSize.height);
		collider->ignoreAnchorPointForPosition(false);
		collider->setAnchorPoint(ccp(0.5, 0.5));
		graphics = collider;
		//graphics->setVisible(false);
	}


	return graphics;
	//return NULL;
}

bool EnterScreenTriggerCreateGraphicsVisitor::VisitEnter(const tinyxml2::XMLElement & element, const  tinyxml2::XMLAttribute * attribute)
{
	// only parse the first frame
	if(strcmp(element.Name(), "DOMFrame") == 0)
	{
		if(element.Attribute("index", "0"))
			return true;
		else
		{
			return false;
		}
	} 

	// parse DOMSymbolInstance
	if(strcmp(element.Name(), "DOMSymbolInstance") == 0)
	{
		const char* libraryItemName = element.Attribute("libraryItemName");
		string libraryItemNameStr = libraryItemName;

		// check if it's prefab instance
		{
			std::size_t pos = libraryItemNameStr.find("prefab/");

			if(pos == 0)
			{

			}
			else
			{
				// it's not prefab
				// get pos and size
				if(!triggerToControl->graphics)
				{
					MatrixElement matrixElement = parseMatrixElement(&element);
					CCPoint transPoint = parseTransformationPoint(&element);

					CCLayerColor* layerColor = CCLayerColor::create(ccc4(0,255,0,100));
					layerColor->changeWidthAndHeight(transPoint.x*2, transPoint.y*2);
					layerColor->setPosition(ccp(matrixElement.tx, -matrixElement.ty - transPoint.y*2));
					triggerToControl->graphics = layerColor;
					//triggerToControl->graphics->setVisible(false);
				}
			}
		}

		return false;
	}

	return true;
}

bool EnterScreenTriggerCreateInstanceVisitor::VisitEnter(const tinyxml2::XMLElement & element, const  tinyxml2::XMLAttribute * attribute)
{
	// only parse the first frame
	if(strcmp(element.Name(), "DOMFrame") == 0)
	{
		if(element.Attribute("index", "0"))
			return true;
		else
		{
			return false;
		}
	} 

	// parse DOMSymbolInstance
	if(strcmp(element.Name(), "DOMSymbolInstance") == 0)
	{
		const char* libraryItemName = element.Attribute("libraryItemName");
		string libraryItemNameStr = libraryItemName;

		// check if it's prefab instance
		{
			std::size_t pos = libraryItemNameStr.find("prefab/");

			if(pos == 0)
			{

				Aircraft* enemy = NULL;

				if(libraryItemNameStr == "prefab/enemy/enemyStraight")
				{
					enemy = Aircraft::createEnemyStraight();
				}
				else if(libraryItemNameStr == "prefab/enemy/enemyRayGun")
				{
					enemy = Aircraft::createEnemyRayGun();
				}
				else if(libraryItemNameStr == "prefab/enemy/enemyOmni")
				{
					enemy = Aircraft::createEnemyOmni();
				}
				else if(libraryItemNameStr == "prefab/enemy/enemyTank")
				{
					enemy = Aircraft::createEnemyTank();
				}
				else if(libraryItemNameStr == "prefab/enemy/enemyBoss00")
				{
					enemy = Aircraft::createBoss00();
				}
				else if(libraryItemNameStr == "prefab/enemy/enemyBoss01")
				{
					enemy = Aircraft::createBoss01();
				}

				MatrixElement matrixElement = parseMatrixElement(&element);
				CCPoint transPoint = parseTransformationPoint(&element);


				enemy->setPosition(ccp(matrixElement.tx + transPoint.x, -(matrixElement.ty + transPoint.y)));

				// add to aircraft layer
				CCNode* triggerParent = triggerToControl->getParent();
				if(triggerParent)
				{
					CCPoint pos = enemy->getPosition();
					CCPoint posInParent = triggerToControl->convertToParentSpace(pos);
					enemy->setPosition(triggerParent->convertToWorldSpace(posInParent));
					// triggerParent->addChild(enemy);
					GameController::sharedInstance()->addAircraft(enemy);
				}
			}
		}

		return false;
	}

	return true;

};


b2Body* EnterScreenTrigger::initPhysics()
{
	if(graphics)
	{
		CCSize size = graphics->getContentSize();
		CCPoint anchorPoint = graphics->getAnchorPointInPoints();
		if(graphics->isIgnoreAnchorPointForPosition())
			anchorPoint = ccp(0,0);

		CCPoint pos = graphics->getPosition();

		b2World* world = PhysicsManager::sharedInstance()->getPhysicsWorld();

		// create the physics shape from graphics content size
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.fixedRotation = true;
		b2Body* body = world->CreateBody(&bodyDef);

		// because if graphics is CCLayerColor
		b2PolygonShape shape;
		b2Vec2 center((size.width/2 + pos.x - anchorPoint.x) / PhysicsManager::PTM_RATIO, (size.height/2 + pos.y - anchorPoint.y) / PhysicsManager::PTM_RATIO);
		shape.SetAsBox(size.width/2/PhysicsManager::PTM_RATIO,
			size.height/2/PhysicsManager::PTM_RATIO,
			center,
			0);
		body->CreateFixture(&shape, 0);

		// set fixture collide filter
		b2Filter filter;
		filter.groupIndex	= PhysicsManager::PHYSICS_GROUP_UNKNOWN;
		filter.categoryBits = PhysicsManager::ONSCREEN_TRIGGER;
		filter.maskBits		= PhysicsManager::SCREEN;

		b2Fixture* fixtureList = body->GetFixtureList();

		while(NULL != fixtureList)
		{
			fixtureList->SetFilterData(filter);
			fixtureList->SetSensor(true);
			fixtureList = fixtureList->GetNext();
		}

		return body;
	}

	return NULL;
}