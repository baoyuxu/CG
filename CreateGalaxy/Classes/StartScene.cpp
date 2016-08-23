//
//  StartScene.cpp
//  Create_Galaxy
//
//  Created by 温泽 on 2016/8/22.
//
//

#include "StartScene.h"
#include "ChooseLevelScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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
    
    auto startLabel = Label::createWithTTF("Start", ".//fonts//Start.ttf", 70);
    startLabel->setTextColor(Color4B::WHITE );
    auto startLabelMenuItem = MenuItemLabel::create( startLabel);
    startLabelMenuItem->setTarget(this, menu_selector( StartScene::onStartLabelMenuItemCallback ));
    auto startLabelMenu = Menu::create( startLabelMenuItem, nullptr);
    auto fadein = FadeIn::create(2);
    auto fadeout = FadeOut::create(0);
    startLabelMenu->runAction( Sequence::create(fadeout, fadein, nullptr) );
    addChild(startLabelMenu);
    
    logo->runAction( MoveTo::create(0.7, Vec2( logo->getPositionX() ,  0.75*Director::getInstance()->getVisibleSize().height ) ) );
    
    return true;
}

void StartScene::onStartLabelMenuItemCallback(Ref*)
{
//    auto scene = ChooseLevelScene::createScene();
//    Director::getInstance()->replaceScene(scene);
}



