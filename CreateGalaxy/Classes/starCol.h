#ifndef STARCOL_H
#define STARCOL_H

#include "cocos2d.h"
#include "Star.h"
#include "GamingScene.h"
#include <vector>

USING_NS_CC;

class starCol : public ActionInterval
{
public:
	//  
	// Overrides  
	//  
	bool initWithDuration(float duration);
	virtual void startWithTarget(cocos2d::Node *target) override;
	virtual void update(float dt) override;

public:
	static starCol * create(float duration);
	float getDuration();
private:
	float m_duration;
};

#endif
