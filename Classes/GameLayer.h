//
// Created by okker on 1/21/2022.
//

#ifndef HANDSUM_GAMELAYER_H
#define HANDSUM_GAMELAYER_H

#include "cocos2d.h"
#include "audio/AudioEngine.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"
#include "Ball.h"
#include "HandPaddle.h"

class GameLayer : public cocos2d::Scene {
private:
    cocos2d::Vec2 origin;
    cocos2d::Size visibleSize;
    void onTouchesBegan(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);
    void onTouchesEnded(const std::vector<cocos2d::Touch*> &touches, cocos2d::Event* event);

    std::vector<HandPaddle*> _handPaddlePool;
public:
    virtual bool init() override;
    void update(float dt) override;

private:
    PaperBall* _ball;
    HandPaddle* _lefthand;
    HandPaddle* _righthand;
    b2WorldNode* _world;
    void createWallBody();
};


#endif //HANDSUM_GAMELAYER_H
