//
// Created by okker on 2/27/2021.
//

#ifndef HANDSUM_MYCONTACTLISTENER_H
#define HANDSUM_MYCONTACTLISTENER_H


#include "box2d/box2d.h"
#include <vector>
#include <algorithm>
#include "cocos2d.h"

struct MyContact {
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    bool operator==(const MyContact& other) const
    {
        return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
    }
};

class MyContactListener : public b2ContactListener {
private:
    cocos2d::Scene* _gL;

public:
    std::vector<MyContact> _contacts;

    MyContactListener();
    ~MyContactListener();

    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};

#endif //HANDSUM_MYCONTACTLISTENER_H
