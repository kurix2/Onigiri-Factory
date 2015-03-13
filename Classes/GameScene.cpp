#include "GameScene.h"
#include "GameOver.h"
#include "GlobalDataWorks.h"
#include "cocos2d.h"
#include <cstdlib>
#include "Onigiri.h"

using namespace cocos2d;
USING_NS_CC;


cocos2d::CCArray onigiriArray; // Array to hold all Onigiri sprite.

CCScene* GameScene::scene()
{
	CCScene *scene = CCScene::create();
	GameScene *layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);

	//Health Meter
	CCSprite* meterBorder = CCSprite::create("healthbarborder.png");

	meterBorder->setPosition(ccp(75, 600));
	this->addChild(meterBorder, -1);

	CCProgressTimer* progressTimer = CCProgressTimer::create(CCSprite::create("healthbar.png"));
	progressTimer->setType(kCCProgressTimerTypeBar);
	progressTimer->setMidpoint(ccp(0, 0));
	progressTimer->setBarChangeRate(ccp(1, 0));
	progressTimer->setPercentage(mBarPercentage);
	progressTimer->setPosition(ccp(75, 600));
	addChild(progressTimer, 1);
	progressTimer->setTag(30);


	int mPoints = 0; // Player Points 

	//Score Label
	CCLabelTTF* scoreLabel = CCLabelTTF::create("SCORE", "MarkerFelt", 25);
	scoreLabel->setPosition(ccp(
		mWinSize.width / 12,
		mWinSize.height - scoreLabel->getContentSize().height / 2));
	this->addChild(scoreLabel);

	//Score Amount Label
	CCLabelTTF* amountLabel =
		CCLabelTTF::create("0", "arial", 25);
	amountLabel->setPosition(ccp(
		scoreLabel->getPositionX() + scoreLabel->getContentSize().width,
		mWinSize.height - amountLabel->getContentSize().height / 2));
	amountLabel->setTag(11);
	this->addChild(amountLabel);


	// Conveyer Belt
	CCSprite* beltSprite1 = CCSprite::create("belt2.png"); // First belt image
	beltSprite1->setScaleX(1.5);
	beltSprite1->setAnchorPoint(ccp(0.5f, 0));
	beltSprite1->setPosition(ccp(mWinSize.width / 2, 0));
	beltSprite1->setTag(40);
	this->addChild(beltSprite1, 1);

	CCSprite* beltSprite2 = CCSprite::create("belt2.png");	// Second belt image
	beltSprite2->setScaleX(1.5);
	beltSprite2->setAnchorPoint(ccp(0.5f, 0));
	beltSprite2->setPosition(ccp(0, beltSprite1->boundingBox().size.height - 1));
	beltSprite2->setPosition(ccp(mWinSize.width / 2,mWinSize.height));
	beltSprite2->setTag(41);
	this->addChild(beltSprite2, 1);

	CCSprite* beltBottom = CCSprite::create("beltbottom.png"); // Black part at the bottom of the screen
	beltBottom->setScaleX(1.5);
	beltBottom->setTag(42);
	beltBottom->setPosition(ccp(mWinSize.width / 2, 20));
	this->addChild(beltBottom, 2);

	CCSprite* boxTop = CCSprite::create("boxtop.png"); // Onigiri sprites will fall in front of his sprite.
	boxTop->setTag(43);
	boxTop->setPosition(ccp(mWinSize.width / 2 + 352, 160));
	this->addChild(boxTop, 0);

	CCSprite* boxBottom = CCSprite::create("boxbottom.png"); // Onigiri sprites will fall behind this sprite
	boxBottom->setTag(44);
	boxBottom->setPosition(ccp(mWinSize.width / 2 + 350, 118));
	this->addChild(boxBottom, 4);
	

	// Updates 
	this->schedule(schedule_selector(GameScene::addOnigiri1), mRandomFloat1);
	this->schedule(schedule_selector(GameScene::addOnigiri2), mRandomFloat2);
	this->schedule(schedule_selector(GameScene::addOnigiri3), mRandomFloat3);
	this->schedule(schedule_selector(GameScene::addDevilOnigiri), 10.0f);
	this->schedule(schedule_selector(GameScene::scrollingBG), 0.01f, kCCRepeatForever, 0);

	//Update every frame
	this->scheduleUpdate();

	return true;
}

