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



class GameLayer : public cocos2d::Scene {
public:
    virtual bool init() override;
    void update(float dt) override;

private:
    PaperBall* _ball;
    b2WorldNode* _world;

};


#endif //HANDSUM_GAMELAYER_H
