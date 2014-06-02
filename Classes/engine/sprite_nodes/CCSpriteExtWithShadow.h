
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


#ifndef __CCSpriteExt_WITH_SHADOW__
#define __CCSpriteExt_WITH_SHADOW__

#include "AppMacros.h"

USING_NS_CC;

class CCSpriteExtWithShadow : public CCSpriteExt
{
public:
	CCSpriteExtWithShadow();
	~CCSpriteExtWithShadow();
	void drawShadow();
	void visitShadow();
	static CCSpriteExtWithShadow* create(const char *pszFileName);

	void setShadowOffset(CCPoint& offset){ shadowOffset = offset;}
	void setShadowScale(float scale){ shadowScaleX = shadowScaleY = scale;}

private:
	void initShader();

private:
	ccV3F_C4B_T2F_Quad m_sShadowQuad;

	CCPoint shadowOffset;
	float shadowScaleX;
	float shadowScaleY;

	CCGLProgram* shadowShaderProgram;
};

#endif