void GameScene::addOnigiri1(float delta)
{
	float beltRan01 = 300 + (CCRANDOM_0_1() * 340); // random x coordinate between 300 and 640

	//Create a new onigiri sprite, sets position, actions, and tag.
	Onigiri* onigiri1 = new Onigiri();
	onigiri1->initWithFile("onigiri1.png");
	onigiri1->autorelease();
	onigiri1->setPosition(ccp(beltRan01, mWinSize.height + onigiri1->getContentSize().height / 2));
	onigiri1->runAction(CCSequence::create(CCMoveTo::create(mDuration, ccp(beltRan01, 10)), NULL));
	onigiri1->setTag(1);
	
	bool intersects = false; // bounding boxes interest, or not.
	
	//  Loops through sprites by their tag and checks for collision before spawning onigiri1.
	for (int i = 0; i < 4; i++)
	{
		Onigiri* otherOnigiri = (Onigiri*)this->getChildByTag(i);
		if (otherOnigiri != nullptr)
		{
			CCRect spriteRec1 = onigiri1->boundingBox();

			CCRect otherOniRec = otherOnigiri->boundingBox();

			if (spriteRec1.intersectsRect(otherOniRec) && onigiri1->getTag() != otherOnigiri->getTag())
			{
				intersects = true;
				CCLog("intersect is true for sprite 1.");
			}
		}
	}

	// If the bounding boxes do not intersect, then spawn the sprite and add to the onigiriArray
	if (!intersects)
	{
		this->addChild(onigiri1, 3);
		onigiriArray.addObject(onigiri1);
		CCLog("Added an Onigiri1.");
	}
	else return;
}

void GameScene::addOnigiri2(float delta)
{
	float beltRan02 = 300 + (CCRANDOM_0_1() * 340);
	Onigiri* onigiri2 = new Onigiri();
	onigiri2->initWithFile("onigiri2.png");
	onigiri2->autorelease();
	onigiri2->setPosition(ccp(beltRan02, mWinSize.height + onigiri2->getContentSize().height / 2));
	onigiri2->runAction(CCSequence::create(CCMoveTo::create(mDuration, ccp(beltRan02, 10)), NULL));
	onigiri2->setTag(2);
	bool intersects = false;
	for (int i = 0; i < 4; i++)
	{
		Onigiri* otherOnigiri = (Onigiri*)this->getChildByTag(i);
		if (otherOnigiri != nullptr)
		{
			CCRect spriteRec2 = onigiri2->boundingBox();

			CCRect otherOniRec = otherOnigiri->boundingBox();

			if (spriteRec2.intersectsRect(otherOniRec) && onigiri2->getTag() != otherOnigiri->getTag())
			{
				intersects = true;
				CCLog("intersect is true for sprite 2.");
			}
		}
	}
	if (!intersects)
	{
		this->addChild(onigiri2, 3);
		onigiriArray.addObject(onigiri2);
	}
	else return;
}

void GameScene::addOnigiri3(float delta)
{
	float beltRan03 = 300 + (CCRANDOM_0_1() * 340); //  random x coordinate between 300 and 640
	Onigiri* onigiri3= new Onigiri();
	onigiri3->initWithFile("onigiri3.png");
	onigiri3->autorelease();
	onigiri3->setPosition(ccp(beltRan03, mWinSize.height + onigiri3->getContentSize().height / 2));
	onigiri3->runAction(CCSequence::create(CCMoveTo::create(mDuration, ccp(beltRan03, 10)), NULL));
	onigiri3->setTag(3);
	bool intersects = false;
	for (int i = 0; i < 4; i++)
	{
		Onigiri* otherOnigiri = (Onigiri*)this->getChildByTag(i);
		if (otherOnigiri != nullptr)
		{
			CCRect spriteRec3 = onigiri3->boundingBox();

			CCRect otherOniRec = otherOnigiri->boundingBox();

			if (spriteRec3.intersectsRect(otherOniRec) && onigiri3->getTag() != otherOnigiri->getTag())
			{
				intersects = true;
				CCLog("intersect is true for sprite 3.");
			}
		}
	}
	if (!intersects) 
	{
		this->addChild(onigiri3, 3);
		onigiriArray.addObject(onigiri3);
	}
	else return;
}

//Spawn devil onigiri
void GameScene::addDevilOnigiri(float delta)
{
	CCSprite* belt = (CCSprite*)getChildByTag(40);
	float beltRan04 = 300 + (CCRANDOM_0_1() * 340); //  random x coordinate between 300 and 640

	float devilRan1 = 300 + (CCRANDOM_0_1() * 340);
	float devilRan2 = 300 + (CCRANDOM_0_1() * 340);

	float mDevilDuration = 2.0f; // define the duration of the sprite's movement

	CCActionInterval* action1;
	CCActionInterval* action2;

	action1 = CCMoveTo::create(mDevilDuration, ccp(devilRan1, 300)); //devil goes here first
	action2 = CCMoveTo::create(mDevilDuration, ccp(devilRan2, 0)); // devil goes here second 
	Onigiri* devil = new Onigiri();
	devil->initWithFile("devilonigiri.png");
	devil->autorelease();
	devil->setPosition(ccp(beltRan04, mWinSize.height + devil->getContentSize().height / 2));
	devil->runAction(CCSequence::create(action1, action2, NULL));
	this->addChild(devil, 3, 4); // add devil onigiri, z-order 2, tag is 4
	onigiriArray.addObject(devil); // add to onigiriArray
}

//Erases onigiri from screen and removes from onigiriArray
void GameScene::eraseOnigiri(CCNode * node)
{
	CCSprite* sprite = (CCSprite*)node;
	bool isCleanUp = true;
	this->removeChild(node, isCleanUp);
	onigiriArray.removeObject(sprite);
}



