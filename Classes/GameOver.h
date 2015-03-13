#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT;

#include "cocos2d.h"

class GameOver : public cocos2d::CCLayer
{
public:

	int _score = 0;

	CCSize mWinSize = CCDirector::sharedDirector()->getWinSize();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	// call back to quit game
	void btnPushCallback(CCObject* pSstatender, CCControlEvent controlEvent);

    // implement the "static node()" method manually
    CREATE_FUNC(GameOver);
};

#endif // __GAME_OVER_H__
