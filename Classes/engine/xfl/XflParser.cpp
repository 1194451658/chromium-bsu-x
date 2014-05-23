
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

#include "XflParser.h"
#include "engine/tinyxml2/tinyxml2utils.h"

XflParser* XflParser::_sharedInstance = NULL;

XflParser::XflParser()
{
	libRootDir =  CCFileUtils::sharedFileUtils()->fullPathForFilename("xfl/LIBRARY");
	//libPrefabDir = libRootDir + "/prefab/";
	//libTriggerDir = libRootDir + "/trigger/";
	//libMapDir = libRootDir + "/map/";

	initLoaded = false;
}

XflParser::~XflParser()
{
	if(_sharedInstance)
	{
		delete _sharedInstance;
		_sharedInstance = NULL;
	}
}


XflParser* XflParser::sharedInstance()
{
	if(!_sharedInstance)
	{

		XflParser* newParser = new XflParser();
		newParser->initialLoad();
		_sharedInstance = newParser;
	}

	return _sharedInstance;
}


// init load 

void XflParser::initialLoad()
{
	if(initLoaded == true)
		return;

	initLoaded = true;

	// load prefabs
	loadXmlToMap(libRootDir, "prefab/enemy/enemyBoss00.xml", prefabDefs);
	loadXmlToMap(libRootDir, "prefab/enemy/enemyBoss02.xml", prefabDefs);
	loadXmlToMap(libRootDir, "prefab/enemy/enemyOmni.xml", prefabDefs);
	loadXmlToMap(libRootDir, "prefab/enemy/enemyRayGun.xml", prefabDefs);
	loadXmlToMap(libRootDir, "prefab/enemy/enemyStraight.xml", prefabDefs);
	loadXmlToMap(libRootDir, "prefab/enemy/enemyTank.xml", prefabDefs);
	loadXmlToMap(libRootDir, "prefab/enemy/hero.xml", prefabDefs);

	// load trigger
	loadXmlToMap(libRootDir, "trigger/enemyStraightTrigger.xml", triggerDefs);
	loadXmlToMap(libRootDir, "trigger/enemyStraightTrigger1.xml", triggerDefs);
	loadXmlToMap(libRootDir, "trigger/enemyStraightTrigger2.xml", triggerDefs);
	loadXmlToMap(libRootDir, "trigger/enemyStraightTrigger3.xml", triggerDefs);

	// load map
	loadXmlToMap(libRootDir, "map/testMap.xml", mapDefs);
	loadXmlToMap(libRootDir, "map/map1.xml", mapDefs);
}

void XflParser::loadXmlToMap(string& rootDir, char* relativeFilePath, map<string, tinyxml2::XMLDocument*>& toMap)
{
	string xmlFilePath = string(rootDir) + "/" + relativeFilePath;

	if(CCFileUtils::sharedFileUtils()->isFileExist(xmlFilePath.c_str()))
	{
		tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
		doc->LoadFile(xmlFilePath.c_str());
		toMap.insert(pair<const char*, tinyxml2::XMLDocument*>(relativeFilePath, doc));
		CCLOG("XflParser::loadXmlToMap load xml file: %s", relativeFilePath);
	}else
	{
		CCLOG("XflParser::loadXmlToMap file %s not exist !", xmlFilePath.c_str());
	}
}




MatrixElement parseMatrixElement(const tinyxml2::XMLNode* node)
{
	MatrixElement matrix;

	const tinyxml2::XMLElement* matrixElement = firstChildElementRecursively(node, "Matrix");

	if(! matrixElement)
	{
		return matrix;
	}

	// parse tx, ty
	matrixElement->QueryFloatAttribute("tx", &matrix.tx);
	matrixElement->QueryFloatAttribute("ty", &matrix.ty);
	matrixElement->QueryFloatAttribute("a", &matrix.a);
	matrixElement->QueryFloatAttribute("b", &matrix.b);

	return matrix;
}

CCPoint parseTransformationPoint(const tinyxml2::XMLNode* node)
{
	CCPoint point;

	const tinyxml2::XMLElement* pointElement = firstChildElementRecursively(node, "Point");
	if(!pointElement)
		return point;

	// parse point
	pointElement->QueryFloatAttribute("x", &point.x);
	pointElement->QueryFloatAttribute("y", &point.y);

	return point;
}

CCSize parseSizeBasedOnTransformationPointAndScale(const tinyxml2::XMLNode* node)
{
	MatrixElement matrix = parseMatrixElement(node);
	CCPoint point = parseTransformationPoint(node);

	CCSize size;

	size.width = point.x * matrix.a * 2;
	size.height = point.y * matrix.b * 2;

	return size;
}
