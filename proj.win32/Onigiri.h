#ifndef __ONIGIRI_H__
#define __ONIGIRI_H__

#include "cocos2d.h"
#include "ccConfig.h"
#include "GameScene.h"

class Onigiri : public GameScene
{
public:
	Onigiri();
	~Onigiri();

	float rBelt = 300 + (CCRANDOM_0_1() * 340); // Random Area between 430 and 530 X coordinates
	float beltX = rBelt; // Area x-coordinate range decided by rBelt
	float duration;
	int nowTag = tnum[0];
	int r;

	void setPosAndTag();

	void setAction();
};

#endif    // __ONIGIRI_H__

