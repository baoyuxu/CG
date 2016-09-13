#ifndef CIRCLEACTION_H
#define CIRCLEACTION_H
#include "cocos2d.h"

USING_NS_CC;

class CircleMoveAction : public cocos2d::ActionInterval
{
public:
	bool initWithDuration(float duration, const cocos2d::Point& center, float radius, float angle, float moveTimes);

	//  
	// Overrides  
	//  
	virtual void startWithTarget(cocos2d::Node *target) override;
	virtual void update(float dt) override;

public:
	static CircleMoveAction* create(float duration, const cocos2d::Point& center, float radius, float angle, float moveTimes);

public:
	//    CircleMoveAction();  
	//    ~CircleMoveAction();  
	//    void updateCircleCenter(Ref *pSender);  
	//    void unUpdateCircleCenter(Ref *pSender);  
private:
	//    CC_SYNTHESIZE(bool, onTouch, OnTouch);  
protected:
	cocos2d::Point m_circleCenter;    
	float m_circleRadius;    
	float m_radian;     
	float m_angle;     
	int m_moveTimes;  
	float m_duration;    
};

#endif // !CIRCLEACTION_H
