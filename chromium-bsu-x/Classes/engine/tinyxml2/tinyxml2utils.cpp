
#include "tinyxml2utils.h"

const tinyxml2::XMLElement* firstChildElementRecursively(const tinyxml2::XMLNode* root, char* childElementName)
{
	//
	const tinyxml2::XMLElement* curChildElement = root->FirstChildElement();

	while(curChildElement)
	{
		if(strcmp(curChildElement->Name(), childElementName) == 0)
		{
			return curChildElement;
		}

		const tinyxml2::XMLElement* grandChild = firstChildElementRecursively(curChildElement, childElementName);
		if(grandChild)
			return grandChild;

		curChildElement = curChildElement->NextSiblingElement();
	}

	return NULL;
}