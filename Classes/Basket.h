//
// Created by okker on 1/30/2022.
//

#ifndef HANDSUM_BASKET_H
#define HANDSUM_BASKET_H

#include "cocos2d.h"
#include "b2WorldNode.h"
#include "GameVars.h"

class Basket {

private:
    b2WorldNode* current_world;
    b2Body* _basketbody;
    void createBasketBody(cocos2d::Sprite* sprite, b2WorldNode *new_world);
public:
    Basket(cocos2d::Scene* _gameLayer, b2WorldNode* new_world);
    ~Basket();
    void update(float dt);
private:
    void createBasketSprite(cocos2d::Scene *_gameLayer);
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
    CC_SYNTHESIZE(cocos2d::Sprite*, _basketSprite, BasketSprite);

};


#endif //HANDSUM_BASKET_H
