//
// Created by okker on 1/27/2022.
//

#include "Ball.h"

USING_NS_CC;

PaperBall::~PaperBall()
{

}

PaperBall::PaperBall(cocos2d::Scene *_gameLayer, b2WorldNode *new_world) {
    // visible and orin
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // sprite
    createBallSprite(_gameLayer);

    // create a paper ball physics body
    createBallBody(_ballSprite, new_world);

}

void PaperBall::createBallSprite(cocos2d::Scene *_gameLayer) {
    _ballSprite = Sprite::create("ball_soccer2.png");
    _ballSprite->setScale(visibleSize.width/_ballSprite->getContentSize().width/16, visibleSize.height/_ballSprite->getContentSize().height/8);
    _ballSprite->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.7f));
    _gameLayer->addChild(_ballSprite);
    log("scale %f: ",_ballSprite->getContentSize().width);
}

void PaperBall::createBallBody(cocos2d::Sprite* new_ballsprite, b2WorldNode *new_world) {
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(new_ballsprite->getPositionX() / GameVars::PTM_Ratio, new_ballsprite->getPositionY() / GameVars::PTM_Ratio);
    //ballBodyDef.userData.pointer = reinterpret_cast<uintptr_t>();

    _ballbody = new_world->getb2World()->CreateBody(&ballBodyDef);

    // create circle shape
    b2CircleShape circle;
    circle.m_radius = new_ballsprite->getContentSize().width/2 * new_ballsprite->getScaleX() / GameVars::PTM_Ratio;

    // create shape definition and add to body
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.f;
    ballShapeDef.restitution = 1.0f;

    _ballbody->CreateFixture(&ballShapeDef);

}

void PaperBall::update(float dt) {

}