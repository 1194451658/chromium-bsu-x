
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


#include "engine/tinyxml2/tinyxml2utils.h"
#include <stdlib.h>
#include "TestTinyXml.h"

USING_NS_CC;


CCScene* TestTinyXml::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	TestTinyXml *layer = TestTinyXml::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestTinyXml::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	float top = origin.y + visibleSize.height;

	CCPoint center = ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);

	// title 
	CCLabelTTF* title = CCLabelTTF::create();
	title->setString("Test Tiny XML");
	title->setPosition(ccp(center.x, top - 50 ));
	addChild(title);


	CCMenu* menu = CCMenu::create();
	addChild(menu);

	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("manul create xml & write", this, menu_selector(TestTinyXml::testManualCreateAndWrite));
		menu->addChild(menuItem);
	}

	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("read manual created xml", this, menu_selector(TestTinyXml::testReadManualCreatedXml));
		menu->addChild(menuItem);
	}

	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("first child element", this, menu_selector(TestTinyXml::testFirstChildElement));
		menu->addChild(menuItem);
	}

	{
		CCMenuItemFont* menuItem = CCMenuItemFont::create("test tinyxml2utils recursively ", this, menu_selector(TestTinyXml::testRecursivelyFirstChild));
		menu->addChild(menuItem);
	}

	menu->alignItemsVertically();

	return true;
}
void TestTinyXml::testManualCreateAndWrite(CCObject* pSender)
{
	tinyxml2::XMLDocument doc;

	// declaration 
	tinyxml2::XMLDeclaration* decl = doc.NewDeclaration("this is declaration");
	doc.InsertEndChild(decl);
	

	// top element
	tinyxml2::XMLElement* element0 = doc.NewElement("level-0");
	doc.InsertEndChild(element0);

	tinyxml2::XMLElement* element11 = doc.NewElement("level-1-1");
	element0->InsertEndChild(element11);

	// comment
	tinyxml2::XMLComment* document = doc.NewComment("this is comment !");
	doc.InsertEndChild(document);


	string fileFolderFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("test").c_str();
	if(fileFolderFullPath != "")
	{
		string fileFullPath = fileFolderFullPath + "/testTinyXml.xml";
			doc.SaveFile(fileFullPath.c_str());
	}
}

	void TestTinyXml::testReadManualCreatedXml(CCObject* pSender)
	{
		tinyxml2::XMLDocument doc;

		string fileFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("test/testTinyXml.xml");

		if(fileFullPath != "")
		{
			doc.LoadFile(fileFullPath.c_str());

			// find second element
			tinyxml2::XMLElement* firstElement = doc.FirstChildElement("level-1-1");
			if(firstElement)
			{
				CCLOG("level-1-1 found !");
			}else
			{
				CCLOG("level-1-1 not found !");
			}

			// find first elemtn ,then second element
			tinyxml2::XMLElement* secondElement = doc.FirstChildElement("level-0")->FirstChildElement("level-1-1");
			if(secondElement)
			{
				CCLOG("level-1-1 found !");
			}
			else
			{
				CCLOG("level-1-1 not found !");
			}
		}
	}

void TestTinyXml::testFirstChildElement(CCObject* pSender)
{
	tinyxml2::XMLDocument doc;

	string fileFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("test/testTinyXml.xml");

	if(fileFullPath != "")
	{
		doc.LoadFile(fileFullPath.c_str());

		// find second element
		tinyxml2::XMLElement* firstElement = doc.FirstChildElement();
		if(firstElement)
		{
			CCLOG("first element name : %s", firstElement->Name());
		}
	}
}

void TestTinyXml::testRecursivelyFirstChild(CCObject* pSender)
{
	tinyxml2::XMLDocument doc;

	string fileFullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("test/testTinyXml.xml");

	if(fileFullPath != "")
	{
		doc.LoadFile(fileFullPath.c_str());

		// find second element
		const tinyxml2::XMLElement* firstElement = firstChildElementRecursively(&doc, "level-1-1");
		if(firstElement)
		{
			CCLOG("first element name : %s found !", firstElement->Name());
		}else
		{
			CCLOG("level-1-1 not recursively found");
		}
	}
}

