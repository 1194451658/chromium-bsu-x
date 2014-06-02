

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

#ifndef __XML_PARSER_H__
#define __XML_PARSER_H__

#include <string>
#include <map>

#include "AppMacros.h"

USING_NS_CC;

using namespace std;

class XflParser
{
public:
	~XflParser();
	static XflParser* sharedInstance();
	static void sharedInstanceCleanUp();

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

//
// tinyxml2 utility for parse xfl.
//

typedef struct	_matrixElement
{
	float tx;
	float ty;
	float a;	// scale x
	float b;	// scale y

	_matrixElement()
	{
		a = 1;
		b = 1;
		tx = 0;
		ty = 0;
	}
} MatrixElement;

MatrixElement parseMatrixElement(const tinyxml2::XMLNode* node);
CCPoint parseTransformationPoint(const tinyxml2::XMLNode* node);
CCSize parseSizeBasedOnTransformationPointAndScale(const tinyxml2::XMLNode* node);


#endif