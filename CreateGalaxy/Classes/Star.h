#ifndef STAR_H
#define STAR_H
#include "cocos2d.h"
USING_NS_CC;

class Star : public Sprite
{
public:
	Star();
	~Star();
	static Star * create();
	//Vec2 getPosition();
	void launch();
	void stop();
	void disappear();
private:
	bool init();
	float speed;
};

#endif // !STAR_H
