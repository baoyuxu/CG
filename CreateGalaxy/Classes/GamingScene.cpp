//
//  GamingScene.cpp
//  CreateGalaxy
//
//  Created by Thomas and his friends on 2016/8/26.
//
//
#include "GamingSCene.h"
#include "Star.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CircleAction.h"
#include <iostream>
#include <cmath>

const std::string GamingScene::levelChoose[2][3] =
{
	{ ".//GamingScene//1_0//GamingScene1_0.csb", ".//GamingScene//1_1//GamingScene1_1.csb", ".//GamingScene//1_2//GamingScene1_2.csb" },
	{ ".//GamingScene//2_0//GamingScene2_0.csb", ".//GamingScene//2_1//GamingScene2_1.csb", ".//GamingScene//2_2//GamingScene2_2.csb" },
};

const int GamingScene::starNumber[2][3] =
{
	{ 5, 0, 0 },
	{ 0, 0, 0 },
};

cocos2d::Scene* GamingScene::createScene(int _sceneNumber, int _levelNumber)
{
	auto scene = Scene::create();
	auto layer = GamingScene::create(_sceneNumber, _levelNumber);
	scene->addChild(layer);
	return scene;
}

bool GamingScene::init(int _sceneNumber, int _levelNumber)
{
	if (!Layer::init())
	{
		return false;
	}
	this->sceneNumber = _sceneNumber;
	this->levelNumber = _levelNumber;
	auto rootnode = CSLoader::createNode(levelChoose[sceneNumber][levelNumber]);
	addChild(rootnode);

	layerNode = rootnode;

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	isFlying = false;
	minDistance = FLT_MAX;
	score = 0;

	for (int i = 0, j = 100; i < starNumber[sceneNumber][levelNumber]; ++i, ++j)
	{
		starAimNode.push_back(rootnode->getChildByTag(j));
		starAimNode.back()->setContentSize(Size(10, 10));
		//log("starAimNode");
	}

	for (std::vector<cocos2d::Node*>::iterator it1 = starAimNode.begin(); it1 != starAimNode.end(); ++it1)
	{
		for (std::vector<cocos2d::Node*>::iterator it2 = it1 + 1; it2 < starAimNode.end(); ++it2)
		{
			minDistance = (((*it1)->getPositionX() - (*it2)->getPositionX())*((*it1)->getPositionX() - (*it2)->getPositionX())) +
			(((*it1)->getPositionY() - (*it2)->getPositionY())*((*it1)->getPositionY() - (*it2)->getPositionY())) < minDistance ?
				          (((*it1)->getPositionX() - (*it2)->getPositionX())*((*it1)->getPositionX() - (*it2)->getPositionX())) +
			(((*it1)->getPositionY() - (*it2)->getPositionY())*((*it1)->getPositionY() - (*it2)->getPositionY())) : minDistance ;
		}
	}
	minDistance *= 0.8;

	for (int i = 0; i < starNumber[sceneNumber][levelNumber]; ++i)
	{
		starSprite.push_back(Star::create());
		starSprite.back()->setScale(0.5f);
		starSprite.back()->setVisible(false);
		starSprite.back()->runAction(RepeatForever::create(RotateBy::create(5, 360)));
		act = CircleMoveAction::create(2, rootnode->getChildByTag(1)->getPosition(), 60, 360, 20);
		starSprite.back()->runAction(RepeatForever::create(act));
		addChild(starSprite.back());
	}
	starSprite.back()->setVisible(true);

	return true;
}


bool GamingScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if ( !GamingScene::isFlying )
	{
		starLaunch();
		isFlying = true;
		//log("touched");
	}
	else if( GamingScene::isFlying )
	{
		isFlying = false;
		//Director::getInstance()->replaceScene(GamingScene::createScene(0, 0));
		starSprite.back()->stop();
		judgeAimed();
	}
	return true;
}

void GamingScene::starLaunch()
{
	starSprite.back()->stopAllActions();
	auto centerPosion = layerNode->getChildByTag(1)->getPosition();
	auto starPosion = starSprite.back()->getPosition();
	auto size = Director::getInstance()->getVisibleSize();
	starSprite.back()->runAction(RepeatForever::create(RotateBy::create(3, 360)));
	starSprite.back()->runAction(MoveTo::create(1, layerNode->getChildByTag(1)->getPosition() + 15*(starSprite.back()->getPosition() - layerNode->getChildByTag(1)->getPosition())));
}

void GamingScene::computerAim(std::vector<cocos2d::Node*>::iterator it)
{
	if (it == starAimNode.end() ) 
	{
		starSprite.back()->disappear();
		starSprite.pop_back();
	}
	else
	{
		auto dis = ((*it)->getPositionX() - starSprite.back()->getPositionX()) * ((*it)->getPositionX() - starSprite.back()->getPositionX()) +
			       ((*it)->getPositionY() - starSprite.back()->getPositionY()) * ((*it)->getPositionY() - starSprite.back()->getPositionY()) ;
		score += static_cast<int>(dis / minDistance * 100);
		starSprite.pop_back();
	}
}

std::vector<cocos2d::Node*>::iterator GamingScene::judgeAimed()
{
	std::vector<cocos2d::Node*>::iterator it;
	for (it = starAimNode.begin(); it != starAimNode.end(); ++it)
	{
		auto dis = ((*it)->getPositionX() - starSprite.back()->getPositionX()) * ((*it)->getPositionX() - starSprite.back()->getPositionX()) +
			       ((*it)->getPositionY() - starSprite.back()->getPositionY()) * ((*it)->getPositionY() - starSprite.back()->getPositionY()) ;
		if (dis < minDistance)
			return it;
	}
	return it;
}