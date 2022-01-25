//
// Created by okker on 1/21/2022.
//

#include "GameLayer.h"

USING_NS_CC;

using namespace ui;

bool GameLayer::init() {
    if(!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin      = Director::getInstance()->getVisibleOrigin();
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    // stop all music
    AudioEngine::stopAll();

    // pause button
    auto pauseButton =  Button::create("pause.png", "pause.png", "pause.png");
    pauseButton->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:

                // add some layer
                pauseLayer = PauseLayer::create("pausemenubg.png", Size(195, 270));
                pauseLayer->setTitle("Pause");
                this->addChild(pauseLayer, 100);
                //Director::getInstance()->pause();
               //pauseLayer->close();

                log("button presssed");

                //Director::getInstance()->pause();
               break;
//            default:
//                break;
        }
    });

    pauseButton->setPosition(Vec2(origin.x + pauseButton->getContentSize().width, origin.y + visibleSize.height * 0.9f));
    this->addChild(pauseButton);

    auto scoreLabel = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 30);
    scoreLabel->setPosition(origin.x + visibleSize.width * 0.9f, origin.y + visibleSize.height * 0.9f);
    this->addChild(scoreLabel);

    auto timeLabel = Label::createWithTTF("Time: 0", "fonts/Marker Felt.ttf", 30);
    timeLabel->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.9f);
    this->addChild(timeLabel);

    return true;
}

void GameLayer::pauseGame(cocos2d::Ref *sender) {
    CCLOG("pause game");
}
