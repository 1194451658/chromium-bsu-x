
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

#ifndef __MAP_H__
#define __MAP_H__


#include "cocos2d.h"

USING_NS_CC;


class Map : public CCNode, public tinyxml2::XMLVisitor
{

public:
	static Map* create(tinyxml2::XMLDocument* mapDef);

	Map();
	~Map();

	bool init(tinyxml2::XMLDocument* mapDef);


	virtual bool VisitEnter (const tinyxml2::XMLElement & element, const  tinyxml2::XMLAttribute * attribute);
};

#endif // !__MAP_H__
