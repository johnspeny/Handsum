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
    current_world = new_world;
    createBallBody(_ballSprite, current_world);

}

void PaperBall::createBallSprite(cocos2d::Scene *_gameLayer) {
    _ballSprite = Sprite::create("ball_soccer2.png");
    _ballSprite->setScale(visibleSize.width/_ballSprite->getContentSize().width/16, visibleSize.height/_ballSprite->getContentSize().height/8);
    _ballSprite->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.7f));
    _gameLayer->addChild(_ballSprite, 0);
}

void PaperBall::createBallBody(cocos2d::Sprite* new_ballsprite, b2WorldNode *new_world) {
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(new_ballsprite->getPositionX() / GameVars::PTM_Ratio, new_ballsprite->getPositionY() / GameVars::PTM_Ratio);
    ballBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(new_ballsprite);

    _ballbody = new_world->getb2World()->CreateBody(&ballBodyDef);

    // create circle shape
    b2CircleShape circle;
    circle.m_radius = new_ballsprite->getContentSize().width/2 * new_ballsprite->getScaleX() / GameVars::PTM_Ratio;

    // create shape definition and add to body
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    //ballShapeDef.friction = 0.f;
    ballShapeDef.restitution = 0.7f;

    _ballbody->CreateFixture(&ballShapeDef);

    // add velocity to it
    _ballbody->ApplyLinearImpulse(b2Vec2(0, -10), b2Vec2(_ballbody->GetWorldCenter()),true);

}

void PaperBall::update(float dt) {

    //  8, 1
    static int velocityIterations = 6;
    static int positionIterations = 2;

    current_world->getb2World()->Step(dt, velocityIterations, positionIterations);

    for (b2Body* body = current_world->getb2World()->GetBodyList(); body != nullptr; body = body->GetNext()) {
    	uintptr_t x = body->GetUserData().pointer;
    	uintptr_t y =_ballbody->GetUserData().pointer;

    	if (x == y) {
    	    //log("even bodies");
    		auto ball = (Sprite*)body->GetUserData().pointer;
            ball->setPosition(Vec2(body->GetPosition().x * GameVars::PTM_Ratio, body->GetPosition().y * GameVars::PTM_Ratio));
            ball->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
    	}
    }
}
