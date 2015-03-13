#include "Onigiri.h"
#include "GameScene.h"
#include "cocos2d.h"
#include "ccConfig.h"

using namespace cocos2d;

Onigiri::Onigiri()
{
}

CCRect Onigiri::getRect()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint point = this->getPosition();
	
	
	int w = this->getContentSize().width;
	int h = this->getContentSize().height;
	
	return CCRectMake(point.x-(w/2), point.y-(h/2), w, h);
}


bool Onigiri::isTouchPoint(CCPoint point)
{
	return this->getRect().containsPoint(point);
}

