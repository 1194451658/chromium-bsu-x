
#include "XflParser.h"

XflParser* XflParser::_sharedInstance = NULL;

XflParser::XflParser()
{
	libRootDir =  CCFileUtils::sharedFileUtils()->fullPathForFilename("Resources/xfl/LIBRARY");
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
	loadXmlToMap(libRootDir, "trigger/enemyStraightTrigger2.xml", triggerDefs);

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
		CCLOG("XflParser::loadXmlToMap file %s not exist !", xmlFilePath);
	}
}
