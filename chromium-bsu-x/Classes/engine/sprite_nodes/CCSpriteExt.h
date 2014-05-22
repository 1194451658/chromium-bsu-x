
#ifndef __CCSpriteExt_EXT_H__
#define __CCSpriteExt_EXT_H__

#include "AppMacros.h"

#ifdef CCSpriteExt
#undef CCSpriteExt
#endif // CCSpriteExt


USING_NS_CC;

class CCSpriteExt : public CCSprite
{
	// duplicate create function with new class CCSpriteExt
public:
	static CCSpriteExt* create();
    static CCSpriteExt* create(const char *pszFileName);
    static CCSpriteExt* create(const char *pszFileName, const CCRect& rect);
    static CCSpriteExt* createWithTexture(CCTexture2D *pTexture);
    static CCSpriteExt* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
    static CCSpriteExt* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
    static CCSpriteExt* createWithSpriteFrameName(const char *pszSpriteFrameName);

	// change setTextureCoords from "protected" to "public"
public:
	virtual void setTextureCoords(CCRect rect);
};

#endif