#include "GameOver.h"
#include "GameScene.h"
#include "menuScene.h"
#include "GlobalDataWorks.h"
#include "cocos2d.h"

using namespace cocos2d;


USING_NS_CC;



CCScene* GameOver::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameOver *layer = GameOver::create();

	// add layer as a child to scene
	scene->addChild(layer);


	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{

	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


	// acquire score that was stored in GlobalDataWorks
	int _score = GlobalDataWorks::getInstance()->getScore();
	CCLOG("output %d", _score);

	// Display a message saying "You earned"
	CCLabelTTF* messageLabel = CCLabelTTF::create("You earned", "arial", 100);
	messageLabel->setPosition(ccp(
		mWinSize.width /2,
		(mWinSize.height/ 3) * 2));
	this->addChild(messageLabel, 5);
	
	//Display the amount of points the player got. Default is 0.
	CCLabelTTF* pointsLabel =
		CCLabelTTF::create("0", "arial", 105);
	pointsLabel->setPosition(ccp(
		mWinSize.width / 2,
		messageLabel->getPositionY() - messageLabel->getContentSize().height));
	pointsLabel->setTag(11);

	//Sets points to the amount acquired from GlobalDataWorks
	CCString* points = CCString::createWithFormat("%d", _score);
	pointsLabel->setString(points->getCString());
	this->addChild(pointsLabel, 5);


	// Restart button
	CCString title = "Restart";
	CCScale9Sprite* sprite = CCScale9Sprite::create("button9.png");
	CCLabelTTF* label = CCLabelTTF::create(title.getCString(), "Ariel", 30);
	CCControlButton* restartBtn = CCControlButton::create(label, sprite);
	restartBtn->setPreferredSize(CCSizeMake(200, 40));
	restartBtn->setPosition(ccp(
		visibleSize.width / 2,
		visibleSize.height / 3));

	//When touched, will change scene
	restartBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(menuScene::btnPushCallback),
		CCControlEventTouchUpInside);
	restartBtn->setTag(1);
	this->addChild(restartBtn);
	
	//When touched, will change button image for as long as being touched.
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameOver::menuCloseCallback));

	pCloseItem->setPosition(ccp(mWinSize.width/2,
		restartBtn->getPosition().y - pCloseItem->getContentSize().height * 2));

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	return true;
}

//Callback that changes scene to gameScene.
void GameOver::btnPushCallback(CCObject* pSender, CCControlEvent controlEvent)
{
	CCScene* nextScene = nullptr;
	CCControlButton* btn = (CCControlButton*)pSender;
	int tag = btn->getTag();
	nextScene = menuScene::scene();
	CCScene* pScene = CCTransitionFade::create(0.5f, nextScene);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

//Menu call back that closes application.
void GameOver::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}


