//
// Created by okker on 1/28/2022.
//

#include "HandPaddle.h"


USING_NS_CC;

HandPaddle::~HandPaddle()
{

}

HandPaddle::HandPaddle(cocos2d::Scene *_gameLayer, b2WorldNode *new_world, float new_posX, float new_posY) {
    _touch = nullptr;
    //_nextPosition = Vec2::ZERO;

    // visible and orin
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // sprite
    createHandSprite(_gameLayer, new_posX, new_posY);

    // create a paper ball physics body
    current_world = new_world;
    createHandBody(_handSprite, current_world);

}

void HandPaddle::createHandSprite(cocos2d::Scene *_gameLayer, float posX, float posY) {
    _handSprite = Sprite::create("ball_soccer2.png");
    _handSprite->setScale(visibleSize.width/_handSprite->getContentSize().width/16, visibleSize.height/_handSprite->getContentSize().height/8);
    _nextPosition.x = posX;
    _nextPosition.y = posY;
    _handSprite->setPosition(getNextPosition());
    _gameLayer->addChild(_handSprite, 0);
}

void HandPaddle::createHandBody(cocos2d::Sprite* new_ballsprite, b2WorldNode *new_world) {
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.fixedRotation = true;
    ballBodyDef.position.Set(new_ballsprite->getPositionX() / GameVars::PTM_Ratio, new_ballsprite->getPositionY() / GameVars::PTM_Ratio);
    ballBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(new_ballsprite);

    _handbody = new_world->getb2World()->CreateBody(&ballBodyDef);

    // create circle shape
    b2CircleShape circle;
    circle.m_radius = new_ballsprite->getContentSize().width/2 * new_ballsprite->getScaleX() / GameVars::PTM_Ratio;

    // create shape definition and add to body
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 10.0f;
    ballShapeDef.friction = 0.4f;
    ballShapeDef.restitution = 0.1f;

    _handbody->CreateFixture(&ballShapeDef);

    // add velocity to it
    //_ballbody->ApplyLinearImpulse(b2Vec2(0, -10), b2Vec2(_ballbody->GetWorldCenter()),true);

}

void HandPaddle::update(float dt) {

    for (b2Body* body = current_world->getb2World()->GetBodyList(); body != nullptr; body = body->GetNext()) {
        uintptr_t x = body->GetUserData().pointer;
        uintptr_t y =_handbody->GetUserData().pointer;

        if (x == y) {
            _handSprite = (Sprite*)body->GetUserData().pointer;
            body->SetTransform(b2Vec2(_handSprite->getPositionX()/GameVars::PTM_Ratio, _handSprite->getPositionY()/GameVars::PTM_Ratio), body->GetAngle());
        }
    }


    //  8, 1
//    static int velocityIterations = 6;
//    static int positionIterations = 2;
//
//    current_world->getb2World()->Step(dt, velocityIterations, positionIterations);

    for (b2Body* body = current_world->getb2World()->GetBodyList(); body != nullptr; body = body->GetNext()) {
        uintptr_t x = body->GetUserData().pointer;
        uintptr_t y =_handbody->GetUserData().pointer;

        if (x == y) {
            log("even handle bodies");
            _handSprite = (Sprite*)body->GetUserData().pointer;
            _handSprite->setPosition(Vec2(body->GetPosition().x * GameVars::PTM_Ratio, body->GetPosition().y * GameVars::PTM_Ratio));
            _handSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
        }
    }
}
