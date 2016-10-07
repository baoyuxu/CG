#include "GameEnd.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* GameEnd::createScene()
{
	auto scene = Scene::create();
	auto layer = GameEnd::create();
	scene->addChild(layer);
	return scene;
}

bool GameEnd::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}