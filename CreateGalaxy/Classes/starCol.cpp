#include "starCol.h"

starCol * starCol::create(float duration)
{
	starCol *pRet = new starCol();

	if (pRet && pRet->initWithDuration(duration))
	{
		pRet->autorelease();

		return pRet;
	}

	CC_SAFE_DELETE(pRet);

	return nullptr;
}

bool starCol::initWithDuration(float duration)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		this->m_duration = duration;
		return true;
	}

	return false;
}

void starCol::update(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 pos = _target->getPosition();
	if ( pos.x < 0 || pos.y < 0 || pos.x > size.width || pos.y > size.height )
	{
		static_cast<Star*>(_target)->disappear();
		log("out\n");
	}
}

float starCol::getDuration()
{
	return this->m_duration;
}

void starCol::startWithTarget(cocos2d::Node *target)
{
	CCActionInterval::startWithTarget(target);
}