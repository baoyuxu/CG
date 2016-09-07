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

USING_NS_CC;

class GamingScene : public Layer
{
public:
    static cocos2d::Scene* createScene(int sceneNumber, int levelNumber);
    virtual bool init(int sceneNumber, int levelNumber);
    
	static GamingScene* create(int sceneNumber, int levelNumber) 
	{ 
		GamingScene *pRet = new(std::nothrow) GamingScene(); 
		if (pRet && pRet->init(sceneNumber, levelNumber)) 
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			delete pRet;
			pRet = nullptr; 
			return nullptr; 
		} 
	}

	//CREATE_FUNC_XU(GamingScene);

private:
	static const std::string levelChoose[2][3];
	static const int starNumber[2][3];
	int sceneNumber;
	int levelNumber;
	bool isFlying;
	float minDistance;
	float minX;
	float minY;
	std::vector<Star*> starSprite;
	std::vector<cocos2d::Node*> starAimNode;
	std::map<cocos2d::Node*, Star*> starStarMap;

	void starLaunch();
	bool onTouchBegan(Touch*, Event*);
	bool judgeAimed();
};


#endif /* GamingScene_h */
