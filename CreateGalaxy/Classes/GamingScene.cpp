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

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	isFlying = false;
	minX = minY = minDistance = FLT_MAX;

	for (int i = 0, j = 100; i < starNumber[sceneNumber][levelNumber]; ++i, ++j)
	{
		starAimNode.push_back(rootnode->getChildByTag(j));
		starAimNode.back()->setContentSize(Size(10, 10));
		log("starAimNode");
	}

	for (std::vector<cocos2d::Node*>::iterator it1 = starAimNode.begin(); it1 != starAimNode.end(); ++it1)
	{
		for (std::vector<cocos2d::Node*>::iterator it2 = it1 + 1; it2 < starAimNode.end(); ++it2)
		{
			//minDistance = sqrt((((*it1)->getPositionX() - (*it2)->getPositionX())*((*it1)->getPositionX() - (*it2)->getPositionX())) +
			//	(((*it1)->getPositionY() - (*it2)->getPositionY())*((*it1)->getPositionY() - (*it2)->getPositionY()))) < minDistance ?
			//	sqrt((((*it1)->getPositionX() - (*it2)->getPositionX())*((*it1)->getPositionX() - (*it2)->getPositionX())) +
			//	(((*it1)->getPositionY() - (*it2)->getPositionY())*((*it1)->getPositionY() - (*it2)->getPositionY()))) : minDistance;
			minX = ((*it1)->getPositionX() - (*it2)->getPositionX()) > minX ? minX : ((*it1)->getPositionX() - (*it2)->getPositionX());
			minY = ((*it1)->getPositionY() - (*it2)->getPositionY()) > minX ? minX : ((*it1)->getPositionY() - (*it2)->getPositionY());
		}
	}

	for (std::vector<cocos2d::Node*>::iterator it = starAimNode.begin(); it != starAimNode.end(); ++it )
	{
		(*it)->setContentSize(Size(minX,minY));
	}

	for (int i = 0; i < starNumber[sceneNumber][levelNumber]; ++i)
	{
		starSprite.push_back(Star::create());
		starSprite.back()->setScale(0.5f);
		starSprite.back()->setVisible(false);
		starSprite.back()->setPosition(rootnode->getChildByTag(1)->getPosition());
		//starSprite.back()->setAnchorPoint(Vec2( ((rootnode->getChildByTag(1)->getPositionX() - rootnode->getChildByTag(0)->getPositionX()) / (starSprite.back()->getContentSize().width) * 2.5) , 0.5f));
		//starSprite.back()->setAnchorPoint(Vec2(-2.0, 0.5f));
		//starSprite.back()->runAction(RepeatForever::create( Sequence::createWithTwoActions(RotateTo::create(2, 180),RotateTo::create(2,0))));
		starSprite.back()->runAction(RepeatForever::create(RotateBy::create(4, 360)));
		addChild(starSprite.back()); 
		log("starSprite");
		
	}
	starSprite.back()->setVisible(true);

	return true;
}

bool GamingScene::judgeAimed()
{
	std::vector<cocos2d::Node*>::iterator it;
	for ( it = starAimNode.begin(); it <= starAimNode.end(); ++it)
	{

	}
	return true;
}

bool GamingScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if ( !GamingScene::isFlying )
	{
		starLaunch();
		isFlying = true;
		log("touched");
	}
	else if( GamingScene::isFlying )
	{
		log("touched with else");
		//starSprite.back()->stop();
		isFlying = false;
		//judgeAimed();
	}
	return true;
}

void GamingScene::starLaunch()
{
	starSprite.back()->stopAllActions();

}