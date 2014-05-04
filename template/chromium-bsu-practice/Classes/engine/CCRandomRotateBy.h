

#ifndef __CCRANDOMROTATEBY_H__
#define __CCRANDOMROTATEBY_H__

#include "cocos2d.h"

USING_NS_CC;

class CCRandomRotateBy : public CCActionInterval
{
public:

	static CCRandomRotateBy* create(float duration, float angleVar)
	{
		CCRandomRotateBy* seq = new CCRandomRotateBy();
		if(seq && seq->initWithDuration(duration, angleVar))
		{

			seq->autorelease();
			return seq;
		}

		return NULL;
	}


	bool initWithDuration(float duration, float angleVar)
	{
		if(CCActionInterval::initWithDuration(duration))
		{
			this->angleVar = angleVar;
			return true;
		}

		return false;
	}

	void update(float time)
	{
		float angle = CCRANDOM_MINUS1_1() * angleVar;
		this->m_pTarget->setRotation(angle);
	}

private:
	float angleVar;
};

#endif



