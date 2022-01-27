//
// Created by okker on 1/27/2022.
//

#ifndef HANDSUM_BALL_H
#define HANDSUM_BALL_H

#include "cocos2d.h"
#include "b2WorldNode.h"
#include "GameVars.h"

class PaperBall {
private:
    b2WorldNode* current_world;
    b2Body* _ballbody;
    void createBallBody(cocos2d::Sprite* sprite, b2WorldNode *new_world);
public:
    PaperBall(cocos2d::Scene* _gameLayer, b2WorldNode* new_world);
    ~PaperBall();
    void update(float dt);
private:
    void createBallSprite(cocos2d::Scene *_gameLayer);
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
    CC_SYNTHESIZE(cocos2d::Sprite*, _ballSprite, BallSprite);
};


#endif //HANDSUM_BALL_H
