#include "CircleAction.h"

CircleMoveAction* CircleMoveAction::create(float duration, const cocos2d::Point& center, float radius, float angle, float moveTimes)
{
	CircleMoveAction *pRet = new CircleMoveAction();

	if (pRet && pRet->initWithDuration(duration, center, radius, angle, moveTimes))
	{
		pRet->autorelease();

		return pRet;
	}

	CC_SAFE_DELETE(pRet);

	return nullptr;
}

bool CircleMoveAction::initWithDuration(float duration, const cocos2d::Point& center, float radius, float angle, float moveTimes)
{
	if (CCActionInterval::initWithDuration(duration * 2))
	{
		this->m_circleCenter = center;
		this->m_circleRadius = radius;
		this->m_duration = duration;
		this->m_angle = angle;
		this->m_moveTimes = moveTimes;

		this->m_radian = angle / duration * Director::getInstance()->getAnimationInterval() / (180 / M_PI);

		return true;
	}
	return false;
}

void CircleMoveAction::startWithTarget(cocos2d::Node *target)
{
	CCActionInterval::startWithTarget(target);
}


void CircleMoveAction::update(float dt)
{
	float radian = m_radian*m_moveTimes;

	float x = m_circleRadius*sin(radian);
	float y = m_circleRadius*cos(radian);

	Point newPoint = Point(m_circleCenter.x + x, m_circleCenter.y + y);
	_target->setPosition(newPoint);

	m_moveTimes++;
}

float CircleMoveAction::getAngle()
{
	return m_angle*m_moveTimes;
}
float CircleMoveAction::getRadian()
{
	return m_duration;
}
float CircleMoveAction::getMovetime()
{
	return m_moveTimes;
}
Point CircleMoveAction::getCenter()
{
	return m_circleCenter;
}
float CircleMoveAction::getRadious()
{
	return m_circleRadius;
}
