//
//  StartScene.h
//  Create_Galaxy
//
//  Created by 温泽 on 2016/8/22.
//
//

#ifndef StartScene_h
#define StartScene_h
#include "cocos2d.h"

USING_NS_CC;

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene * createScene();
    bool init();
    
    CREATE_FUNC(StartScene);
private:
    Sprite * logo;
    Menu * startLabelMenu;
    void onStartLabelMenuItemCallback(Ref*);
    int TextureNumber;
    void initHasDown();
    void onTextureLoading(float dt);
};


#endif /* StartScene_h */
