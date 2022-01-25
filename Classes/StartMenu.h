//
// Created by okker on 1/21/2022.
//

#ifndef HANDSUM_STARTMENU_H
#define HANDSUM_STARTMENU_H

#include "cocos2d.h"
#include "GameLayer.h"
#include "audio/AudioEngine.h"


class StartMenu : public cocos2d::Scene {
private:
    void playGame(cocos2d::Ref* pSender);
    void exitGame(cocos2d::Ref* pSender);
public:
    virtual bool init() override;
};


#endif //HANDSUM_STARTMENU_H
