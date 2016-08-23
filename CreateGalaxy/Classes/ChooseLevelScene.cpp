//
//  ChooseLevelScene.cpp
//  CreateGalaxy
//
//  Created by 温泽 on 2016/8/23.
//
//

#include "ChooseLevelScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


cocos2d::Scene * ChooseLevelScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ChooseLevelScene::create();
    scene->addChild(layer);
    return scene;
}

bool ChooseLevelScene::init()
{
    return true;
}