//
//  GamingScene.cpp
//  CreateGalaxy
//
//  Created by Thomas and his friends on 2016/8/26.
//
//
#include "GamingScene.h"
#include "Star.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CircleAction.h"
#include <iostream>
#include <cmath>
#include "ChooseLevelScene.h"
#include "ChooseLevelScene_1.h"

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
	this->starLeftNumber = starNumber[sceneNumber][levelNumber];

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
		starStarMap[starAimNode.back()] = nullptr;
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

	minDistance *= 0.1f;

	for (int i = 0; i < starNumber[sceneNumber][levelNumber]+1; ++i)
	{
		starSprite.push_back(Star::create());
		starSprite.back()->setScale(0.5f);
		starSprite.back()->setVisible(false);
		starSprite.back()->runAction(RepeatForever::create(RotateBy::create(5, 360)));
		act = CircleMoveAction::create(5, rootnode->getChildByTag(1)->getPosition(), 60, 360, 20);
		starSprite.back()->runAction(RepeatForever::create(act));
		addChild(starSprite.back());
	}
	starSprite.back()->setVisible(true);
	scheduleUpdate();
	return true;
}

void GamingScene::update(float delta)
{
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 pos = starSprite.back()->getPosition();
	if (pos.x < 0 || pos.y < 0 || pos.x > size.width || pos.y > size.height)
	{
		isFlying = false;
		starSprite.back()->disappear();
		unscheduleUpdate();
		starSprite.pop_back();

		if (--starLeftNumber > 0)
		{
			starSprite.back()->setVisible(true);
			scheduleUpdate();
		}
		else
		{
			this->gameEnd();
		}
		log("log");
	}
}


bool GamingScene::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if ( !GamingScene::isFlying )
	{
		starLaunch();
		isFlying = true;
	}
	else if( GamingScene::isFlying )
	{
		isFlying = false;
		starSprite.back()->stop();
		computerAim(judgeAimed());
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
	starSprite.back()->runAction(MoveTo::create(3, layerNode->getChildByTag(1)->getPosition() + 15*(starSprite.back()->getPosition() - layerNode->getChildByTag(1)->getPosition())));
}


void GamingScene::computerAim(std::vector<cocos2d::Node*>::iterator it)
{
	if (it == starAimNode.end() ) 
	{
		log("end\n");
		starSprite.back()->disappear();
	}
	else
	{
		auto dis = ((*it)->getPositionX() - starSprite.back()->getPositionX()) * ((*it)->getPositionX() - starSprite.back()->getPositionX()) +
			       ((*it)->getPositionY() - starSprite.back()->getPositionY()) * ((*it)->getPositionY() - starSprite.back()->getPositionY()) ;
		if ( starStarMap[*it] == nullptr )
		{
			log("nullptr");
			starWithDistacne *p = new starWithDistacne;
			p->star = starSprite.back();
			p->dis = dis;
			starStarMap[*it] = p;
			score += static_cast<int>(minDistance / dis * 100);
		}
		else
		{
			if (starStarMap[*it]->dis > dis)
			{
				log("replace");
				auto a = starStarMap[*it]->dis;
				auto b = dis;
				starStarMap[*it]->star->disappear();
				starStarMap[*it]->star = starSprite.back();
				starStarMap[*it]->dis = dis;
			}
			else
			{
				auto a = starStarMap[*it]->dis;
				auto b = dis;
				log("not replace");
				starSprite.back()->disappear();
			}
		}
	}
	unscheduleUpdate();
	starSprite.pop_back();
	scheduleUpdate();
	if (--starLeftNumber > 0)
		starSprite.back()->setVisible(true);
	else
		this->gameEnd();
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

void GamingScene::callBack(Ref*)
{
	Director::getInstance()->replaceScene(ChooseLevelScene::createScene());
}

void GamingScene::gameEnd()
{
	_eventDispatcher->removeAllEventListeners();
	log("gameEnd");
	layerNode->getChildByTag(1)->setVisible(false);
	layerNode->getChildByTag(50)->setVisible(false);

	auto backLabel = Label::createWithTTF("Back", ".//fonts//Start.ttf", 50);
	backLabel->setTextColor(Color4B::WHITE);
	Menu * backMenu = Menu::createWithItem(MenuItemLabel::create(backLabel, CC_CALLBACK_1(GamingScene::callBack, this)));
	backMenu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width * 0.95, Director::getInstance()->getVisibleSize().height * 0.04));
	addChild(backMenu);

	for (auto it = starAimNode.begin(); it != starAimNode.end(); ++it)
	{
		if (starStarMap[*it] != nullptr)
		{
			score += ( minDistance / starStarMap[*it]->dis * 2 );
		}
	}

	std::stringstream ss;
	ss << score;
	std::string scoreStr;
	ss >> scoreStr;

	std::string str = "Your score is " + scoreStr;
	auto scoreLabel = Label::createWithTTF(str, ".//fonts//Start.ttf", 40);
	scoreLabel->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	scoreLabel->setTextColor(Color4B::WHITE);
	scoreLabel->setZOrder(5);
	addChild(scoreLabel);
}