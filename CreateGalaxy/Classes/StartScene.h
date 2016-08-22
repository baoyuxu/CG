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

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene * createScene();
    bool init();
    
    CREATE_FUNC(StartScene);
private:
    void onTextureLoading(float dt);
    cocos2d::Sprite * logo;
    int TextureNumber;
};


#endif /* StartScene_h */
