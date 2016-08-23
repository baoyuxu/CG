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
    
    auto rootnode = CSLoader::createNode(".//StartScene//StartScene.csb");
    addChild(rootnode);
    
    TextureNumber = 0;
    int * pTextureNum = &TextureNumber;
    
    auto addTextureCallback = [pTextureNum](Texture2D* texture)
    {
        (*pTextureNum)++;
        log("load the logo");
    };

    Director::getInstance()->getTextureCache()->addImageAsync( ".//StartScene//logo_1.png" , addTextureCallback );
    
    schedule(schedule_selector(StartScene::onTextureLoading));
    
    
//    logo = static_cast<Sprite*>( rootnode->getChildByName("logo") );
    
//    auto call = CallFunc::create(  [this](){
//        logo->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(".//StartScene//logo.png"));
//    }   );
    
    return true;
}

void StartScene::onStartLabelMenuItemCallback(Ref*)
{
//    auto scene = ChooseLevelScene::createScene();
//    Director::getInstance()->replaceScene(scene);
}

void StartScene::onTextureLoading(float dt)
{
    log("%f", dt);
    if( TextureNumber == 1 )
    {
        log("load Has Done");
        unschedule(schedule_selector(StartScene::onTextureLoading));
        this->initHasDown();
    }
}

void StartScene::initHasDown()
{
    logo = Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey(".//StartScene//logo_1.png") ) ;
    logo->setVisible(false);
    addChild(logo);
    logo->setScale(.8, .6);
    logo->setPosition(Vec2( Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
    auto call_1 = CallFunc::create( [this](){ logo->setVisible(true); } ) ;
    logo->runAction( Sequence::create( FadeOut::create(0), call_1,FadeIn::create(1) , MoveTo::create(0.7, Vec2( logo->getPositionX() ,  0.75*Director::getInstance()->getVisibleSize().height ) ) ,  nullptr)  );
    
    auto startLabel = Label::createWithTTF("Start", ".//fonts//Start.ttf", 70);
    startLabel->setTextColor(Color4B::WHITE );
    auto startLabelMenuItem = MenuItemLabel::create( startLabel);
    startLabelMenuItem->setTarget(this, menu_selector( StartScene::onStartLabelMenuItemCallback ));
    startLabelMenu = Menu::create( startLabelMenuItem, nullptr);
    startLabelMenu->setVisible(false);
    addChild(startLabelMenu);
    auto call_2 = CallFunc::create( [this](){ startLabelMenu->setVisible(true); } );
    startLabelMenu->runAction( Sequence::create(FadeOut::create(0), call_2 ,DelayTime::create(1) ,FadeIn::create(2), nullptr) );
}

