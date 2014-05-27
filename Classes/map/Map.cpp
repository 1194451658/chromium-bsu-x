
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


#include "Map.h"
#include "trigger/EnterScreenTrigger.h"
#include "engine/xfl/XflParser.h"

#include <string>

using namespace std;

Map* Map::create(tinyxml2::XMLDocument* mapDef)
{
	Map* newMap = new Map();

	if(newMap && newMap->init(mapDef))
	{
		newMap->autorelease();
		return newMap;
	}

	return NULL;
}

Map::Map()
{
}

Map::~Map()
{
}

bool Map::init(tinyxml2::XMLDocument* mapDef)
{

	mapDef->Accept(this);

	return true;
}

bool 	Map::VisitEnter (const  tinyxml2::XMLElement & element, const  tinyxml2::XMLAttribute * attribute)
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


	// parse _contentSizeLayer layer
	if(strcmp(element.Name(), "DOMLayer") == 0 &&
		element.Attribute("name", "_contentSize"))
	{

		CCSize contentSize = parseSizeBasedOnTransformationPointAndScale(&element);
		setContentSize(contentSize);
		return false;
	}


	// parse DOMSymbolInstance
	if(strcmp(element.Name(), "DOMSymbolInstance") == 0)
	{
		const char* libraryItemName = element.Attribute("libraryItemName");
		string libraryItemNameStr = string(libraryItemName) + ".xml";

		// check if it's trigger, create trigger with xfl.
		{
			std::size_t pos = libraryItemNameStr.find("trigger/");

			if(pos == 0)
			{
				map<string, tinyxml2::XMLDocument*>::iterator triggerDef = XflParser::sharedInstance()->triggerDefs.find(libraryItemNameStr.c_str());

				if(triggerDef != XflParser::sharedInstance()->triggerDefs.end())
				{

					EnterScreenTrigger* trigger = EnterScreenTrigger::create(triggerDef->second);
					// get & set pos 
					MatrixElement matrix = parseMatrixElement(&element);
					trigger->setPosition(ccp(matrix.tx, -matrix.ty));
					addChild(trigger);
				}else
				{
					// trigger not found !!
					CCLOG("Map::init library trigger not found : %s", libraryItemNameStr.c_str());
				}
			}
		}

		// check if it's prefab, create trigger with single prefab
		{
			std::size_t pos = libraryItemNameStr.find("prefab/");

			if(pos == 0)
			{
				// get & set pos
				MatrixElement matrix = parseMatrixElement(&element);
				CCSize size = parseSizeBasedOnTransformationPointAndScale(&element);

				EnterScreenTrigger* trigger = EnterScreenTrigger::create(libraryItemNameStr, size);
				trigger->setPosition(ccp(matrix.tx + size.width/2, -matrix.ty - size.height/2));
				addChild(trigger);
			}
		}

		return false;
	}

	return true;
}