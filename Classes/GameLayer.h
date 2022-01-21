//
// Created by okker on 1/21/2022.
//

#ifndef HANDSUM_GAMELAYER_H
#define HANDSUM_GAMELAYER_H

#include "cocos2d.h"

USING_NS_CC;

class GameLayer : public cocos2d::Scene {
public:
    virtual bool init() override;
    void update();
};


#endif //HANDSUM_GAMELAYER_H
