//
//  StartScene.h
//  Create_Galaxy
//
//  Created by Thomas and his friends on 2016/8/22.
//
//

#ifndef StartScene_h
#define StartScene_h
#include "cocos2d.h"

USING_NS_CC;

class StartScene : public cocos2d::Layer
{
public:
    StartScene();
    virtual ~StartScene();
    static cocos2d::Scene * createScene();
    bool init();
    
    CREATE_FUNC(StartScene);
private:
    Sprite * logo;
    Menu * startSceneLabelMenu;
    Menu * startSceneImageMenu;
    
    void onStartLabelMenuItemCallback( Ref*);
    void onHelpLabelMenuItemCallback( Ref*);
    void onExitLabelMenuItemCallback( Ref*);
    
    int TextureNumber;
    void initHasDown();
    void onTextureLoading(float dt);
};


#endif /* StartScene_h */
