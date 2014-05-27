
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

#include "CCDrawGameObjectShadowNode.h"
#include "engine/sprite_nodes/CCSpriteExtWithShadow.h"
#include "GameObject.h"

CCDrawGameObjectShadowNode* CCDrawGameObjectShadowNode::create()
{
	CCDrawGameObjectShadowNode * pRet = new CCDrawGameObjectShadowNode();
	if (pRet && pRet->init())
	{
		pRet->childrenToRemove = CCArray::create();
		pRet->childrenToRemove->retain();
		pRet->gameObjects = NULL;
		
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

CCDrawGameObjectShadowNode::CCDrawGameObjectShadowNode()
{
	childrenToRemove = NULL;
	gameObjects = NULL;
}

CCDrawGameObjectShadowNode::~CCDrawGameObjectShadowNode()
{
	CC_SAFE_RELEASE(childrenToRemove);
	CC_SAFE_RELEASE(gameObjects);
}


void CCDrawGameObjectShadowNode::addGameObject(GameObject* go)
{
	CCAssert( go != NULL, "Argument must be non-nil");
	// CCAssert( child->m_pParent == NULL, "child already added. It can't be added again");

	if( ! gameObjects )
	{
		gameObjects = CCArray::createWithCapacity(4);
		gameObjects->retain();
	}

	CCNode* node = CCNode::create();

	// ccArrayAppendObjectWithResize(gameObjects->data, go);
	gameObjects->addObject(go);
}

void CCDrawGameObjectShadowNode::removeShouldReleasedGameObject()
{
	if(gameObjects && gameObjects->count() > 0)
	{
		int i = 0;
		ccArray *arrayData = gameObjects->data;
		for( ; i < arrayData->num; i++ )
		{
			GameObject* go = dynamic_cast<GameObject*>(arrayData->arr[i]);

			if(go && go->shouldReleased)
			{
				childrenToRemove->addObject(go);
			}
		}

		// remove 
		if(childrenToRemove->count() > 0)
		{
			int i = 0;
			ccArray *arrayData = childrenToRemove->data;
			for( ; i < arrayData->num; i++ )
			{
				gameObjects->removeObject(arrayData->arr[i]);
			}
		}
		childrenToRemove->removeAllObjects();
	}
}

void CCDrawGameObjectShadowNode::visit()
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

	CCNode* pNode = NULL;
	unsigned int i = 0;

	///////////////
	// draw shadow
	///////////////
	// remove should released gameObject
	if(gameObjects && gameObjects->count() > 0)
	{
		removeShouldReleasedGameObject();

		for(i =0; i < gameObjects->data->num; i++)
		{
			GameObject* go = dynamic_cast<GameObject*>(gameObjects->data->arr[i]);
			if(go)
				go->visitShadow();
		}
	}

	if(m_pChildren && m_pChildren->count() > 0)
	{
		sortAllChildren();
		// draw children zOrder < 0
		ccArray *arrayData = m_pChildren->data;
		for( ; i < arrayData->num; i++ )
		{
			pNode = (CCNode*) arrayData->arr[i];

			if ( pNode && pNode->getZOrder() < 0 ) 
			{
				pNode->visit();
			}
			else
			{
				break;
			}
		}
		// self draw
		this->draw();

		for( ; i < arrayData->num; i++ )
		{
			pNode = (CCNode*) arrayData->arr[i];
			if (pNode)
			{
				pNode->visit();
			}
		}        
	}
	else
	{
		this->draw();
	}

	// reset for next frame
	m_uOrderOfArrival = 0;

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}


