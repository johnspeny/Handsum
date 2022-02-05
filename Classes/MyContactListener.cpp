//
// Created by okker on 2/27/2021.
//

#include "MyContactListener.h"

MyContactListener::MyContactListener() {
    //_gL = _gameLayer;
}

MyContactListener::~MyContactListener() {

}

void MyContactListener::BeginContact(b2Contact *contact) {
//    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
//    _contacts.push_back(myContact);
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

    auto spriteA = (cocos2d::Sprite *) bodyA->GetUserData().pointer;
    auto spriteB = (cocos2d::Sprite *) bodyB->GetUserData().pointer;

    if (spriteA && spriteB){
        if (spriteB->getTag() == 0 && spriteA->getTag() == 3){
            // ball hit left hand
            cocos2d::log("ball hit left hand");
        }
        else if (spriteB->getTag() == 1 && spriteA->getTag() == 3){
            // ball hit right hand
            cocos2d::log("ball hit right hand");
        }
        else if (spriteB->getTag() == 3 && spriteA->getTag() == 4){
            // ball  hit basket
            // update score
            //scoreInt++;
            //_gL->scoreLabel->setString(std::to_string(_gL->scoreInt));
            cocos2d::log("ball hit basket");
        }
//        cocos2d::log("Collided A %d", spriteA->getTag());
//        cocos2d::log("Collided B %d", spriteB->getTag());
    }
}

void MyContactListener::EndContact(b2Contact *contact) {
//    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
//    std::vector<MyContact>::iterator pos;
//    pos = std::find(_contacts.begin(), _contacts.end(), myContact);
//    if (pos != _contacts.end()) {
//        _contacts.erase(pos);
//    }
}

void MyContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
}

void MyContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {
}

