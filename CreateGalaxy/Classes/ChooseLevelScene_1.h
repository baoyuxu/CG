//
//  ChooseLevelScene_1.h
//  CreateGalaxy
//
//  Created by 温泽 on 2016/8/24.
//
//

#ifndef ChooseLevelScene_1_h
#define ChooseLevelScene_1_h

#include "cocos2d.h"
USING_NS_CC;

class ChooseLevelScene_1 : public Layer
{
public:
    ChooseLevelScene_1();
    virtual ~ChooseLevelScene_1();
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC( ChooseLevelScene_1 );
private:
    Menu * icon_0;
    Menu * icon_1;
    
    void callBackBack(Ref*);
    void callBack2_0(Ref*);
    void callBack2_1(Ref*);
    void callBack2_2(Ref*);
    void callBack2_3(Ref*);
    void callBack2_4(Ref*);
    void callBack2_5(Ref*);
};

#endif /* ChooseLevelScene_1_h */
