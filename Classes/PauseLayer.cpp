//
// Created by okker on 1/24/2022.
//

#include "PauseLayer.h"

USING_NS_CC;

bool PauseLayer::init() {
    if(!LayerColor::init()){
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin      = Director::getInstance()->getVisibleOrigin();
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;


    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch* touch, Event* event)->bool{return true;};
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    setColor(Color3B(255, 0, 0));
    setOpacity(128);

    return true;
}

void PauseLayer::close(cocos2d::Ref *sender) {
    this->removeFromParentAndCleanup(true);
}

PauseLayer::PauseLayer() {
    log("hi");
}

PauseLayer::~PauseLayer() {

}

PauseLayer *PauseLayer::create(const char* bgImage, cocos2d::Size size) {

        PauseLayer* ret = new PauseLayer();
        if (ret->init())
        {
            auto sp = Sprite::create(bgImage);
            //sp->setScale(ret->visibleSize.width/sp->getContentSize().width,  ret->visibleSize.height/sp->getContentSize().height);
            //sp->setScale(9.0f);
            ret->setSpriteBackGround(sp);
            ret->_dialogContextSize = sp->getContentSize();
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
        return ret;
}

bool PauseLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    return false;
}

void PauseLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {

}

void PauseLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {

}



void PauseLayer::backgroundFinish() {

    // title
    auto pauseLabelTitle = Label::createWithTTF("Pause", "fonts/Marker Felt.ttf", 40);
    pauseLabelTitle->setPosition(_dialogContextSize.width * 0.5f, _dialogContextSize.height * 0.8f - pauseLabelTitle->getHeight());
    log("Label x: %f, y: %f", pauseLabelTitle->getPositionX(), pauseLabelTitle->getPositionY());
    getSpriteBackGround()->addChild(pauseLabelTitle);

    // buttons
    auto play = Sprite::create("play.png");
    auto exit = Sprite::create("exit.png");

    auto menuItPlay = MenuItemSprite::create(play, play, CC_CALLBACK_1(PauseLayer::resumeGame, this));
    menuItPlay->setScale(_dialogContextSize.width/play->getContentSize().width/2, _dialogContextSize.height/play->getContentSize().height/2/2/2);

    auto menuItExit = MenuItemSprite::create(exit, exit, CC_CALLBACK_1(PauseLayer::quitGame, this));
    menuItExit->setScale(_dialogContextSize.width/exit->getContentSize().width/2, _dialogContextSize.height/exit->getContentSize().height/2/2/2);


    auto mainMenu = Menu::create(menuItPlay, menuItExit, nullptr);
    mainMenu->setPosition(Vec2(_dialogContextSize.width * 0.5f, _dialogContextSize.height * 0.5f));
    mainMenu->alignItemsVerticallyWithPadding(20);
    log("bgSprite x: %f, y: %f", getSpriteBackGround()->getPositionX(), getSpriteBackGround()->getPositionY());
    log("bgSprite x: %f, y: %f", bgSprite->getPositionX(), bgSprite->getPositionY());
    log("x: %f, y: %f", mainMenu->getPositionX(), mainMenu->getPositionY());
    bgSprite->addChild(mainMenu, 1);

}

void PauseLayer::onEnter() {
    LayerColor::onEnter();

    bgSprite = getSpriteBackGround();
    //bgSprite->setContentSize(_dialogContextSize);
    bgSprite->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f));
    this->addChild(bgSprite, 0, 0);

    // add animation/ pop effect
    Action* pauseLayerAction = Sequence::create(
            ScaleTo::create(0.0, 0.0),
            ScaleTo::create(0.2, 1.25),
            ScaleTo::create(0.2, 2.5),
            CallFunc::create(CC_CALLBACK_0(PauseLayer::backgroundFinish, this)),
            nullptr
            );

    bgSprite->runAction(pauseLayerAction);
}

void PauseLayer::setTitle(const std::string_view& title, float fontsize) {
        auto titleLabel = Label::createWithTTF(title, "fonts/Marker Felt.ttf", fontsize);
        this->setTitleLabel(titleLabel);
}

void PauseLayer::onExit() {
    LayerColor::onExit();
}

void PauseLayer::resumeGame(cocos2d::Ref *sender) {
    //Director::getInstance()->resume();
    //this->removeFromParentAndCleanup(true);
}

void PauseLayer::quitGame(cocos2d::Ref *sender) {
    //auto scene = utils::createInstance<GameLayer>();
    //Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

