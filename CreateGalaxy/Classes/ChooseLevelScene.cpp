//
//  ChooseLevelScene.cpp
//  CreateGalaxy
//
//  Created by Thomas and his friends on 2016/8/23.
//
//

#include "ChooseLevelScene.h"
#include "ChooseLevelScene_1.h"
#include "GamingScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include <vector>

ChooseLevelScene::ChooseLevelScene()
{
    
}

ChooseLevelScene::~ChooseLevelScene()
{
    
}

cocos2d::Scene * ChooseLevelScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ChooseLevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool ChooseLevelScene::init()
{
    if( !Layer::init() )
    {
        return  false;
    }
    
    auto rootnode = CSLoader::createNode(".//ChooseLevelScene//ChooseLevelScene.csb");
    addChild(rootnode);
    
    Vector<MenuItem*> menuItemSprites_0;
    Vector<MenuItem*> menuItemSprites_1;
    menuItemSprites_0.pushBack(
    MenuItemSprite::create( Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_0.png" ) ),
                            Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_0.png" ) ),
                            CC_CALLBACK_1( ChooseLevelScene::callBack1_0, this) ) );
    menuItemSprites_0.pushBack(
    MenuItemSprite::create( Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_1.png" ) ),
                            Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_1.png" ) ),
                            CC_CALLBACK_1( ChooseLevelScene::callBack1_1, this) ) );
    menuItemSprites_0.pushBack(
    MenuItemSprite::create( Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_2.png" ) ),
                            Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_2.png" ) ),
                            CC_CALLBACK_1( ChooseLevelScene::callBack1_2, this) ) );
    menuItemSprites_1.pushBack(
    MenuItemSprite::create( Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_3.png" ) ),
                            Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_3.png" ) ),
                            CC_CALLBACK_1( ChooseLevelScene::callBack1_3, this) ) );
    menuItemSprites_1.pushBack(
    MenuItemSprite::create( Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_4.png" ) ),
                            Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_4.png" ) ),
                            CC_CALLBACK_1( ChooseLevelScene::callBack1_4, this) ) );
    menuItemSprites_1.pushBack(
    MenuItemSprite::create( Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_5.png" ) ),
                            Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey( ".//ChooseLevelScene//1_5.png" ) ),
                            CC_CALLBACK_1( ChooseLevelScene::callBack1_5, this) ) );
    icon_0 = Menu::createWithArray( menuItemSprites_0 );
    icon_1 = Menu::createWithArray( menuItemSprites_1 );
    icon_0->alignItemsHorizontallyWithPadding( Director::getInstance()->getVisibleSize().width / 10 );
    icon_1->alignItemsHorizontallyWithPadding( Director::getInstance()->getVisibleSize().width / 10 );
    icon_0->setPositionY( Director::getInstance()->getVisibleSize().height * 0.7 );
    icon_1->setPositionY( Director::getInstance()->getVisibleSize().height * 0.35 );
    addChild(icon_0);
    addChild(icon_1);
    
    
//    auto ArrowRight = Menu::createWithItem(
//                    MenuItemSprite::create(
//                                           Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey(".//ChooseLevelScene//ArrowRight.png")) ,
//                                           Sprite::createWithTexture( Director::getInstance()->getTextureCache()->getTextureForKey(".//ChooseLevelScene//ArrowRight.png")),
//                                           CC_CALLBACK_1( ChooseLevelScene::callBackRightArrow, this) ));
//    ArrowRight->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.85, Director::getInstance()->getVisibleSize().height * 0.45 ) );
//    ArrowRight->setScale( 0.8 );
//    addChild( ArrowRight );
    
    auto RightArrow = cocos2d::ui::Button::create( ".//ChooseLevelScene//ArrowRight.png" );
    RightArrow->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.95, Director::getInstance()->getVisibleSize().height / 2 ) );
    RightArrow->Widget::setScale( 0.3 );
    RightArrow->addTouchEventListener(
                                      [&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
                                      {
                                          switch ( type )
                                          {
                                              case ui::Widget::TouchEventType::BEGAN:
                                                  log( "RightArrow" );
                                                  Director::getInstance()->replaceScene( TransitionSlideInL::create( .5, ChooseLevelScene_1::createScene() ) );
                                                  break;
                                              case ui::Widget::TouchEventType::ENDED:
                                                  break;
                                              case ui::Widget::TouchEventType::CANCELED:
                                                  break;
                                              case ui::Widget::TouchEventType::MOVED:
                                                  break;
                                          }
                                      } );
    addChild(RightArrow);
    
    auto backLabel = Label::createWithTTF( "Back" , ".//fonts//Start.ttf" , 50);
    backLabel->setTextColor( Color4B::WHITE );
    Menu * backMenu = Menu::createWithItem( MenuItemLabel::create( backLabel, CC_CALLBACK_1( ChooseLevelScene::callBackBack, this) ) );
    backMenu->setPosition( Vec2( Director::getInstance()->getVisibleSize().width * 0.95 , Director::getInstance()->getVisibleSize().height * 0.04) );
    addChild(backMenu);
    return true;
}

void ChooseLevelScene::callBack1_0(Ref*)
{
	Director::getInstance()->replaceScene(GamingScene::createScene(0, 0));
    log("callBack1_0");
}

void ChooseLevelScene::callBack1_1(Ref*)
{
    log("callBack1_1");
}

void ChooseLevelScene::callBack1_2(Ref*)
{
    log("callBack1_2");
}

void ChooseLevelScene::callBack1_3(Ref*)
{
    log("callBack1_3");
}

void ChooseLevelScene::callBack1_4(Ref*)
{
    log("callBack1_4");
}

void ChooseLevelScene::callBack1_5(Ref*)
{
    log("callBack1_5");
}

void ChooseLevelScene::callBackBack(Ref*)
{
    log("Back_0");
    Director::getInstance()->popScene();
}

