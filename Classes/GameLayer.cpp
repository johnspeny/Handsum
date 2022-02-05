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
    visibleSize = Director::getInstance()->getVisibleSize();
    origin      = Director::getInstance()->getVisibleOrigin();
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
    scoreInt = 0;
    scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 30);
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
    this->addChild(_world, -10);


    // add collision listener
    _collisionListener = new MyContactListener();
    _world->getb2World()->SetContactListener(_collisionListener);


    // create wall
    createWallBody();

    // create a basket
    _basket = new Basket(this, _world);
    _basket->getBasketSprite()->setTag(4);

    // create Ball
    _ball = new PaperBall(this, _world);
    _ball->getBallSprite()->setTag(3);


    // left hand
    _lefthand = new HandPaddle(this, _world, origin.x + visibleSize.width * 0.1f, origin.y + visibleSize.height * 0.25f);
    _lefthand->getHandSprite()->setTag(0);
    _handPaddlePool.push_back(_lefthand);

    // right hand
    _righthand = new HandPaddle(this, _world, origin.x + visibleSize.width * 0.9f, origin.y + visibleSize.height * 0.25f);
    _righthand->getHandSprite()->setTag(1);
    _handPaddlePool.push_back(_righthand);

    // multiple touch events
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan =
            CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    listener->onTouchesMoved =
            CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
    listener->onTouchesEnded =
            CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    this->scheduleUpdate();

    return true;
}

void GameLayer::update(float dt) {
    // update basket physics
    _basket->update(dt);

    // update ball physics
    _ball->update(dt);

    // update handlePaddle physics
    _lefthand->update(dt);
    _lefthand->getHandSprite()->setPosition(_lefthand->getNextPosition());

    _righthand->update(dt);
    _righthand->getHandSprite()->setPosition(_righthand->getNextPosition());
}

void GameLayer::createWallBody() {
    b2BodyDef wallDef;
    wallDef.type = b2_staticBody;

    b2Body* body = _world->getb2World()->CreateBody(&wallDef);

    b2PolygonShape boxShape;

    b2FixtureDef wallFixtureDef;
    wallFixtureDef.shape = &boxShape;

    // add four walls to the static body
    boxShape.SetAsBox(visibleSize.width / GameVars::PTM_Ratio, 0.1f, b2Vec2(origin.x, (visibleSize.height / GameVars::PTM_Ratio) + (origin.y / GameVars::PTM_Ratio)), 0);
    body->CreateFixture(&wallFixtureDef);// ceiling

    boxShape.SetAsBox(visibleSize.width / GameVars::PTM_Ratio, 0.1f, b2Vec2(origin.x, origin.y / GameVars::PTM_Ratio), 0);
    body->CreateFixture(&wallFixtureDef);// ground

    boxShape.SetAsBox(0.1f, visibleSize.height / GameVars::PTM_Ratio, b2Vec2((origin.x / GameVars::PTM_Ratio) - (0.1f / GameVars::PTM_Ratio), origin.y / GameVars::PTM_Ratio), 0);
    body->CreateFixture(&wallFixtureDef);// left wall

    boxShape.SetAsBox(0.1f, visibleSize.height / GameVars::PTM_Ratio, b2Vec2(visibleSize.width / GameVars::PTM_Ratio, origin.y / GameVars::PTM_Ratio), 0);
    body->CreateFixture(&wallFixtureDef);// right wall

}

void
GameLayer::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {

    for( auto touch : touches) {
        if(touch != nullptr) {
            auto tap = touch->getLocation();
            for (auto hand : _handPaddlePool) {
                Point locationInNode = hand->getHandSprite()->convertToNodeSpace(touch->getLocation());
                Size s = hand->getHandSprite()->getContentSize();
                Rect rect = Rect(0, 0, s.width, s.height);
                if(rect.containsPoint(locationInNode)){
                    hand->setTouch(touch);
                    //log("touch began");
                }
            }
        }
    }
}

void
GameLayer::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {

    for( auto touch : touches) {
        if(touch != nullptr) {
            auto tap = touch->getLocation();
            for (auto hand : _handPaddlePool) {
                Point locationInNode = hand->getHandSprite()->convertToNodeSpace(touch->getLocation());
                if (hand->getTouch() != nullptr && hand->getTouch() == touch){
                    //log("moved");
                    Point nextPosition = tap;
                    hand->setNextPosition(nextPosition);
                    hand->getHandbody()->SetLinearVelocity(b2Vec2(tap.x - hand->getHandSprite()->getPositionX(), tap.y - hand->getHandSprite()->getPositionY()));
                    //hand->getHandbody()->ApplyLinearImpulse(b2Vec2(0, 0), hand->getHandbody()->GetWorldCenter(),true);
                }
//                Size s = hand->getHandSprite()->getContentSize();
//                Rect rect = Rect(0, 0, s.width, s.height);
//                if(rect.containsPoint(locationInNode)){
//                    hand->setTouch(touch);
//                }
            }
        }
    }
}

void
GameLayer::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    for( auto touch : touches) {
        if(touch != nullptr) {
            auto tap = touch->getLocation();
            for (auto hand : _handPaddlePool) {
                Point locationInNode = hand->getHandSprite()->convertToNodeSpace(touch->getLocation());
                if (hand->getTouch() != nullptr && hand->getTouch() == touch){
                    hand->setTouch(nullptr);
                }
            }
        }
    }
}
