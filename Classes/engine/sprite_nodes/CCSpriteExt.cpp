
#include "CCSpriteExt.h"

CCSpriteExt* CCSpriteExt::createWithTexture(CCTexture2D *pTexture)
{
	CCSpriteExt *pobSprite = new CCSpriteExt();
	if (pobSprite && pobSprite->initWithTexture(pTexture))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSpriteExt* CCSpriteExt::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
	CCSpriteExt *pobSprite = new CCSpriteExt();
	if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSpriteExt* CCSpriteExt::create(const char *pszFileName)
{
	CCSpriteExt *pobSprite = new CCSpriteExt();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSpriteExt* CCSpriteExt::create(const char *pszFileName, const CCRect& rect)
{
	CCSpriteExt *pobSprite = new CCSpriteExt();
	if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSpriteExt* CCSpriteExt::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
	CCSpriteExt *pobSprite = new CCSpriteExt();
	if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCSpriteExt* CCSpriteExt::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = {0};
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

CCSpriteExt* CCSpriteExt::create()
{
	CCSpriteExt *pSprite = new CCSpriteExt();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

void CCSpriteExt::setTextureCoords(CCRect rect)
{
	CCSprite::setTextureCoords(rect);
}
