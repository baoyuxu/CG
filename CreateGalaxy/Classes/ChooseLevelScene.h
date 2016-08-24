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
private:
    Menu * icon;
    
    void callBack1_0(Ref*);
    void callBack1_1(Ref*);
    void callBack1_2(Ref*);
    void callBack1_3(Ref*);
    void callBack1_4(Ref*);
    void callBack1_5(Ref*);
};

#endif /* ChooseLevelScene_h */
