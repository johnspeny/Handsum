//
// Created by okker on 1/24/2022.
//

#ifndef HANDSUM_PAUSELAYER_H
#define HANDSUM_PAUSELAYER_H

#include "cocos2d.h"
#include "StartMenu.h"

class PauseLayer : public cocos2d::LayerColor {
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Sprite* bgSprite;
public:
    PauseLayer();
    ~PauseLayer();
    static PauseLayer* create(const char* bgImage, cocos2d::Size size);
    virtual bool init() override;
    void close(cocos2d::Ref* sender= nullptr);

    // Touch event listening shield down touch
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    // Title
    void setTitle(const std::string_view& title, float fontsize = 20.0f);

    virtual void onEnter();
    virtual void onExit();

    void resumeGame(cocos2d::Ref* sender);
    void quitGame(cocos2d::Ref* sender);

    void backgroundFinish();

    // set and get
    CC_SYNTHESIZE(bool , _swallowsTouches, SwallowsTouches);
    CC_SYNTHESIZE(cocos2d::Label*, _titleLabel, TitleLabel);
    CC_SYNTHESIZE(cocos2d::Sprite*, _spriteBackGround, SpriteBackGround);

private:
    cocos2d::Size _dialogContextSize;
};


#endif //HANDSUM_PAUSELAYER_H
