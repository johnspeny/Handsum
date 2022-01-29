//
// Created by okker on 1/28/2022.
//

#ifndef HANDSUM_HANDPADDLE_H
#define HANDSUM_HANDPADDLE_H

#include "cocos2d.h"
#include "b2WorldNode.h"
#include "GameVars.h"

class HandPaddle {
private:
    b2WorldNode* current_world;
    //b2Body* _handbody;
    void createHandBody(cocos2d::Sprite* sprite, b2WorldNode *new_world);
public:
    HandPaddle(cocos2d::Scene* _gameLayer, b2WorldNode* new_world, float new_posX, float new_posY);
    ~HandPaddle();
    void update(float dt);
private:
    void createHandSprite(cocos2d::Scene *_gameLayer, float posX, float posY);
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
public:
    CC_SYNTHESIZE(cocos2d::Sprite*, _handSprite, HandSprite);
    CC_SYNTHESIZE(cocos2d::Touch*, _touch, Touch);
    CC_SYNTHESIZE(cocos2d::Point, _nextPosition, NextPosition);
    CC_SYNTHESIZE(b2Body* , _handbody, Handbody);

};


#endif //HANDSUM_HANDPADDLE_H
