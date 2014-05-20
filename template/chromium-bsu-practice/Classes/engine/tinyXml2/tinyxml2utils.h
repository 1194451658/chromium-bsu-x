
#ifndef __TINY_XML_2_UTILS_H__
#define __TINY_XML_2_UTILS_H__


#include "cocos2d.h"

USING_NS_CC;


const tinyxml2::XMLElement* firstChildElementRecursively(const tinyxml2::XMLNode* root, char* childElementName);

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