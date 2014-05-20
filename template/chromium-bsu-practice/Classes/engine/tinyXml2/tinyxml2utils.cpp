

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