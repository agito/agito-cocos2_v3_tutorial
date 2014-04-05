//
//  GameScene.h
//  nyan30
//
//  Created by agito on 2014/02/14.
//
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
private:
    int nextNumber;
    float gameTime;
    
    void makeBackground();
    void makeCards();
    void measureGameTime(float fDelta);
    void showGameTimeLabel();
    
public:
    virtual bool init();
    static cocos2d::Scene *scene();
    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
};

#endif /* defined(__GAME_SCENE_H__) */
