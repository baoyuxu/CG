#include "Star.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

Star::Star()
{

}

Star::~Star()
{

}

Star* Star::create()
{
	auto star = new Star();
	if (star && star->init() )
	{
		star->autorelease();
		return star;
	}
	else
	{
		CC_SAFE_DELETE(star);
		return nullptr;
	}
}

bool Star::init()
{
	Sprite::init();
	this->initWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(".//GamingScene//1_0//aroundStar.png"));
	return true;
}

void Star::launch()
{

}

void Star::stop()
{

}

void Star::disappear()
{

}
