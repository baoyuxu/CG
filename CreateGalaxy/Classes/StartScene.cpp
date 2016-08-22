//
//  StartScene.cpp
//  Create_Galaxy
//
//  Created by 温泽 on 2016/8/22.
//
//

#include "StartScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

cocos2d::Scene * StartScene::createScene()
{
    auto scene = Scene::create();
    auto layer = StartScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool StartScene::init()
{
    if( !Layer::init() )
    {
        return false;
    }
    
    TextureNumber = 0;
    int * pTexNumber = &TextureNumber;
    
    auto rootnode = CSLoader::createNode(".//StartScene//StartScene.csb");
    addChild(rootnode);
    logo = static_cast<Sprite*>( rootnode->getChildByName("logo") );
    
    logo->runAction( MoveTo::create(0.7, Vec2( logo->getPositionX() ,  0.75*Director::getInstance()->getVisibleSize().height ) ) );
    
    //logo->runAction( MoveTo::create(30, Vec2( logo->getPositionX() ,1.5* ( logo->getPositionY() ) ) ) );
    
    //    auto addTextureCallBack = [pTexNumber](Texture2D* texture)
    //    {
    //        ++( * pTexNumber );
    //        log("Load a TexTure");
    //    };
    
    //Director::getInstance()->getTextureCache()->addImageAsync("", addTextureCallBack);
    
    return true;
}

void StartScene::onTextureLoading(float dt)
{
    
}

