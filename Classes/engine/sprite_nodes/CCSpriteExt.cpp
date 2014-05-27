
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
