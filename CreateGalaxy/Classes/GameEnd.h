#ifndef GAMEEND_H
#define GAMEEND_H
#include "cocos2d.h"

USING_NS_CC;

class GameEnd : public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameEnd);
protected:
private:
};

#endif // !GAMEEND_H
