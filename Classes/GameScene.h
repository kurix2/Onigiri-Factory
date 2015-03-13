#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__


#include "cocos2d.h"
#include "ccConfig.h"
#include <vector>


USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
protected:
	//Produce random floats between .95 and 1.0
	//Used for onigiri spawn updates
	float mRandomFloat1 = 0.95 + (CCRANDOM_0_1() * 1);
	float mRandomFloat2 = 0.95 + (CCRANDOM_0_1() * 1);
	float mRandomFloat3 = 0.95 + (CCRANDOM_0_1() * 1);



	//Bottom position of the conveyor belt
	int mBottom = 50; 
	
	// Produces a random number between 0 and 3.
	int mDevilActionType = (CCRANDOM_0_1() * 3);
	
	// Gets window size
	CCSize mWinSize = CCDirector::sharedDirector()->getWinSize(); 

public:

	int mPoints = 0; // Player Points
	float mDuration = 10.f; // Move duration for onigiri sprite
	float mBeltMove = 1.1f; // Rate at which the conveyor belt moves
	float mDevilDuration = 2.0f; // Move duration for the devil onigiri sprite
	float mBarPercentage = 0.0f; // Percentage of rage meter that is filled
	int mLast = 0; // Member value for last onigiri sprite touched
	int mLast_last = 0; // Member value for second to last onigiri touched
	cocos2d::CCArray mOnigiriArray; // CCArray that stores spawned onigiri sprite
	
	//Erases node from screen and mOnigiriArray
	void eraseOnigiri(CCNode * node);
    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	// Adds onigiri1 sprite to screen.  
	void addOnigiri1(float delta);

	// Adds onigiri2 sprite to screen.  
	void addOnigiri2(float delta);

	// Adds onigiri3 sprite to screen.  
	void addOnigiri3(float delta);
	

	// Adds devil onigiri sprite to screen.  
	void addDevilOnigiri(float delta);

	// Updates every frame
	void update(float delta);
	
	//This function sends score to globaldataworks and changes scene to GameOverScene.
	void gameOver();

	//Moves belt images and repositions them when they reach the bottom of the screen.
	void scrollingBG(float delta);
	
	//Detects touch event and does actions to sprites
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};



#endif // __GAME_SCENE_H__
