//
//  GameScene.cpp
//  nyan30
//
//  Created by agito on 2014/02/14.
//
//

#include "GameScene.h"



using namespace cocos2d;
using namespace std;

Scene *GameScene::scene()
{
    Scene *scene = Scene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}


bool GameScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    srand((unsigned)time(NULL));
    
    nextNumber = 1;
    gameTime = 0;
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    makeBackground();
    makeCards();
    showGameTimeLabel();
    
    this->schedule(schedule_selector(GameScene::measureGameTime));
    
    
    return true;
}

void GameScene::makeBackground()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite *pBG = Sprite::create("background.png");
    pBG->setPosition(Point(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(pBG);
}


void GameScene::makeCards()
{
    Vector<CCInteger*> numbers;
    for (int i = 1; i < 26; i++) {
        numbers.pushBack(CCInteger::create(i));
    }
    
    Size winSize = Director::getInstance()->getWinSize();

    
    for (int x = 0; x <5; x++) {
        for (int y = 0; y <5; y++) {
            int index = rand() % numbers.size();
            int number = numbers.at(index)->getValue();
            
            Sprite *pCard = Sprite::create("card_frontside.png");
            Size cardSize = pCard->getContentSize();
            pCard->setPosition(Point(winSize.width * 0.5 + (x -2) * cardSize.width, winSize.height * 0.5 + (y -2) * cardSize.height));
            pCard->setTag(number);
            this->addChild(pCard);
            
            CCString *fileNmae = CCString::createWithFormat("%d.png", number);
            Sprite *pNumber = Sprite::create(fileNmae->getCString());
            pNumber->setPosition(Point(cardSize.width * 0.5, cardSize.height * 0.5));
            pCard->addChild(pNumber);
            
            numbers.erase(index);
        }
    }
}



bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    return true;
}

void GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    
    Director *pDirecotr = Director::getInstance();
    Point touchPoint = pDirecotr->convertToGL(pTouch->getLocationInView());
    
    Node *pCard = this->getChildByTag(nextNumber);
    if (!pCard) {
        return;
    }
    
    Rect cardRect = pCard->boundingBox();
    if(cardRect.containsPoint(touchPoint))
    {
        Sprite *pNewCard = Sprite::create("card_backside.png");
        pNewCard->setPosition(pCard->getPosition());
        this->addChild(pNewCard);
        
        pCard->removeFromParentAndCleanup(true);
        
        if (nextNumber >= 25) {
            this->unschedule(schedule_selector(GameScene::measureGameTime));
            
            return;
        }
        
        nextNumber++;
    }
    
    CCLOG("x: %f, y: %f", touchPoint.x, touchPoint.y);
}


void GameScene::measureGameTime(float fDelta)
{
    gameTime += fDelta;
    
    
    CCLOG("gametime: %f", gameTime);
    
    showGameTimeLabel();
}

void GameScene::showGameTimeLabel()
{
    const int tagGameTimeLabel = 100;
    
    CCString *timeString = CCString::createWithFormat("%8.1fs", gameTime);
    
    LabelTTF *timerLabel = (LabelTTF *)this->getChildByTag(tagGameTimeLabel);
    
    
    if (timerLabel) {
        timerLabel->setString(timeString->getCString());
    }
    else
    {
        Size winSize = Director::getInstance()->getWinSize();
        
        timerLabel = LabelTTF::create(timeString->getCString(), "Arial", 24.0);
        timerLabel->setPosition(Point(winSize.width * 0.9, winSize.height * 0.9));
        timerLabel->setTag(tagGameTimeLabel);
        this->addChild(timerLabel);
    }
}

