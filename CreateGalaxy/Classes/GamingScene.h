//
//  GamingScene.h
//  CreateGalaxy
//
//  Created by 温泽 on 2016/8/26.
//
//

#ifndef GamingScene_h
#define GamingScene_h

#include "cocos2d.h"

USING_NS_CC;

class GamingScene : public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC( GamingScene );
private:
};


#endif /* GamingScene_h */
