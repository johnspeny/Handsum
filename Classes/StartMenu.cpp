//
// Created by okker on 1/21/2022.
//

#include "StartMenu.h"

USING_NS_CC;

bool StartMenu::init() {
    if(!Scene::init()){
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin      = Director::getInstance()->getVisibleOrigin();
    auto safeArea = Director::getInstance()->getSafeAreaRect();
    auto safeOrigin = safeArea.origin;

    // play music
    AudioEngine::stopAll();
    AudioEngine::play2d("rs.wav", true);

    // background image
    auto bg = Sprite::create("handsome.png");
    //CCLOG("w = %f, h = %f", visibleSize.width, visibleSize.height);
    bg->setScale(visibleSize.width/bg->getContentSize().width, visibleSize.height/bg->getContentSize().height);
    bg->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f));
    this->addChild(bg, -100);

    // buttons
    auto play = Sprite::create("play.png");
    auto exit = Sprite::create("exit.png");

    auto menuItPlay = MenuItemSprite::create(play, play, CC_CALLBACK_1(StartMenu::playGame, this));
    auto menuItExit = MenuItemSprite::create(exit, exit, CC_CALLBACK_1(StartMenu::exitGame, this));

    auto mainMenu = Menu::create(menuItPlay, menuItExit, nullptr);
    mainMenu->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.35f));
    mainMenu->alignItemsVerticallyWithPadding(40);
    this->addChild(mainMenu);
    //CCLOG("x: %f, y: %f", mainMenu->getAnchorPoint().x, mainMenu->getAnchorPoint().y);
    return true;
}

void StartMenu::playGame(Ref* pSender) {
    //Director::getInstance()->replaceScene(utils::createInstance<GameLayer>());
    auto scene = utils::createInstance<GameLayer>();
    Director::getInstance()->pushScene(scene);
}

void StartMenu::exitGame(cocos2d::Ref *pSender) {
    Director::getInstance()->end();
}
