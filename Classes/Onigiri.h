#ifndef __ONIGIRI_H__
#define __ONIGIRI_H__

#include "cocos2d.h"
#include "ccConfig.h"
#include <iostream>
#include <vector>

using namespace std;



class Onigiri : public cocos2d::CCSprite
{
public:
	int comboNum;
	Onigiri();
	cocos2d::CCRect getRect();
	bool isTouchPoint(cocos2d::CCPoint);
	
};

#endif /* defined(__SQUARE_ONIGIRI_H__) */