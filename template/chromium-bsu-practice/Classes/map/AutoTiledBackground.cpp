
#include "AutoTiledBackground.h"

AutoTiledBackground* AutoTiledBackground::create(const char *pszFileName)
{
	AutoTiledBackground *pobSprite = new AutoTiledBackground();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();

		// vertex shader
		const GLchar* vertexShader = 
		"													\n\
		attribute vec4 a_position;							\n\
		attribute vec2 a_texCoord;							\n\
		attribute vec4 a_color;								\n\
		\n\
		#ifdef GL_ES										\n\
		varying lowp vec4 v_fragmentColor;					\n\
		varying mediump vec2 v_texCoord;					\n\
		#else												\n\
		varying vec4 v_fragmentColor;						\n\
		varying vec2 v_texCoord;							\n\
		varying vec4 v_position;							\n\
		#endif												\n\
		\n\
		void main()											\n\
		{													\n\
			gl_Position = CC_MVPMatrix * a_position;		\n\
			v_fragmentColor = a_color;						\n\
			v_texCoord = a_texCoord;						\n\
			v_position = a_position;						\n\
		}													\n\
		";

		// create shader 
		const GLchar* fragShader = 
			"													\n\
			#ifdef GL_ES										\n\
			precision lowp float;								\n\
			#endif												\n\
			\n\
			varying vec4 v_fragmentColor;						\n\
			varying vec2 v_texCoord;							\n\
			varying vec4 v_position;							\n\
			uniform sampler2D CC_Texture0;						\n\
			uniform float textureWidth;							\n\
			uniform float textureHeight;						\n\
			uniform float textureCoordLeft;						\n\
			uniform float textureCoordRight;					\n\
			uniform float textureCoordTop;						\n\
			uniform float textureCoordBottom;					\n\
			\n\
			\n\
			void main()											\n\
			{													\n\
				float widthPercent = mod(v_position.x, textureWidth) / textureWidth;						\n\
				float heightPercent = mod(v_position.y, textureHeight) / textureHeight;						\n\
				float texCoordX = textureCoordLeft * (1-widthPercent) + textureCoordRight * widthPercent;	\n\
				float texCoordY = textureCoordBottom * (1-heightPercent) + textureCoordTop* heightPercent;	\n\
				\n\
				gl_FragColor = vec4( v_fragmentColor * texture2D(CC_Texture0, vec2(texCoordX, texCoordY)));	// A from texture & uniform		\n\
			}													\n\
			";

		CCGLProgram* shader = new CCGLProgram();
		shader->initWithVertexShaderByteArray(vertexShader, fragShader);
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

		shader->link();

		// get uniform location
		 pobSprite->textureWidthLoc = glGetUniformLocation(shader->getProgram(), "textureWidth");
		 pobSprite->textureHeightLoc = glGetUniformLocation(shader->getProgram(), "textureHeight");
		 pobSprite->textureCoordLeftLoc = glGetUniformLocation(shader->getProgram(), "textureCoordLeft");
		 pobSprite->textureCoordRighthLoc = glGetUniformLocation(shader->getProgram(), "textureCoordRight");
		 pobSprite->textureCoordTopLoc = glGetUniformLocation(shader->getProgram(), "textureCoordTop");
		 pobSprite->textureCoordBottomLoc = glGetUniformLocation(shader->getProgram(), "textureCoordBottom");

		 shader->updateUniforms();

		pobSprite->setShaderProgram(shader);

		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void AutoTiledBackground::draw()
{
	//  get visible area
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	// convert to self space
	// note: can get the transform from kmath.
	CCPoint topLeft = CCPoint(origin.x, origin.y + size.height);
	CCPoint topRight = CCPoint(origin.x + size.width, origin.y + size.height);
	CCPoint bottomLeft = CCPoint(origin.x, origin.y);
	CCPoint bottomRight = CCPoint(origin.x + size.width, origin.y);

	topLeft = convertToNodeSpace(topLeft);
	topRight = convertToNodeSpace(topRight);
	bottomLeft = convertToNodeSpace(bottomLeft);
	bottomRight = convertToNodeSpace(bottomRight);

	m_sQuad.tl.vertices = vertex3(topLeft.x, topLeft.y, 0);
	m_sQuad.tr.vertices = vertex3(topRight.x, topRight.y, 0);
	m_sQuad.bl.vertices = vertex3(bottomLeft.x, bottomLeft.y, 0);
	m_sQuad.br.vertices = vertex3(bottomRight.x, bottomRight.y, 0);


	// CCSprite::draw();
	// -----------------------------

	CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
	CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
	CC_NODE_DRAW_SETUP();

	//GLint textureWidthLoc;
	//GLint textureHeightLoc;
	//GLint textureCoordLeftLoc;
	//GLint textureCoordRighthLoc;
	//GLint textureCoordTopLoc;
	//GLint textureCoordBottomLoc;

	CCGLProgram* shader = getShaderProgram();
	shader->setUniformLocationWith1f(textureWidthLoc, m_obRect.size.width);
	shader->setUniformLocationWith1f(textureHeightLoc, m_obRect.size.height);
	shader->setUniformLocationWith1f(textureCoordLeftLoc, m_sQuad.tl.texCoords.u);
	shader->setUniformLocationWith1f(textureCoordRighthLoc,m_sQuad.tr.texCoords.u);
	shader->setUniformLocationWith1f(textureCoordTopLoc,m_sQuad.tl.texCoords.v);
	shader->setUniformLocationWith1f(textureCoordBottomLoc, m_sQuad.bl.texCoords.v);

	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	ccGLBindTexture2D( m_pobTexture->getName() );
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
	long offset = 0;
	setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
	long offset = (long)&m_sQuad;
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