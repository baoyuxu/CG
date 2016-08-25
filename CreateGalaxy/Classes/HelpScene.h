//
//  HelpScene.h
//  CreateGalaxy
//
//  Created by 温泽 on 2016/8/23.
//
//

#ifndef HelpScene_h
#define HelpScene_h

#include "cocos2d.h"
USING_NS_CC;

class HelpScene : public cocos2d::Layer
{
public:
    HelpScene();
    virtual ~HelpScene();
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(HelpScene);
};

#endif /* HelpScene_h */
