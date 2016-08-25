//
//  StartScene.cpp
//  Create_Galaxy
//
//  Created by 温泽 on 2016/8/22.
//
//

#include "StartScene.h"
#include "ChooseLevelScene.h"
#include "HelpScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

StartScene::StartScene()
{
    
}

StartScene::~StartScene()
{
    
}

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
        log("load %d Texture", *pTextureNum );
    };

    Director::getInstance()->getTextureCache()->addImageAsync(".//StartScene//logo_1.png" , addTextureCallback );
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//1_0.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//1_1.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//1_2.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//1_3.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//1_4.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//1_5.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//2_0.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//2_1.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//2_2.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//2_3.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//2_4.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//2_5.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//ArrowRight.png", addTextureCallback);
    Director::getInstance()->getTextureCache()->addImageAsync(".//ChooseLevelScene//ArrowLeft.png", addTextureCallback);

    schedule(schedule_selector(StartScene::onTextureLoading));
    
    return true;
}

void StartScene::onStartLabelMenuItemCallback( Ref* )
{
    auto scene = ChooseLevelScene::createScene();
    Director::getInstance()->pushScene( scene );
    //Director::getInstance()->replaceScene(scene);
    log("onStartLabelMenuItemCallback");
}

void StartScene::onHelpLabelMenuItemCallback( Ref* )
{
    log("onHelpLabelMenuItemCallback");
}

void StartScene::onExitLabelMenuItemCallback( Ref* )
{
    log("onExitLabelMenuItemCallback");
    Director::getInstance()->end();
}

void StartScene::onTextureLoading(float dt)
{
    if( TextureNumber == 15 )
    {
        log("load Has Done");
        unschedule(schedule_selector(StartScene::onTextureLoading));
        this->initHasDown();
    }
}

void StartScene::initHasDown()
{
    Size visableSize = Director::getInstance()->getVisibleSize();
    logo = Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey(".//StartScene//logo_1.png") ) ;
    logo->setVisible(false);
    addChild(logo);
    logo->setScale(.8, .6);
    logo->setPosition(Vec2( visableSize.width / 2, visableSize.height / 2));
    auto call_1 = CallFunc::create( [this](){ logo->setVisible(true); } ) ;
    logo->runAction( Sequence::create( FadeOut::create(0), call_1, FadeIn::create(1.5), MoveTo::create(0.7, Vec2( logo->getPositionX(),  0.75*visableSize.height)),  nullptr)  );
    
    auto startLabel = Label::createWithTTF("Start", ".//fonts//Start.ttf", 70);
    startLabel->setTextColor(Color4B::WHITE );
    auto startLabelMenuItem = MenuItemLabel::create( startLabel, CC_CALLBACK_1( StartScene::onStartLabelMenuItemCallback, this));
//    auto helpLabel = Label::createWithTTF("Help", ".//fonts//Start.ttf", 70);
//    helpLabel->setTextColor(Color4B::WHITE);
//    auto helpLabelMenuItem = MenuItemLabel::create( helpLabel , CC_CALLBACK_1( StartScene::onHelpLabelMenuItemCallback, this ));
//    auto exitLabel = Label::createWithTTF("Exit", ".//fonts//Start.ttf", 70);
//    exitLabel->setTextColor(Color4B::WHITE);
//    auto exitLabelItem = MenuItemLabel::create( exitLabel , CC_CALLBACK_1( StartScene::onExitLabelMenuItemCallback, this)  );
    
//    startSceneLabelMenu = Menu::create( helpLabelMenuItem ,startLabelMenuItem, exitLabelItem, nullptr);
    startSceneLabelMenu = Menu::create( startLabelMenuItem, nullptr );
    startSceneLabelMenu->alignItemsHorizontallyWithPadding( visableSize.width / 7 );
    startSceneLabelMenu->setPositionY( visableSize.height * 0.35 );
    startSceneLabelMenu->setVisible(false);
    
    auto helpItem = MenuItemImage::create( ".//StartScene//help.png", ".//StartScene//help.png", CC_CALLBACK_1( StartScene::onHelpLabelMenuItemCallback, this ) );
    auto exitItem = MenuItemImage::create( ".//StartScene//exit.png", ".//StartScene//exit.png", CC_CALLBACK_1( StartScene::onExitLabelMenuItemCallback, this ) );
    startSceneImageMenu = Menu::create( helpItem, exitItem, nullptr);
    startSceneImageMenu->setScale( 0.1 );
    startSceneImageMenu->setPosition( Vec2( visableSize.width * 0.5, - visableSize.height * 0.4 ) );
    startSceneImageMenu->setVisible(false);
    startSceneImageMenu->alignItemsHorizontally();
    
    addChild(startSceneLabelMenu);
    addChild(startSceneImageMenu);
    auto call_2 = CallFunc::create( [this](){ startSceneLabelMenu->setVisible(true); } );
    auto call_3 = CallFunc::create( [this](){ startSceneImageMenu->setVisible(true); } );
    startSceneLabelMenu->runAction( Sequence::create(FadeOut::create(0), call_2, DelayTime::create(2), FadeIn::create(1.5), nullptr) );
    startSceneImageMenu->runAction( Sequence::create(FadeOut::create(0), call_3, DelayTime::create(2), FadeIn::create(1.5), nullptr) );
}

