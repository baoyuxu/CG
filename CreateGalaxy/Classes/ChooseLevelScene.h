//
//  ChooseLevelScene.h
//  CreateGalaxy
//
//  Created by 温泽 on 2016/8/23.
//
//

#ifndef ChooseLevelScene_h
#define ChooseLevelScene_h
#include "cocos2d.h"
USING_NS_CC;

class ChooseLevelScene : public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(ChooseLevelScene);
};

#endif /* ChooseLevelScene_h */
