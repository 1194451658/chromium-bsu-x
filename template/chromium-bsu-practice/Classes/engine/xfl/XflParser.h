
#ifndef __XML_PARSER_H__
#define __XML_PARSER_H__

#include <string>
#include <map>

#include "cocos2d.h"

USING_NS_CC;

using namespace std;

class XflParser
{
public:
	~XflParser();
	static XflParser* sharedInstance();

	// init load 
	void initialLoad();
	void loadXmlToMap(string& rootDir, char* relativeFilePath, map<string, tinyxml2::XMLDocument*>& toMap);

	// create trigger



private:
	XflParser();

private:
	string libRootDir;
	//string libPrefabDir;
	//string libTriggerDir;
	//string libMapDir;

	bool initLoaded;

	static XflParser* _sharedInstance;

public:
	//
	map<string, tinyxml2::XMLDocument*> prefabDefs;
	map<string, tinyxml2::XMLDocument*> triggerDefs;
	map<string, tinyxml2::XMLDocument*> mapDefs;
};


#endif