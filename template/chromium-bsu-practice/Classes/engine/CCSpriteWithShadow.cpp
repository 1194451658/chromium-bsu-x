
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

#include "CCSpriteWithShadow.h"

CCSpriteWithShadow* CCSpriteWithShadow::create(const char *pszFileName)
{
	CCSpriteWithShadow *pobSprite = new CCSpriteWithShadow();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		//
		pobSprite->shadowOffset = CCPoint(-50, -50);
		pobSprite->shadowScaleX = pobSprite->shadowScaleY = 1.0;

		//
		pobSprite->initShader();
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void CCSpriteWithShadow::initShader()
{
	CCGLProgram* shader = new CCGLProgram();

	const char* fragShader = 
		"											\n\
		#ifdef GL_ES								\n\
		precision lowp float;						\n\
		#endif										\n\
		\n\
		varying vec4 v_fragmentColor;				\n\
		varying vec2 v_texCoord;					\n\
		uniform sampler2D CC_Texture0;				\n\
		\n\
		void main()									\n\
		{											\n\
			vec4 texColor = texture2D(CC_Texture0, v_texCoord);						\n\
			vec4 finalColor;														\n\
			if((texColor.r > 0.0 || texColor.g > 0.0 || texColor.b > 0.0) &&		\n\
				texColor.a > 0.0)													\n\
				finalColor = vec4(0.0, 0.0, 0.0, texColor.a);						\n\
			else																	\n\
				//finalColor = vec4(0.0);											\n\
				discard;															\n\
			gl_FragColor = finalColor;												\n\
			// gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);								\n\
		}																			\n\
		";

	shader->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragShader);
	shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

	shader->link();
	shader->updateUniforms();

	shadowShaderProgram = shader;
	return ;
}

void CCSpriteWithShadow::drawShadow()
{
	
	// adjust shadow size && position
	m_sShadowQuad = m_sQuad;

	float originQuadWidth = m_sQuad.tr.vertices.x - m_sQuad.tl.vertices.x;
	float originQuadHeight = m_sQuad.tl.vertices.y - m_sQuad.bl.vertices.y;
	CCPoint originQuadCenter = CCPoint(m_sQuad.bl.vertices.x + originQuadWidth/2, m_sQuad.bl.vertices.y + originQuadHeight/2);

	float shadowWidth = originQuadWidth * shadowScaleX;
	float shadowHeight = originQuadHeight * shadowScaleY;
	CCPoint shadowCenter = originQuadCenter + shadowOffset;

	m_sShadowQuad.bl.vertices.x = shadowCenter.x - shadowWidth/2;
	m_sShadowQuad.bl.vertices.y = shadowCenter.y - shadowHeight/2;
	// m_sShadowQuad.bl.vertices.z = -0.5;

	m_sShadowQuad.br.vertices.x = shadowCenter.x + shadowWidth/2;
	m_sShadowQuad.br.vertices.y = shadowCenter.y - shadowHeight/2;
	// m_sShadowQuad.br.vertices.z = -0.5;

	m_sShadowQuad.tl.vertices.x = shadowCenter.x - shadowWidth/2;
	m_sShadowQuad.tl.vertices.y = shadowCenter.y + shadowHeight/2;
	// m_sShadowQuad.tl.vertices.z = -0.5;

	m_sShadowQuad.tr.vertices.x = shadowCenter.x + shadowWidth/2;
	m_sShadowQuad.tr.vertices.y = shadowCenter.y + shadowHeight/2;
	// m_sShadowQuad.tr.vertices.z = -0.5;

	// draw shadow first
	CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
	CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
	//CC_NODE_DRAW_SETUP();
	// use the shadow shader;
	
	CCAssert(shadowShaderProgram, "no shadow shader program");
	shadowShaderProgram->use();
	shadowShaderProgram->setUniformsForBuiltins();

	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	ccGLBindTexture2D( m_pobTexture->getName() );
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
	long offset = 0;
	setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
	long offset = (long)&m_sShadowQuad;
#endif // EMSCRIPTEN

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	// texCoods
	diff = offsetof( ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CHECK_GL_ERROR_DEBUG();


#if CC_SPRITE_DEBUG_DRAW == 1
	// draw bounding box
	CCPoint vertices[4]={
		ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
		ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
		ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
		ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
	};
	ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
	// draw texture box
	CCSize s = this->getTextureRect().size;
	CCPoint offsetPix = this->getOffsetPosition();
	CCPoint vertices[4] = {
		ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
		ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
	};
	ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW

	CC_INCREMENT_GL_DRAWS(1);

	CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}

void CCSpriteWithShadow::visitShadow()
{
	// quick return if not visible. children won't be drawn.
	if (!m_bVisible)
	{
		return;
	}
	kmGLPushMatrix();

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->beforeDraw();
	}

	this->transform();

	// CCNode* pNode = NULL;
	CCSpriteWithShadow* spriteWithShadow = NULL;

	unsigned int i = 0;

	if(m_pChildren && m_pChildren->count() > 0)
	{
		sortAllChildren();
		// draw children zOrder < 0
		ccArray *arrayData = m_pChildren->data;
		for( ; i < arrayData->num; i++ )
		{
			spriteWithShadow = dynamic_cast<CCSpriteWithShadow*>(arrayData->arr[i]);

			if ( spriteWithShadow && spriteWithShadow->m_nZOrder < 0 ) 
			{
				spriteWithShadow->visitShadow();
			}
			else
			{
				break;
			}
		}
		// self draw
		this->drawShadow();

		for( ; i < arrayData->num; i++ )
		{
			spriteWithShadow = dynamic_cast<CCSpriteWithShadow*>(arrayData->arr[i]);
			if (spriteWithShadow)
			{
				spriteWithShadow->visitShadow();
			}
		}        
	}
	else
	{
		this->drawShadow();
	}

	// reset for next frame
	// m_uOrderOfArrival = 0;

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}