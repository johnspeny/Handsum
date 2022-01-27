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

    // pause Layer
    auto pauseLayer = PauseLayer::create("pausemenubg.png", Size(195, 270));
    pauseLayer->setTitle("Paused");
    pauseLayer->setVisible(false);
    this->addChild(pauseLayer, 100);


    // pause button
    auto pauseButton =  Button::create("pause.png", "pause.png", "pause.png");
    pauseButton->addTouchEventListener([pauseLayer](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if(!Director::getInstance()->isPaused()){
                    pauseLayer->setVisible(true);
                    pauseLayer->setSwallowsTouches(true);
                    Director::getInstance()->pause();
                    log("show pop up");

                }
                break;
//            default:
//                break;
        }
    });

    pauseButton->setPosition(Vec2(origin.x + pauseButton->getContentSize().width, origin.y + visibleSize.height * 0.9f));
    this->addChild(pauseButton);


    // Labels
    auto scoreLabel = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 30);
    scoreLabel->setPosition(origin.x + visibleSize.width * 0.9f, origin.y + visibleSize.height * 0.9f);
    this->addChild(scoreLabel);

    auto timeLabel = Label::createWithTTF("Time: 0", "fonts/Marker Felt.ttf", 30);
    timeLabel->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.9f);
    this->addChild(timeLabel);

    // world of bodies
    GameVars::initVars();
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);

    // create the world
    _world = b2WorldNode::create(gravity.x, gravity.y, GameVars::metersHeight);
    this->addChild(_world, -1);


    // create Ball
    _ball = new PaperBall(this, _world);

    this->scheduleUpdate();

    return true;
}

void GameLayer::update(float dt) {
    // update ball physics
    _ball->update(dt);
}

