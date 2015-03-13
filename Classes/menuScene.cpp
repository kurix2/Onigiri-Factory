#include "menuScene.h"
#include "GameScene.h"
#include "HelloWorldScene.h"
#include "Onigiri.h"

USING_NS_CC;

CCScene* menuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    menuScene *layer = menuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);


    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool menuScene::init()
{
	
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
   

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSprite* pSprite = CCSprite::create("title.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
	
	CCString titleTbl[] = {"Start"};

	for (int i = 0; i < 1;i++)
	{
	
		CCScale9Sprite* sprite = CCScale9Sprite::create("button9.png");
	
		CCLabelTTF* label = CCLabelTTF::create(titleTbl[i].getCString(),"MarkerFelt",30);
	
		CCControlButton* btn = CCControlButton::create(label, sprite);
	
		btn->setPreferredSize(CCSizeMake(200,40));
	
		btn->setPosition(ccp(
			visibleSize.width / 2 + (i/11) * 400,
			(visibleSize.height / 2 - (i % 11) * 50) - 100 ));
		btn->addTargetWithActionForControlEvents(this, cccontrol_selector(menuScene::btnPushCallback),
			CCControlEventTouchUpInside);

		btn->setTag(i);

		this->addChild(btn);
	}

    return true;
}

void menuScene::btnPushCallback(CCObject* pSender,CCControlEvent controlEvent)
{
	CCScene* nextScene = GameScene::scene();
	CCControlButton* btn = (CCControlButton*)pSender;
	int tag = btn->getTag();
	CCScene* pScene = CCTransitionFade::create(0.5f, nextScene);

	CCDirector::sharedDirector()->replaceScene(pScene);
}