//Detects touch event and does actions to sprites
bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	CCSprite* goal = (CCSprite*)this->getChildByTag(44);

	CCActionInterval* action1;
	CCActionInterval* action2;
	action1 = CCScaleTo::create(0.09f, 0.0f);
	//action2 = CCMoveTo::create(2.0f, ccp(goal->getPosition().x, goal->getPosition().y + 80));
	action2 = CCJumpTo::create(1.0f, ccp(goal->getPosition().x, goal->getPosition().y + 80), 250, 1);
	CCObject* obj = NULL;

	// Iterates through the onigiri array for the touched sprite.
	CCARRAY_FOREACH(&onigiriArray, obj)
	{
		Onigiri* onigiri = (Onigiri*)obj;
		int now = onigiri->getTag(); // The onigiri sprite that was just touched.
		if (onigiri->isTouchPoint(pTouch->getLocation()) )
		{
			if (onigiri->getTag() <= 3)
			{
				//Erases sprite;
				onigiri->runAction(CCSequence::create(
					action2, CCCallFuncN::create(this, callfuncN_selector(GameScene::eraseOnigiri)),
					NULL));
			}
			else
			{
				onigiri->runAction(CCSequence::create(
					action1, CCCallFuncN::create(this, callfuncN_selector(GameScene::eraseOnigiri)),
					NULL));
			}

			this->mPoints += 100;//add 100 points to score
			this->mDuration -= 0.1f; // Increase onigiri speed
			this->mDevilDuration -= 0.15f;// Increase devil onigiri speed
			this->mBeltMove += 0.01f; // Increase movement of belts

			//Update score label
			CCLabelTTF* label = (CCLabelTTF *)this->getChildByTag(11);
			CCString* points = CCString::createWithFormat("%d", this->mPoints);
			label->setString(points->getCString());

			//When 3 or more of the same onigiri are tapped in a row
			if (now == mLast && mLast == mLast_last)
			{
				this->mPoints += 500;//add 500
				label->setString(points->getCString());
			}
	
			else
			{
				mLast_last = mLast;
				mLast = now;
			}
		}
	}

	return true;
}


// Every frame update
void GameScene::update(float delta)
{
	CCObject* obj = NULL;

	CCActionInterval* action1;
	CCActionInterval* action2;

	action1 = CCScaleTo::create(0.1f, 1.1f);
	action2 = CCScaleTo::create(0.1f, 0.1f);

	CCProgressTimer* timer = (CCProgressTimer*)getChildByTag(30);

	CCARRAY_FOREACH(&onigiriArray, obj)
	{
		Onigiri* onigiri = (Onigiri*)obj;

		//If onigiri reach the bottom then erase from screen, remove from onigiriArray, and increase bar percentage.
		if (onigiri->getPosition().y <= mBottom && onigiri->getTag() != 4)
		{
			onigiri->runAction(CCSequence::create(
				action1,
				action2,
				(CCCallFuncN::create(
				this,
				callfuncN_selector(GameScene::eraseOnigiri))),
				NULL));
			mBarPercentage += 5.0f;
			timer->setPercentage(mBarPercentage);
			
		}

		else if (onigiri->getPosition().y <= mBottom && onigiri->getTag() == 4)
		{
			onigiri->runAction(CCSequence::create(
				action1,
				action2,
				(CCCallFuncN::create(
				this,
				callfuncN_selector(GameScene::eraseOnigiri))),
				NULL));
			onigiriArray.removeObject(onigiri);
			mBarPercentage += 7.0f;
			timer->setPercentage(mBarPercentage);
		}
	}

	// If health bar reaches 100%
	if (mBarPercentage >= 100.0f)
	{
		this->gameOver();
	}
}

// When game is over.
void GameScene::gameOver()
{
	GlobalDataWorks::getInstance()->setScore(mPoints); //Get the class instance pointer

	CCLOG("input score", mPoints); // Print the score that was input

	CCScene* nextScene = (CCScene*)GameOver::create(); // Define next scene;

	//Radial Transition Effect
	CCScene* pScene = CCTransitionProgressRadialCCW::create(1.0f, nextScene);

	//If pScene is not null, then change scene.
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

// Scrolling background function
void GameScene::scrollingBG(float delta)
{
	//get the two belt sprite images
	CCSprite* pSprite1 = (CCSprite*)this->getChildByTag(40);
	CCSprite* pSprite2 = (CCSprite*)this->getChildByTag(41);

	//images move down every frame.
	pSprite1->setPosition(ccp(pSprite1->getPosition().x, pSprite1->getPosition().y - mBeltMove));
	pSprite2->setPosition(ccp(pSprite2->getPosition().x, pSprite2->getPosition().y - mBeltMove));

	// if an image is one full height under the screen, then put it on top of the other belt sprite image.
	if (pSprite1->getPosition().y < -mWinSize.height)
	{
		pSprite1->setPosition(ccp(mWinSize.width / 2, pSprite2->getPosition().y + pSprite2->boundingBox().size.height));
	}
	if (pSprite2->getPosition().y < -mWinSize.height)
	{
		pSprite2->setPosition(ccp(mWinSize.width / 2, pSprite1->getPosition().y + pSprite1->boundingBox().size.height));
	}
}