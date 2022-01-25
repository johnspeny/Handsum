//
// Created by okker on 1/21/2022.
//

#ifndef HANDSUM_GAMELAYER_H
#define HANDSUM_GAMELAYER_H

#include "cocos2d.h"
#include "audio/AudioEngine.h"
#include "ui/CocosGUI.h"
#include "PauseLayer.h"


class GameLayer : public cocos2d::Scene {
public:
    virtual bool init() override;

private:
    void pauseGame(cocos2d::Ref* sender);
    PauseLayer* pauseLayer;
};


#endif //HANDSUM_GAMELAYER_H
