//
//  GamingScene.h
//  CreateGalaxy
//
//  Created by Thomas and his friends on 2016/8/26.
//
//

#ifndef GamingScene_h
#define GamingScene_h

#include <string>
#include <vector>
#include <map>
#include "cocos2d.h"
#include "Star.h"
#include "CircleAction.h"
#include "starCol.h"

USING_NS_CC;

typedef struct 
{
	Star* star;
	float dis;
} starWithDistacne;

class GamingScene : public Layer
{
public:
    static cocos2d::Scene* createScene(int sceneNumber, int levelNumber);
    virtual bool init(int sceneNumber, int levelNumber);
	std::vector<Star*> starSprite;
	virtual void update(float delta);

	void gameEnd();
	CREATE_FUNC_XU(GamingScene);

private:
	static const std::string levelChoose[2][3];
	static const int starNumber[2][3];
	int sceneNumber;
	int levelNumber;
	int score;
	int starLeftNumber;
	bool isFlying;
	float minDistance;
	cocos2d::Node* layerNode;
	std::vector<cocos2d::Node*> starAimNode;
	std::map<cocos2d::Node*, starWithDistacne*> starStarMap;
	CircleMoveAction * act;

	void starLaunch();
	bool onTouchBegan(Touch*, Event*);
	void computerAim(std::vector<cocos2d::Node*>::iterator it);
	std::vector<cocos2d::Node*>::iterator judgeAimed();
};

#endif /* GamingScene_h */
